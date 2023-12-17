#pragma once

#include <iostream>
#include <algorithm>
#include <bitset>
#include <memory>
#include <vector>
#include <array>

using namespace std;

class Component;
class Entity;

using ComponentId = size_t;

// This function is responsible for providing a unique ComponentId each time it is called.
// It uses a static variable lastId to keep track of the last assigned type ID.
inline ComponentId getComponentTypeId()
{
	static ComponentId lastId = 0;
	return lastId++;
}

/* This is a function template that specializes the type ID retrieval for a specific type T.
It ensures that each type T gets a unique type ID.
It uses a static variable typeId to store the type ID for the specific type T.
It calls the non-template version getComponentTypeId() to obtain a new type ID if it hasn't been assigned yet.
It returns the type ID associated with type T. */
template <typename T> inline ComponentId getComponentTypeId() noexcept
{
	static ComponentId typeId = getComponentTypeId();
	return typeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitset = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component {
public:

	Entity* entity;

	virtual void update() {}
	virtual void init() {}
	virtual void draw(){}

	virtual ~Component() {}
};

class Entity {
private:
	bool active = true;
	vector<unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitset componentBitset;

public:
	void update() {
		for (auto& c : components) c->update();
	}

	void draw() {
		for (auto& c : components) c->draw();
	}
	bool isActive() { return active; }

	template<typename T> bool hasComponent() const {
		return componentBitset[getComponentTypeId<T>];
	}

	template<typename T, typename... TArgs>
	//  add a component to an entity and return a reference to the newly created component.
	T& addComponent(TArgs&&...mArgs)
	{
		// takes the arguments and forward it to the components constructor
		T* c(new T(forward <TArgs>(mArgs)...));
		c->entity = this;

		unique_ptr<Component> uPtr{ c };
		components.emplace_back(move(uPtr));

		componentArray[getComponentTypeId<T>()] = c;
		componentBitset[getComponentTypeId<T>()]= true;

		c->init();
		return *c;
	}

	// write the comment about it later
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeId<T>()]);
		return *static_cast<T*>(ptr);
	} 

};

class Manager
{
private:
	vector<unique_ptr<Entity>> entities;

public:
	void update() {
		for (auto& e : entities) e->update();
	}

	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		entities.erase(remove_if(entities.begin(), entities.end(),
			[](const unique_ptr<Entity>& mEnt) {
				return !mEnt->isActive();
			}), end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		unique_ptr<Entity> uPtr{ e };

		// move: to transfer ownership to the entities
		entities.emplace_back(move(uPtr));

		return *e;
	}
};
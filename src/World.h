#ifndef WORLD_H
#define WORLD_H

#include "Archetype.h"
#include "Component.h"
#include "Entity.h"
#include "Vector.h"
#include <concepts>
#include <iostream>
#include <unordered_map>

class World {
public:
  // Adds a new entity to the world and returns its ID.
  EntityId AddEntity();

  // Adds a component to an entity.
  template <std::derived_from<Component> T>
  void AddComponent(EntityId entityId);

  // Removes a component from an entity.
  template <std::derived_from<Component> T>
  void RemoveComponent(EntityId entityId);

#ifdef DEBUG
  void PrintEntities() const {
    std::wcout << L"World:" << std::endl;
    for (const auto& [entityId, archetype] : m_entities) {
      std::wcout << L"  Entity " << entityId << L": { ";
      for (const auto& type : archetype->m_type) {
        std::wcout << ComponentTypeIndex::Name(type) << " ";
      }
      std::wcout << L"}" << std::endl;
    }
  };
#else
  inline void PrintEntities() const {};
#endif

private:
  EntityId m_nextEntityId = 0;

  std::unordered_map<EntityId, Archetype*> m_entities;
  std::unordered_map<EntityType, Archetype, VectorHasher<ComponentType>>
      m_archetypes;

  void AddComponentOfType(EntityId entityId, ComponentType componentType);
  void RemoveComponentOfType(EntityId entityId, ComponentType componentType);

  Archetype* FindOrCreateArchetype(EntityType& entityType);
  void MoveToArchetype(EntityId entityId, Archetype* archetype);
};

// -----------------------------------------------------------------------------

template <std::derived_from<Component> T>
void World::AddComponent(EntityId entityId) {
  const ComponentType componentType = ComponentTypeIndex::Id<T>();
  AddComponentOfType(entityId, componentType);
}

template <std::derived_from<Component> T>
void World::RemoveComponent(EntityId entityId) {
  const ComponentType componentType = ComponentTypeIndex::Id<T>();
  RemoveComponentOfType(entityId, componentType);
}

#endif // WORLD_H

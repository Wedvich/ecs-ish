#include "World.h"

EntityId World::AddEntity() {
  EntityId id = ++m_nextEntityId;
  Archetype& archetype = m_archetypes[{}];
  m_entities[id] = &archetype;
  return id;
}

// -----------------------------------------------------------------------------

void World::AddComponentOfType(EntityId entityId, ComponentType componentType) {
  const auto archetype = m_entities[entityId];

  // If an edge already exists to the next archetype, follow it.
  if (archetype->m_edges[componentType].add != nullptr) {
    MoveToArchetype(entityId, archetype->m_edges[componentType].add);
    return;
  }

  // Bail out early if the entity already has the component.
  if (std::find(archetype->m_type.begin(), archetype->m_type.end(),
                componentType) != archetype->m_type.end()) {
    std::wcout << L"Entity " << entityId << L" already has component "
               << ComponentTypeIndex::Name(componentType) << std::endl;
    return;
  }

  auto entityType = EntityType(archetype->m_type);
  auto insertPosition =
      std::lower_bound(entityType.begin(), entityType.end(), componentType);
  entityType.insert(insertPosition, componentType);

  auto nextArchetype = FindOrCreateArchetype(entityType);
  archetype->m_edges[componentType].add = nextArchetype;
  nextArchetype->m_edges[componentType].remove = archetype;

  MoveToArchetype(entityId, nextArchetype);
}

// -----------------------------------------------------------------------------

void World::RemoveComponentOfType(EntityId entityId,
                                  ComponentType componentType) {
  const auto archetype = m_entities[entityId];

  // If an edge already exists to the next archetype, follow it.
  if (archetype->m_edges[componentType].remove != nullptr) {
    MoveToArchetype(entityId, archetype->m_edges[componentType].remove);
    return;
  }

  // Bail out early if the entity doesn't have the component.
  if (std::find(archetype->m_type.begin(), archetype->m_type.end(),
                componentType) == archetype->m_type.end()) {
    std::wcout << L"Entity " << entityId << L" doesn't have component "
               << ComponentTypeIndex::Name(componentType) << std::endl;
    return;
  }

  auto entityType = EntityType(archetype->m_type);
  auto removePosition =
      std::lower_bound(entityType.begin(), entityType.end(), componentType);
  entityType.erase(removePosition);

  auto nextArchetype = FindOrCreateArchetype(entityType);
  archetype->m_edges[componentType].remove = nextArchetype;
  nextArchetype->m_edges[componentType].add = archetype;

  MoveToArchetype(entityId, nextArchetype);
}

// -----------------------------------------------------------------------------

void World::MoveToArchetype(EntityId entityId, Archetype* archetype) {
  m_entities[entityId] = archetype;
}

// -----------------------------------------------------------------------------

Archetype* World::FindOrCreateArchetype(EntityType& entityType) {
  if (m_archetypes.find(entityType) == m_archetypes.end()) {
    m_archetypes[entityType] = Archetype{entityType};
  }

  return &m_archetypes[entityType];
}

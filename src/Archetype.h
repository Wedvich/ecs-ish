#ifndef ARCHETYPE_H
#define ARCHETYPE_H

#include "Component.h"
#include "Entity.h"
#include <unordered_map>

struct Archetype;

struct ArchetypeEdge {
  Archetype* add = nullptr;
  Archetype* remove = nullptr;
};

struct Archetype {
  EntityType m_type;
  std::unordered_map<ComponentType, ArchetypeEdge> m_edges;
};

#endif // ARCHETYPE_H

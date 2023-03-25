#define DEBUG 1

#include "Component.h"
#include "World.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>

struct Position : public Component {
  float x, y;
};

struct Velocity : public Component {
  float x, y;
};

int main() {
  World world;

  auto entityId1 = world.AddEntity();
  world.AddComponent<Position>(entityId1);
  world.AddComponent<Velocity>(entityId1);

  auto entityId2 = world.AddEntity();
  world.AddComponent<Velocity>(entityId2);
  world.AddComponent<Position>(entityId2);

  world.PrintEntities();

  world.RemoveComponent<Position>(entityId1);
  world.RemoveComponent<Velocity>(entityId2);

  world.PrintEntities();

  world.AddComponent<Velocity>(entityId2);
  world.AddComponent<Velocity>(entityId2);
  world.AddComponent<Velocity>(entityId2);

  world.PrintEntities();

  return 0;
}

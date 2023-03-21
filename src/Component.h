#ifndef COMPONENT_H
#define COMPONENT_H

#include <concepts>

// Base type for all components.
struct Component {
  virtual ~Component() {}
};

// Unique identifier for a Component type.
typedef std::uint32_t ComponentTypeId;

// Provides unique identifiers for Component types.
struct ComponentTypeIndex final {
  template <std::derived_from<Component> T>
  static ComponentTypeId Id() noexcept {
    static ComponentTypeId id = Count()++;
    return id;
  }

private:
  static ComponentTypeId& Count() noexcept {
    static ComponentTypeId counter = 0;
    return counter;
  }
};

#endif // COMPONENT_H

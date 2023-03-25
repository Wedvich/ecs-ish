#ifndef COMPONENT_H
#define COMPONENT_H

#include <concepts>
#include <unordered_map>

// Base type for all components.
struct Component {
  virtual ~Component() {}
};

// Unique identifier for a Component type.
typedef std::uint32_t ComponentType;

constexpr ComponentType INVALID_COMPONENT_TYPE =
    std::numeric_limits<ComponentType>::max();

// Provides unique identifiers for Component types.
class ComponentTypeIndex final {
public:
  template <std::derived_from<Component> T> static ComponentType Id() noexcept {
    static const ComponentType id = ++Count();
    s_names[id] = typeid(T).name();
    return id;
  }

  static const char* Name(ComponentType id) noexcept {
    if (s_names.find(id) == s_names.end()) {
      return "<<Invalid Component Type>>";
    }

    return s_names[id];
  }

private:
  static ComponentType& Count() noexcept {
    static ComponentType counter = INVALID_COMPONENT_TYPE;
    return counter;
  }

  static std::unordered_map<ComponentType, const char*> s_names;
};

#endif // COMPONENT_H

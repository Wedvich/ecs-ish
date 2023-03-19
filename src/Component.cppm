export module Component;

#include <concepts>

// Base type for all components.
export struct Component {
  virtual ~Component() {}
};

// Unique identifier for a Component type.
export typedef std::uint32_t ComponentTypeId;

// Provides unique identifiers for Component types.
export struct ComponentTypeIndex final {
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

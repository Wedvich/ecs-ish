#ifndef VECTOR_H
#define VECTOR_H

#include <bit>
#include <concepts>
#include <vector>

// Base class for type erased vectors.
struct TypeErasedVector {
  virtual ~TypeErasedVector(){};
  virtual void* at(std::size_t index) const = 0;
};

template <typename T> class TypedVector : public TypeErasedVector {
public:
  virtual void* at(std::size_t index) const override {
    if (index >= m_data.size()) {
      throw std::out_of_range("TypedVector::at() index out of range");
    }
    return &m_data[index];
  }

private:
  std::vector<T> m_data;
};

template <std::integral T> struct VectorHasher {
  std::size_t operator()(const std::vector<T>& vec) const {
    static constexpr int prime = 31;
    static constexpr int offset = 11;

    std::size_t hash = 0;
    for (const auto& val : vec) {
      hash = (hash * prime) + val;
      hash = std::rotl(hash, offset);
    }
    return hash;
  }
};

#endif // VECTOR_H

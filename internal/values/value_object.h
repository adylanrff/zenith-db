#pragma once

#include <cstdint>
#include <string>
#include <variant>

class ValueObject {
public:
  ValueObject(const ValueObject &) = default;
  ValueObject(ValueObject &&) = default;
  ValueObject &operator=(const ValueObject &) = default;
  ValueObject &operator=(ValueObject &&) = default;

  // Constructors
  ValueObject();
  ValueObject(int64_t);
  ValueObject(double);
  ValueObject(std::string);

  ~ValueObject() = default;

  std::string to_string() const;

private:
  std::variant<std::monostate, int64_t, double, std::string> value;
};

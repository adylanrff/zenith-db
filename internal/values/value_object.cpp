#include "values/value_object.h"
#include <cstdint>
#include <format>
#include <string>
#include <variant>

ValueObject::ValueObject() : value(std::monostate()) {}
ValueObject::ValueObject(int64_t v) : value(v) {}
ValueObject::ValueObject(double v) : value(v) {}
ValueObject::ValueObject(std::string v) : value(v) {}

struct StringVisitor {
  std::string operator()(std::monostate) { return "nil"; };
  std::string operator()(int64_t value) { return std::format("{}", value); };
  std::string operator()(double value) { return std::format("{}", value); };
  std::string operator()(const std::string &value) { return value; };
};

std::string ValueObject::to_string() const {
  return std::visit(StringVisitor(), value);
}

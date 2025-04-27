#pragma once

#include "expression.hpp"
#include <variant>
namespace intrp {

class unexpected_type_exception {};

template <typename T>
std::pair<T, T> expect_both(const expr_t &a, const expr_t &b) {
  if (!std::holds_alternative<T>(a) || !std::holds_alternative<T>(b))
    throw unexpected_type_exception{};
  return std::pair<T, T>(std::get<T>(a), std::get<T>(b));
}

template <typename T> T expect(const expr_t &a) {
  if (!std::holds_alternative<T>(a))
    throw unexpected_type_exception{};
  return std::get<T>(a);
}

expr_t expr_add(const expr_t &a, const expr_t &b);
std::ostream &operator<<(std::ostream &output, const expr_t &expr);
} // namespace intrp
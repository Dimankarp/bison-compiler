#include "expression.hpp"

#include "visitor.hpp"
#include <utility>
namespace intrp {

// Binop
binop_expression::binop_expression(binop op, std::unique_ptr<expression> left,
                                   std::unique_ptr<expression> right)
    : op(op), left(std::move(left)), right(std::move(right)) {}

void binop_expression::accept(expression_visitor &visitor) {
  visitor.visit_binop(*this);
}
// Unarop

unarop_expression::unarop_expression(unarop op, std::unique_ptr<expression> exp)
    : op(op), exp(std::move(exp)) {};
void unarop_expression::accept(expression_visitor &visitor) {
  visitor.visit_unarop(*this);
};

literal_expression::literal_expression(expr_t val) : val(std::move(val)) {};
void literal_expression::accept(expression_visitor &visitor) {
  visitor.visit_literal(*this);
};

identifier_expression::identifier_expression(std::string identificator)
    : identificator(std::move(identificator)) {}
void identifier_expression::accept(expression_visitor &visitor) {
  visitor.visit_identifier(*this);
};

} // namespace intrp
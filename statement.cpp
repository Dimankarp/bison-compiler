#include "statement.hpp"
#include "expression.hpp"
#include "visitor.hpp"
#include <memory>
#include <vector>
namespace intrp {

// Block
void block_statement::add_statement(std::unique_ptr<statement> s) {
  statements.push_back(std::move(s));
}
void block_statement::accept(statement_visitor &visitor) {
  visitor.visit_block(*this);
};

// Print
print_statement::print_statement(std::unique_ptr<expression> exp)
    : exp(std::move(exp)) {}
void print_statement::accept(statement_visitor &visitor) {
  visitor.visit_print(*this);
}

// Assign
assign_statement::assign_statement(std::string &&id,
                                   std::unique_ptr<expression> exp)
    : identifier(id), exp(std::move(exp)) {}
void assign_statement::accept(statement_visitor &visitor) {
  visitor.visit_assign(*this);
}

// If
if_statement::if_statement(std::unique_ptr<expression> cond,
                           std::unique_ptr<block_statement> then)
    : condition(std::move(cond)), then_block(std::move(then)) {}

void if_statement::accept(statement_visitor &visitor) {
  visitor.visit_if(*this);
}

void if_statement::add_else(std::unique_ptr<block_statement> else_block) {
  this->else_block = std::move(else_block);
};

// While
while_statement::while_statement(std::unique_ptr<expression> cond,
                                 std::unique_ptr<block_statement> block)
    : condition(std::move(cond)), block(std::move(block)) {}

void while_statement::accept(statement_visitor &visitor) {
  visitor.visit_while(*this);
}

} // namespace intrp
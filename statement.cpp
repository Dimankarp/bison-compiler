#include "statement.hpp"
#include "expression.hpp"
#include "visitor.hpp"
#include <memory>
#include <vector>
namespace intrp {
using std::unique_ptr;

// Block
void block_statement::add_statement(unique_ptr<statement> s) {
  statements.push_back(std::move(s));
}
void block_statement::accept(statement_visitor &visitor) {
  visitor.visit_block(*this);
};

const std::vector<unique_ptr<statement>> &
block_statement::get_statements() const {
  return statements;
}

// Print
print_statement::print_statement(unique_ptr<expression> exp)
    : exp(std::move(exp)) {}
void print_statement::accept(statement_visitor &visitor) {
  visitor.visit_print(*this);
}
const unique_ptr<expression> &print_statement::get_exp() const { return exp; }

// Assign
assign_statement::assign_statement(std::string &id, unique_ptr<expression> exp)
    : identifier(id), exp(std::move(exp)) {}
void assign_statement::accept(statement_visitor &visitor) {
  visitor.visit_assign(*this);
}

const std::string &assign_statement::get_identifier() const {
  return identifier;
}
const unique_ptr<expression> &assign_statement::get_exp() const { return exp; }

// If
if_statement::if_statement(unique_ptr<expression> cond,
                           unique_ptr<block_statement> then)
    : condition(std::move(cond)), then_block(std::move(then)) {}

void if_statement::accept(statement_visitor &visitor) {
  visitor.visit_if(*this);
}

void if_statement::add_else(unique_ptr<block_statement> else_block) {
  this->else_block = std::move(else_block);
};

const unique_ptr<expression> &if_statement::get_condition() const {
  return condition;
}
const unique_ptr<block_statement> &if_statement::get_then_block() const {
  return then_block;
}
const std::optional<unique_ptr<block_statement>> &
if_statement::get_else_block() const {
  return else_block;
}

// While
while_statement::while_statement(unique_ptr<expression> cond,
                                 unique_ptr<block_statement> block)
    : condition(std::move(cond)), block(std::move(block)) {}

void while_statement::accept(statement_visitor &visitor) {
  visitor.visit_while(*this);
}

const unique_ptr<expression> &while_statement::get_condition() const {
  return condition;
}
const unique_ptr<block_statement> &while_statement::get_block() const {
  return block;
}
} // namespace intrp
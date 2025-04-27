#pragma once

#include "expression.hpp"
#include "statement.hpp"
namespace intrp {

class expression_visitor {
public:
  virtual void visit_binop(const binop_expression &) = 0;
  virtual void visit_unarop(const unarop_expression &) = 0;
  virtual void visit_literal(const literal_expression &) = 0;
  virtual void visit_identifier(const identifier_expression &) = 0;
};

class statement_visitor {
public:
  virtual void visit_block(const block_statement &) = 0;
  virtual void visit_print(const print_statement &) = 0;
  virtual void visit_assign(const assign_statement &) = 0;
  virtual void visit_if(const if_statement &) = 0;
  virtual void visit_while(const while_statement &) = 0;
};

} // namespace intrp
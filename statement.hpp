#pragma once
#include "expression.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>
namespace intrp {

class statement_visitor;

class statement {
public:
  virtual ~statement() = default;
  virtual void accept(statement_visitor &) = 0;
};

class block_statement : public statement {
private:
  std::vector<std::unique_ptr<statement>> statements;

public:
  void add_statement(std::unique_ptr<statement> s);
  void accept(statement_visitor &visitor) override;
};
class print_statement : public statement {
private:
  std::unique_ptr<expression> exp;

public:
  print_statement(std::unique_ptr<expression> exp);
  void accept(statement_visitor &visitor) override;
};
class assign_statement : public statement {
private:
  std::string identifier;
  std::unique_ptr<expression> exp;

public:
  assign_statement(std::string &&id, std::unique_ptr<expression> exp);
  void accept(statement_visitor &visitor) override;
};

class if_statement : public statement {
private:
  std::unique_ptr<expression> condition;
  std::unique_ptr<block_statement> then_block;
  std::optional<std::unique_ptr<block_statement>> else_block;

public:
  if_statement(std::unique_ptr<expression> cond,
               std::unique_ptr<block_statement> then);
  void accept(statement_visitor &visitor) override;
  void add_else(std::unique_ptr<block_statement> else_block);
};

class while_statement : public statement {
private:
  std::unique_ptr<expression> condition;
  std::unique_ptr<block_statement> block;

public:
  while_statement(std::unique_ptr<expression> cond,
                  std::unique_ptr<block_statement> block);
  void accept(statement_visitor &visitor) override;
};

} // namespace intrp

#pragma once

#include <memory>
#include <string>
#include <variant>
namespace intrp {

class expression_visitor;

using expr_t = std::variant<std::string, int>;

class expression {
public:
  virtual ~expression() = default;
  virtual void accept(expression_visitor &) = 0;
};

enum class binop : char { ADD };

class binop_expression : public expression {
private:
  binop op;
  std::unique_ptr<expression> left;
  std::unique_ptr<expression> right;

public:
  binop_expression(binop op, std::unique_ptr<expression> left,
                   std::unique_ptr<expression> right);
  void accept(expression_visitor &visitor) override;
};

enum class unarop : char { MINUS };

class unarop_expression : public expression {
private:
  unarop op;
  std::unique_ptr<expression> exp;

public:
  unarop_expression(unarop op, std::unique_ptr<expression> exp);
  void accept(expression_visitor &visitor) override;
};

class literal_expression : public expression {
private:
  expr_t val;

public:
  literal_expression(expr_t val);
  void accept(expression_visitor &visitor) override;
};

class identifier_expression : public expression {
private:
  std::string identificator;

public:
  identifier_expression(std::string identificator);
  void accept(expression_visitor &visitor) override;
};

} // namespace intrp
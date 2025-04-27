%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.8"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  #include "expression.hpp"
  #include "statement.hpp"
  #include <string>
  #include <variant>

  class driver;
}

// The parsing context.
%param { driver& drv }


// Adding locations support
%locations

%define parse.trace
%define parse.error verbose

%code {
#include "driver.hpp"
#include "expression.hpp"
#include "statement.hpp"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  EOS     ";" // end of statement
  
  MINUS   "-"
  PLUS    "+"
  MUL     "*"
  DIV     "/"
  MOD     "%"
  LPAR    "("
  RPAR    ")"
  ASSIGN  "="
  LESS    "<"
  GRTR    ">"
  LESS_EQ "<="
  GRTR_EQ ">="
  EQUALS  "=="
  LCURL   "{"
  RCURL   "}"
  WHILE   "while"
  IF      "if"
  ELSE    "else"

  PRINT   "print"
;

%token <std::string> STR "string"
%token <std::string> ID "identifier"
%token <int> NUM "number"
%type  <std::unique_ptr<intrp::expression>> exp
%type  <std::unique_ptr<intrp::statement>> statement
%type  <std::unique_ptr<intrp::block_statement>> statements


// %printer { yyoutput << $$; } <*>;

%%
%start program;
program: statements {};

statements:
  %empty {
    $$ = std::make_unique<intrp::block_statement>();
  }
| statement statements {
    $$ = std::move($2);
    $2->add_statement(std::move($1));
};


statement: 
  "print" exp ";" {
    $$ = std::make_unique<intrp::print_statement>(std::move($2));
  };

//  | "identifier" "=" exp ";" {
//      drv.variables[$1] = $3;};
  
//  | "if" exp "{" statements

%left "+";

exp:
//  exp "+" exp {$$ = intrp::expr_add($1, $3);}
//  | "string" {$$ = intrp::expr_t($1);};
  "number" {
    $$ = std::make_unique<intrp::literal_expression>(intrp::expr_t($1));
  };
  //  | "identifier"  { $$ = drv.variables[$1]; };

/*
unit: assignments exp  { drv.result = $2; };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "identifier" ":=" exp { drv.variables[$1] = $3; };

%left "+" "-";
%left "*" "/";

exp:
  exp "+" exp   { $$ = $1 + $3; }
| exp "-" exp   { $$ = $1 - $3; }
| exp "*" exp   { $$ = $1 * $3; }
| exp "/" exp   { $$ = $1 / $3; }
| "(" exp ")"   { std::swap ($$, $2); }
| "identifier"  { $$ = drv.variables[$1]; }
| "number"      { std::swap ($$, $1); };
*/
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

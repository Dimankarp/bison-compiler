%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.8"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  #include<string>
  #include<variant>
  
  class driver;
  using expr_t = std::variant<int,  std::string>;
}

// The parsing context.
%param { driver& drv }


// Adding locations support
%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.hpp"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  
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
%type  <expr_t> exp

%printer { yyoutput << $$; } <*>;

%%
%start unit;
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
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}

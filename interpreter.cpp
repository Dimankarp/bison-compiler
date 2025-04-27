#include "driver.hpp"
#include "visitor.hpp"
#include <memory>

int main(int argc, char *argv[]) {
  int res = 0;
  driver drv;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string("-p"))
      drv.trace_parsing = true;
    else if (argv[i] == std::string("-s"))
      drv.trace_scanning = true;
    else {
      auto result = drv.parse(argv[i]);
      intrp::statement_executor exec{drv.variables};
      auto tree = std::move(result);
      tree->accept(exec);
    }
}

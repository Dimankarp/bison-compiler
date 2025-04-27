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
      if(drv.parse(argv[i])){
        std::cout << "Failed to parse - exiting.\n";
        exit(1);
      };
      auto variables = std::make_shared<var_table>();
      intrp::statement_executor exec{variables};
      auto tree = std::move(drv.result);
      tree->accept(exec);
    }
}

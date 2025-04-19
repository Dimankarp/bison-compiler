#include "driver.hpp"
#include "parser.tab.hpp"

driver::driver() : trace_parsing(false), trace_scanning(false) {}

void driver::parse(const std::string &f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  yy::parser parser(*this);
  parser.set_debug_level(trace_parsing);
  parser.parse();
  scan_end();
}

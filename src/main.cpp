#include "logger/logger.h"

#include <fmt/format.h>
#include <string>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  std::string var = fmt::format("hello {}", 10);

  auto log = Logger::get_instance().get_logger();
  log->info("hehehe");

  return 0;
}

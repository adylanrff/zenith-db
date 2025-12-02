#include "logger/logger.h"
#include "values/value_object.h"

#include <cstdint>
#include <fmt/format.h>
#include <string>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  std::string var = fmt::format("hello {}", 10);

  auto log = Logger::get_instance().get_logger();
  log->info("logger works. ");

  ValueObject v1("test");
  ValueObject v2(90.0);
  ValueObject v3((int64_t)90000);

  log->info(v1.to_string());
  log->info(v2.to_string());
  log->info(v3.to_string());

  return 0;
}

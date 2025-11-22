#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <string>

int main(int argc, char *argv[]) {
  std::string var = fmt::format("hello {}", 10);

  spdlog::info("Hello world!");
  spdlog::info(var);

  return 0;
}

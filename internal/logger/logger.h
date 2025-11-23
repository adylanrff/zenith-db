#pragma once
#include <memory>

#include <spdlog/logger.h>

class Logger {
public:
  static Logger &get_instance() {
    static Logger l;
    return l;
  };
  std::shared_ptr<spdlog::logger> get_logger() const;

private:
  Logger();
  ~Logger() = default;

  std::shared_ptr<spdlog::logger> internal_logger_;
};

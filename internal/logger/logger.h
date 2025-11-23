#pragma once
#include <memory>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  // copy
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  static Logger &get_instance() {
    static Logger logger;
    return logger;
  }

  std::shared_ptr<spdlog::logger> get_logger() const {
    return internal_logger_;
  }

private:
  ~Logger() = default;

  Logger() { internal_logger_ = spdlog::stdout_color_mt("Zenith"); };

  std::shared_ptr<spdlog::logger> internal_logger_;
};

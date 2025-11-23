#include <ios>
#include <memory>

#include "logger/logger.h"
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

Logger::Logger() { internal_logger_ = spdlog::stdout_color_mt("Zenith"); }

std::shared_ptr<spdlog::logger> Logger::get_logger() const {
  return internal_logger_;
}

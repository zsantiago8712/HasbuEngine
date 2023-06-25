#include "Utilities/Logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Hasbu::Utils {

std::shared_ptr<spdlog::logger> Logger::s_logger;

void Logger::initLogger()
{

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%T] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Logs/Hasbu.txt", true);
    file_sink->set_level(spdlog::level::info);

    file_sink->set_pattern("[%T] [%^%l%$] %v");

    const spdlog::sinks_init_list sink_list { console_sink, file_sink };
    s_logger = std::make_shared<spdlog::logger>("HasbuLogger", sink_list);
    s_logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> Logger::getLogger()
{
    return s_logger;
}

}

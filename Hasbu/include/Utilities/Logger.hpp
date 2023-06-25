#include <spdlog/logger.h>

namespace Hasbu::Utils {

class Logger {

public:
    static void initLogger();
    static std::shared_ptr<spdlog::logger> getLogger();

private:
    static std::shared_ptr<spdlog::logger> s_logger;
};

}

#define HASBU_BREAK __builtin_debugtrap();

#ifdef DEBUG

#define HASBU_TRACE(...) Hasbu::Utils::Logger::getLogger()->trace(__VA_ARGS__)
#define HASBU_DEBUG(...) Hasbu::Utils::Logger::getLogger()->debug(__VA_ARGS__)
#define HASBU_INFO(...) Hasbu::Utils::Logger::getLogger()->info(__VA_ARGS__)
#define HASBU_WARNING(...) Hasbu::Utils::Logger::getLogger()->warn(__VA_ARGS__)
#define HASBU_ERROR(...) Hasbu::Utils::Logger::getLogger()->error(__VA_ARGS__)
#define HASBU_FATAL(...) Hasbu::Utils::Logger::getLogger()->critical(__VA_ARGS__)

#elif defined(RELEASE)

#define HASBU_TRACE(...)
#define HASBU_DEBUG(...)
#define HASBU_INFO(...) Hasbu::Utils::Logger::getLogger()->info(__VA_ARGS__)
#define HASBU_WARNING(...) Hasbu::Utils::Logger::getLogger()->warn(__VA_ARGS__)
#define HASBU_ERROR(...) Hasbu::Utils::Logger::getLogger()->error(__VA_ARGS__)
#define HASBU_FATAL(...) Hasbu::Utils::Logger::getLogger()->critical(__VA_ARGS__)

#endif

#define HASBU_ASSERT(expr, message)                                                                          \
    if (expr) {                                                                                              \
        HASBU_FATAL("ASSERT - {}\n\t{}\n\tint file: {}\n\ton line: {}", #expr, message, __FILE__, __LINE__); \
        HASBU_BREAK;                                                                                         \
    }

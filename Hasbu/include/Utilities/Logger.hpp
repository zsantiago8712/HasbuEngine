#include <spdlog/logger.h>

namespace HasbuUtils {

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

#define HASBU_TRACE(...) HasbuUtils::Logger::getLogger()->trace(__VA_ARGS__)
#define HASBU_DEBUG(...) HasbuUtils::Logger::getLogger()->debug(__VA_ARGS__)
#define HASBU_INFO(...) HasbuUtils::Logger::getLogger()->info(__VA_ARGS__)
#define HASBU_WARNING(...) HasbuUtils::Logger::getLogger()->warn(__VA_ARGS__)
#define HASBU_ERROR(...) HasbuUtils::Logger::getLogger()->error(__VA_ARGS__)
#define HASBU_FATAL(...) HasbuUtils::Logger::getLogger()->critical(__VA_ARGS__)

#elif defined(RELEASE)

#define HASBU_TRACE(...)
#define HASBU_DEBUG(...)
#define HASBU_INFO(...) HasbuUtils::Logger::getLogger()->info(__VA_ARGS__)
#define HASBU_WARNING(...) HasbuUtils::Logger::getLogger()->warn(__VA_ARGS__)
#define HASBU_ERROR(...) HasbuUtils::Logger::getLogger()->error(__VA_ARGS__)
#define HASBU_FATAL(...) HasbuUtils::Logger::getLogger()->critical(__VA_ARGS__)

#endif

#define HASBU_ASSERT(expr, message)                                                                          \
    if (expr) {                                                                                              \
        HASBU_FATAL("ASSERT - {}\n\t{}\n\tint file: {}\n\ton line: {}", #expr, message, __FILE__, __LINE__); \
        HASBU_BREAK;                                                                                         \
    }

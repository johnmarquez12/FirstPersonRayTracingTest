#pragma once 

#include <spdlog/include/spdlog/spdlog.h>
#include <spdlog/include/spdlog/sinks/stdout_color_sinks.h>
#include <memory>

class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
            return coreLogger;
        }

        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
            return coreLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
};

#define CORE_ERROR(...)   Log::GetCoreLogger()->error(__VA_ARGS__);
#define CORE_WARN(...)    Log::GetCoreLogger()->warn(__VA_ARGS__);
#define CORE_INFO(...)    Log::GetCoreLogger()->info(__VA_ARGS__);
#define CORE_TRACE(...)   Log::GetCoreLogger()->trace(__VA_ARGS__);
#define CORE_FATAL(...)   Log::GetCoreLogger()->fatal(__VA_ARGS__);

#define CLIENT_ERROR(...) Log::GetClientLogger()->error(__VA_ARGS__);
#define CLIENT_WARN(...)  Log::GetClientLogger()->warn(__VA_ARGS__);
#define CLIENT_INFO(...)  Log::GetClientLogger()->info(__VA_ARGS__);
#define CLIENT_TRACE(...) Log::GetClientLogger()->trace(__VA_ARGS__);
#define CLIENT_FATAL(...) Log::GetClientLogger()->fatal(__VA_ARGS__);
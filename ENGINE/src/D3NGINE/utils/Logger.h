#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#ifndef D3G_UTILS_LOGGER_H
#define D3G_UTILS_LOGGER_H

namespace D3G {

	class Logger
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define D3G_CORE_TRACE(...)    ::D3G::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define D3G_CORE_INFO(...)     ::D3G::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define D3G_CORE_WARN(...)     ::D3G::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define D3G_CORE_ERROR(...)    ::D3G::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define D3G_CORE_CRITICAL(...) ::D3G::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define D3G_CORE_DEBUG(...)    ::D3G::Logger::GetCoreLogger()->debug(__VA_ARGS__)
// ClienD3Glog macros
#define D3G_TRACE(...)         ::D3G::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define D3G_INFO(...)          ::D3G::Logger::GetClientLogger()->info(__VA_ARGS__)
#define D3G_WARN(...)          ::D3G::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define D3G_ERROR(...)         ::D3G::Logger::GetClientLogger()->error(__VA_ARGS__)
#define D3G_CRITICAL(...)      ::D3G::Logger::GetClientLogger()->critical(__VA_ARGS__)
#define D3G_DEBUG(...)         ::D3G::Logger::GetClientLogger()->debug(__VA_ARGS__)

#endif

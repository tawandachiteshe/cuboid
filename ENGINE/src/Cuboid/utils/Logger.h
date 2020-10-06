#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Cuboid {

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
#define CUBOID_CORE_TRACE(...)    ::Cuboid::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CUBOID_CORE_INFO(...)     ::Cuboid::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CUBOID_CORE_WARN(...)     ::Cuboid::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CUBOID_CORE_ERROR(...)    ::Cuboid::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CUBOID_CORE_CRITICAL(...) ::Cuboid::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define CUBOID_CORE_DEBUG(...)    ::Cuboid::Logger::GetCoreLogger()->debug(__VA_ARGS__)
// ClienD3Glog macros				Cuboid
#define CUBOID_TRACE(...)         ::Cuboid::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define CUBOID_INFO(...)          ::Cuboid::Logger::GetClientLogger()->info(__VA_ARGS__)
#define CUBOID_WARN(...)          ::Cuboid::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define CUBOID_ERROR(...)         ::Cuboid::Logger::GetClientLogger()->error(__VA_ARGS__)
#define CUBOID_CRITICAL(...)      ::Cuboid::Logger::GetClientLogger()->critical(__VA_ARGS__)
#define CUBOID_DEBUG(...)         ::Cuboid::Logger::GetClientLogger()->debug(__VA_ARGS__)

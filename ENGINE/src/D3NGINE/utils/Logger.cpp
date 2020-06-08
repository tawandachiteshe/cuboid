#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace D3G {

	std::shared_ptr<spdlog::logger> D3G::Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> D3G::Logger::s_ClientLogger;

	void D3G::Logger::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>()); // @suppress("Invalid arguments") // @suppress("Symbol is not resolved") // @suppress("Type cannot be resolved")
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("D3G.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_CoreLogger = std::make_shared<spdlog::logger>("D3G", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

}


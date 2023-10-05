#include "logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>


std::shared_ptr<spdlog::logger> Logger::m_engineLogger;

void Logger::Init() {

    // sinks are out locations that the logger would forward things to
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // set a string pattern to pre every log line
    consoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %v%$");

    spdlog::sinks_init_list sinks = {consoleSink};

    // make the logger
    auto logger = std::make_shared<spdlog::logger>("hidden_logger", sinks.begin(), sinks.end());

    // set the lowest that the logger will generate for. 
    // this can be futhered filtered on the sink level
    logger->set_level(spdlog::level::trace);

    // set the level at messages should be immediately forwarded to sinks
    logger->flush_on(spdlog::level::trace);

    spdlog::register_logger(logger);


    /*
    Log Level Hiearchy
        Critical,
        Error,
        Warn,
        Info,
        Debug,
        Trace
    */
}

std::shared_ptr<spdlog::logger>& Logger::Get() {
    return m_engineLogger;
}

void Logger::Shutdown() {

}
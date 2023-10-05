#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <iostream>

class Logger {
    private:
        static std::shared_ptr<spdlog::logger> m_engineLogger;

    public:
        Logger() = default;
        ~Logger() = default;

        // Define the following for the engine to decide when to initialize and shutdown the logger
        static void Init();
        static void Shutdown();

        static std::shared_ptr<spdlog::logger>& Get();
        
};


// Set up preprocessor macros as guards to accessing the logging functions
// ... & __VA_ARGS__ are a way of accepting an unlimited number of arguements

#ifdef HIDDEN_CONFIG_DEBUG
    
    #define HIDDEN_TRACE(...)  Logger::Get()->trace(__VA_ARGS__)
    #define HIDDEN_INFO(...)   Logger::Get()->info(__VA_ARGS__)
    #define HIDDEN_WARN(...)   Logger::Get()->warn(__VA_ARGS__)
    #define HIDDEN_ERROR(...)  Logger::Get()->error(__VA_ARGS__)
    #define HIDDEN_FATAL(...)  Logger::Get()->fatal(__VA_ARGS__)

#else 

    #define HIDDEN_TRACE(...)  (void)0;
    #define HIDDEN_INFO(...)   (void)0;
    #define HIDDEN_WARN(...)   (void)0;
    #define HIDDEN_ERROR(...)  (void)0;
    #define HIDDEN_FATAL(...)  (void)0;
    

#endif
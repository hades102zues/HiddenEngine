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


// Define platform specific debugger breakpoints




// Set up preprocessor macros as guards to accessing the logging functions
// ... & __VA_ARGS__ are a way of accepting an unlimited number of arguements
#ifndef HIDDEN_CONFIG_RELEASE
    
    #define HIDDEN_TRACE(...)  if(Logger::Get()) { Logger::Get()->trace(__VA_ARGS__);}
    #define HIDDEN_DEBUG(...)  if(Logger::Get()) { Logger::Get()->debug(__VA_ARGS__);}
    #define HIDDEN_INFO(...)   if(Logger::Get()) { Logger::Get()->info(__VA_ARGS__);}
    #define HIDDEN_WARN(...)   if(Logger::Get()) { Logger::Get()->warn(__VA_ARGS__);}
    #define HIDDEN_ERROR(...)  if(Logger::Get()) { Logger::Get()->error(__VA_ARGS__);}
    #define HIDDEN_FATAL(...)  if(Logger::Get()) { Logger::Get()->critical(__VA_ARGS__);}
   
    #define HIDDEN_ASSERT(assert_condition, response_msg) if ((assert_condition)) {} else { HIDDEN_FATAL("Asserted {} :-  \n\tin file: {} \n\ton line: {} \n\thint: {} ", #assert_condition, __FILE__, __LINE__, response_msg);  }

#else 

    #define HIDDEN_TRACE(...)  (void)0;
    #define HIDDEN_DEBUG(...)  (void)0;
    #define HIDDEN_INFO(...)   (void)0;
    #define HIDDEN_WARN(...)   (void)0;
    #define HIDDEN_ERROR(...)  (void)0;
    #define HIDDEN_FATAL(...)  (void)0;
    #define HIDDEN_ASSERT(...) (void)0;
    

#endif
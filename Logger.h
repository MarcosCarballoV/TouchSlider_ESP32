#ifndef LOGGER_H
#define LOGGER_H

/*********************** EXTERNAL LIBRARIES **********************/

#include <Arduino.h>
#include <esp_log.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef CONFIG_LOGGER_COLORS    // Controlled by -D CONFIG_LOGGER_COLORS in platformio.ini
  #define LOGGER_COLOR_RED     "\e[31m" 
  #define LOGGER_COLOR_GREEN   "\e[32m" 
  #define LOGGER_COLOR_YELLOW  "\e[33m" 
  #define LOGGER_COLOR_BLUE    "\e[34m"
  #define LOGGER_COLOR_CYAN    "\e[36m" 
  #define LOGGER_COLOR_GRAY    "\e[37m" 
  #define LOGGER_COLOR_RESET   "\e[39m"
#else
  #define LOGGER_COLOR_RED     
  #define LOGGER_COLOR_GREEN   
  #define LOGGER_COLOR_YELLOW  
  #define LOGGER_COLOR_BLUE    
  #define LOGGER_COLOR_CYAN    
  #define LOGGER_COLOR_GRAY    
  #define LOGGER_COLOR_RESET
#endif

#define LOGER(format, ...)          log_e(LOGGER_COLOR_RED format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGEG(format, ...)          log_e(LOGGER_COLOR_GREEN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGEY(format, ...)          log_e(LOGGER_COLOR_YELLOW format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGEB(format, ...)          log_e(LOGGER_COLOR_BLUE format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGEC(format, ...)          log_e(LOGGER_COLOR_CYAN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGEGR(format, ...)         log_e(LOGGER_COLOR_GRAY format LOGGER_COLOR_RESET, ##__VA_ARGS__)

#define LOGWR(format, ...)          log_w(LOGGER_COLOR_RED format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGWG(format, ...)          log_w(LOGGER_COLOR_GREEN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGWY(format, ...)          log_w(LOGGER_COLOR_YELLOW format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGWB(format, ...)          log_w(LOGGER_COLOR_BLUE format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGWC(format, ...)          log_w(LOGGER_COLOR_CYAN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGWGR(format, ...)         log_w(LOGGER_COLOR_GRAY format LOGGER_COLOR_RESET, ##__VA_ARGS__)

#define LOGIR(format, ...)          log_i(LOGGER_COLOR_RED format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGIG(format, ...)          log_i(LOGGER_COLOR_GREEN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGIY(format, ...)          log_i(LOGGER_COLOR_YELLOW format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGIB(format, ...)          log_i(LOGGER_COLOR_BLUE format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGIC(format, ...)          log_i(LOGGER_COLOR_CYAN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGIGR(format, ...)         log_i(LOGGER_COLOR_GRAY format LOGGER_COLOR_RESET, ##__VA_ARGS__)

#define LOGDR(format, ...)          log_d(LOGGER_COLOR_RED format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGDG(format, ...)          log_d(LOGGER_COLOR_GREEN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGDY(format, ...)          log_d(LOGGER_COLOR_YELLOW format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGDB(format, ...)          log_d(LOGGER_COLOR_BLUE format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGDC(format, ...)          log_d(LOGGER_COLOR_CYAN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGDGR(format, ...)         log_d(LOGGER_COLOR_GRAY format LOGGER_COLOR_RESET, ##__VA_ARGS__)

#define LOGVR(format, ...)          log_v(LOGGER_COLOR_RED format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGVG(format, ...)          log_v(LOGGER_COLOR_GREEN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGVY(format, ...)          log_v(LOGGER_COLOR_YELLOW format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGVB(format, ...)          log_v(LOGGER_COLOR_BLUE format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGVC(format, ...)          log_v(LOGGER_COLOR_CYAN format LOGGER_COLOR_RESET, ##__VA_ARGS__)
#define LOGVGR(format, ...)         log_v(LOGGER_COLOR_GRAY format LOGGER_COLOR_RESET, ##__VA_ARGS__)

#endif
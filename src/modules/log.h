#ifndef _LOG_H
#define _LOG_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

typedef int (*pLogPrintf)(const char *format, va_list list);
#define LOG_PREFIX_MAX_LEN (64)

typedef enum{
	LOG_LE_EMPTY = 0,
	LOG_LE_DEBUG,
	LOG_LE_INFO,
	LOG_LE_WARING,
	LOG_LE_ERROR
}LOG_LEVEL_Typedef;

struct LogAttributes{
	bool _lable;	
	bool _append_n;	
	bool _append_r;	
	bool _trace_err;	
};

struct LogOpt{
	pLogPrintf pfun;
	LOG_LEVEL_Typedef level;
	int8_t prefix[LOG_PREFIX_MAX_LEN];
	struct LogAttributes atb;
};

extern struct LogOpt log_opt;

#define _LogPrintf(format, list){if(log_opt.pfun)\
								{log_printf("%s",log_opt.prefix);\
								log_opt.pfun(format, list);\
								if(log_opt.atb._append_n){log_printf("\n");}\
								if(log_opt.atb._append_r){log_printf("\r");}\
								}}

#define printf_debug(format, ...)  printf_level(LOG_LE_DEBUG,0, 0, format, ##__VA_ARGS__)
#define printf_info(format, ...)   printf_level(LOG_LE_INFO, 0, 0, format, ##__VA_ARGS__)
#define printf_waring(format, ...) printf_level(LOG_LE_WARING,0, 0, format, ##__VA_ARGS__)
#define printf_err(format, ...)    printf_level(LOG_LE_ERROR, __FILE__, __LINE__,format, ##__VA_ARGS__)
int8_t LogConfigure(const pLogPrintf pFun,
					const LOG_LEVEL_Typedef level,
					const int8_t *prefix,
					const bool lable,
					const bool n, 
					const bool r, 
					const bool trace_err);
void LogDestory(void);
int printf_level(LOG_LEVEL_Typedef level, 
				const char *file,
				const int line,
				const char *format, ...);
#endif



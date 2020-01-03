/* This file is part of stdplus.
 * 
 * 
 * stdplus is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * stdplus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 * 
 * You should have received a copy of the Lesser GNU General Public License
 * along with stdplus.  If not, see <https://www.gnu.org/licenses/>.
 */
/**
 * @file log.c
 * @brief 实现了日志信息的打印
 * 	支持添加前缀
 * 	支持添加标签
 * 	支持自定义打印结束符 \n\r
 * 	支持错误输出时打印TRACE信息跟踪出错位置
 * @author wangkai
 * @version v0.1
 * @date 2019-07-24
 */

#include "log.h"
#include <stdarg.h>
#include "FreeRTOS.h"
#include "task.h"

struct LogOpt log_opt;

int8_t LogConfigure(const pLogPrintf pFun,
			const LOG_LEVEL_Typedef level,
			const int8_t *prefix,
			const bool lable,
			const bool n, 
			const bool r, 
			const bool trace_err)
{
	if((!pFun)
	||(level > LOG_LE_ERROR))
		return -1;

	log_opt.pfun = pFun;
	log_opt.level = level;

	if(!prefix)	
		return 0;

	if(strlen((char *)prefix) > (LOG_PREFIX_MAX_LEN - 1))
			return -2;

	memset(log_opt.prefix, 0, sizeof(log_opt.prefix));
	strcat((char *)log_opt.prefix, (char *)prefix);

	memcpy(log_opt.prefix, prefix, strlen((char *)prefix)+1);
	log_opt.atb._lable = lable;
	log_opt.atb._append_n = n;
	log_opt.atb._append_r = r;
	log_opt.atb._trace_err= trace_err;
		
	return 0;
}

void LogDestory(void)
{
	memset(&log_opt, 0, sizeof(struct LogOpt));
}

static int log_printf(const char *format, ...)
{
	int r=0;
	va_list ParamList;

	va_start(ParamList, format);
	r = log_opt.pfun(format, ParamList);
	va_end(ParamList);
	return r;

}

int printf_level(LOG_LEVEL_Typedef level, 
				const char *file,
				const int line,
				const char *format, ...)
{
	va_list ParamList;


	
	if(log_opt.level <= level)
	{
		if(log_opt.atb._lable)
		{
			switch(level)
			{
				case LOG_LE_DEBUG:
					log_printf("<debug>");
					break;
				case LOG_LE_INFO:
					log_printf("<info>");
					break;
				case LOG_LE_WARING:
					log_printf("<waring>");
					break;
				case LOG_LE_ERROR:
					log_printf("<error>");
					break;
				default:
					break;
			}
		}
		va_start(ParamList, format);
		_LogPrintf(format, ParamList);
		va_end(ParamList);

		if((log_opt.atb._trace_err)&&
			(level == LOG_LE_ERROR))
		{
			log_printf("<error occur>%s:%d", file,line);
		}
	}

	return 0;
}


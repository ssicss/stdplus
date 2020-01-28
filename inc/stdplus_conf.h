#ifndef _STDPLUS_CONF_H
#define _STDPLUS_CONF_H


#define USE_PREVITE_INLINE


#define USE_EXTERN_LIB_METHOD
#define CALLOC_METHOD calloc
#define FREE_METHOD free
#define MEMCPY_METHOD memcpy



/****not need to modify blew****/
#ifndef CALLOC_METHOD
#define CALLOC_METHOD malloc
#endif

#ifndef FREE_METHOD
#define FREE_METHOD free
#endif

#ifndef MEMCPY_METHOD
#define MEMCPY_METHOD memcpy
#endif

#ifdef USE_EXTERN_LIB_METHOD
#if((!defined CALLOC_METHOD)||\
	(!defined FREE_METHOD)||\
	(!defined MEMCPY_METHOD)\
	) 
#error "You define use extern api, buf not defined detail, must fixd it"
#endif
#endif


#endif

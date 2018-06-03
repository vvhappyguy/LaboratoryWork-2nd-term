#ifndef __LOGGER_H__
#define __LOGGER_H__

enum LEVEL{LOG_INFO, LOG_WARN, LOG_ERROR};

#ifdef __cplusplus
extern "C" {
#endif

void logger( enum LEVEL l, const char* format, ...);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __LOGGER_H__

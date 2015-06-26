/***********************************************************************************************************************************
* Error check in C 
* 
* part 1
*   #include<errno.h>
*   1) errno in this library shows the error code for any 
*   kind of errors.
*   2) there are two useful functions: perror() and strerror()
*   perror() display string you pass to it and error information 
*   strerror() display error based on errno you pass to it
*
* part2 
*   how to use these MACROS?
*   MACROS can use variable argument after C99. 
*   #define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
*   1) __VA_ARGS__ is used to replace ...; ##__VA_ARGS__ is used to replace ,... (__VA_ARGS__ can not handle zero argument while )
*   while ##__VA_ARGS__ can)
*   2) __FILE__ displays file name and __LINE__ displays line number which are important in debug
***********************************************************************************************************************************/


#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif

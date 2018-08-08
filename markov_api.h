#ifndef PHP_MARKOV_API_H
#define PHP_MARKOV_API_H

#include <time.h>
#include <string.h>
#include <stdint.h>

#ifdef __cplusplus

#include "markovchain.h"

extern "C" {

#endif /* __cplusplus */

#ifndef MARKOV_API
#   if defined(_WIN32) || defined(_WIN64)
#       define MARKOV_API __declspec(dllimport)
#   else
#       define MARKOV_API extern
#   endif /* defined(_WIN32) || defined(_WIN64) */
#endif /* MARKOV_API */

#ifndef MARKOV_VERSION
#    define MARKOV_VERSION 12
#endif /* MARKOV_VERSION */

#define MARKOV_TRUE           (1)
#define MARKOV_FALSE          (0)

typedef void *MarkovHandle;

MARKOV_API int MarkovVersion();
MARKOV_API MarkovHandle MarkovCreate(const char *str, int nsize);
MARKOV_API void MarkovFree(MarkovHandle handle);
MARKOV_API void MarkovFreeText(char *text);
MARKOV_API char* MarkovGenerate(MarkovHandle handle, const char *start, const int width);
MARKOV_API int MarkovHas(MarkovHandle handle, const char *key);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PHP_MARKOV_API_H */

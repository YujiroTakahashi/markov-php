#ifndef PHP_MARKOV_H
#define PHP_MARKOV_H

#include "markov_api.h"

extern zend_module_entry markov_module_entry;
#define phpext_markov_ptr &markov_module_entry

#define PHP_MARKOV_VERSION	"0.1.0"

#ifdef PHP_WIN32
#	define PHP_EXTNAME_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_EXTNAME_API __attribute__ ((visibility("default")))
#else
#	define PHP_EXTNAME_API
#endif

#ifdef ZTS
#   include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(markov)
    char *dicpath;
ZEND_END_MODULE_GLOBALS(markov)

#define MARKOV_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(markov, v)

typedef struct {
    zend_object zo;
    MarkovHandle markov;
} php_markov_object;

static inline php_markov_object *php_markov_from_obj(zend_object *obj) {
	return (php_markov_object*)((char*)(obj) - XtOffsetOf(php_markov_object, zo));
}

#define Z_MARKOV_P(zv) php_markov_from_obj(Z_OBJ_P((zv)))

#if defined(ZTS) && defined(COMPILE_DL_MARKOV)
    ZEND_TSRMLS_CACHE_EXTERN()
#endif


#endif  /* PHP_MARKOV_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */

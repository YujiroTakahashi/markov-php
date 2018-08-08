#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_markov.h"
#include "main/SAPI.h"

#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "SAPI.h"

#include "markov_api.h"

ZEND_DECLARE_MODULE_GLOBALS(markov)

/* Handlers */
static zend_object_handlers markov_object_handlers;

/* Class entries */
zend_class_entry *php_markov_sc_entry;

/* {{{ proto void markov::__construct(String str, int nsize)
 */
PHP_METHOD(markov, __construct)
{
	php_markov_object *ft_obj;
	zval *object = getThis();
	char *word;
	size_t word_len;
	zend_long nsize = 10;

	ft_obj = Z_MARKOV_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s|l", &word, &word_len, &nsize)) {
		return;
	}
	ft_obj->markov = MarkovCreate((const char*)word, (const int)nsize);
}
/* }}} */

/* {{{ proto long markov::generate(String start, int width)
 */
PHP_METHOD(markov, generate)
{
	php_markov_object *ft_obj;
	zval *object = getThis();
	char *start;
	size_t start_len;
	zend_long width = 10;
	char *text;

	ft_obj = Z_MARKOV_P(object);

	if (FAILURE == zend_parse_parameters_throw(ZEND_NUM_ARGS(), "s|l", &start, &start_len, &width)) {
		return;
	}

	if (0 == MarkovHas(ft_obj->markov, (const char*)start)) {
		RETURN_FALSE;
	}

	text = MarkovGenerate(ft_obj->markov, (const char*)start, (const int)width);

	ZVAL_STRING(return_value, text);
	MarkovFreeText(text);
}
/* }}} */


/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_markov, 0, 0, 1)
	ZEND_ARG_INFO(0, word)
	ZEND_ARG_INFO(0, k)
ZEND_END_ARG_INFO()
/* }}} */


/* {{{ php_smarkov_class_methods */
static zend_function_entry php_markov_class_methods[] = {
	PHP_ME(markov, __construct,	arginfo_markov,	ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(markov, generate, 	arginfo_markov, ZEND_ACC_PUBLIC)

	PHP_FE_END
};
/* }}} */

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("markov.dicpath", "/tmp", PHP_INI_ALL, OnUpdateString, dicpath, zend_markov_globals, markov_globals)
PHP_INI_END()
/* }}} */

/* {{{ markov_init_globals
 */
static void markov_init_globals(zend_markov_globals *markov_globals)
{
}
/* }}} */

static void php_markov_object_free_storage(zend_object *object) /* {{{ */
{
	php_markov_object *intern = php_markov_from_obj(object);

	if (!intern) {
		return;
	}

	if (intern->markov) {
		MarkovFree(intern->markov);
		intern->markov = NULL;
	}

	zend_object_std_dtor(&intern->zo);
}
/* }}} */

static zend_object *php_markov_object_new(zend_class_entry *class_type) /* {{{ */
{
	php_markov_object *intern;

	/* Allocate memory for it */
	intern = ecalloc(1, sizeof(php_markov_object) + zend_object_properties_size(class_type));

	zend_object_std_init(&intern->zo, class_type);
	object_properties_init(&intern->zo, class_type);

	intern->zo.handlers = &markov_object_handlers;

	return &intern->zo;
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(markov)
{
	zend_class_entry ce;

	REGISTER_INI_ENTRIES();
	ZEND_INIT_MODULE_GLOBALS(markov, markov_init_globals, NULL);

	memcpy(&markov_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	/* Register markov Class */
	INIT_CLASS_ENTRY(ce, "markov", php_markov_class_methods);
	ce.create_object = php_markov_object_new;
	markov_object_handlers.offset = XtOffsetOf(php_markov_object, zo);
	markov_object_handlers.clone_obj = NULL;
	markov_object_handlers.free_obj = php_markov_object_free_storage;
	php_markov_sc_entry = zend_register_internal_class(&ce);


	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(markov)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(markov)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "markov support", "enabled");
	php_info_print_table_row(2, "markov module version", PHP_MARKOV_VERSION);
	php_info_print_table_row(2, "markov Library", MarkovVersion());
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION
*/
static PHP_GINIT_FUNCTION(markov)
{
	memset(markov_globals, 0, sizeof(*markov_globals));
}
/* }}} */

/* {{{ markov_module_entry
*/
zend_module_entry markov_module_entry = {
	STANDARD_MODULE_HEADER,
	"markov",
	NULL,
	PHP_MINIT(markov),
	PHP_MSHUTDOWN(markov),
	NULL,
	NULL,
	PHP_MINFO(markov),
	PHP_MARKOV_VERSION,
	PHP_MODULE_GLOBALS(markov),
	PHP_GINIT(markov),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_MARKOV
#	ifdef ZTS
		ZEND_TSRMLS_CACHE_DEFINE()
#	endif
	ZEND_GET_MODULE(markov)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

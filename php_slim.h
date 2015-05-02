/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_SLIM_H
#define PHP_SLIM_H

extern zend_module_entry slim_module_entry;
#define phpext_slim_ptr &slim_module_entry

#define PHP_SLIM_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_SLIM_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SLIM_API __attribute__ ((visibility("default")))
#else
#	define PHP_SLIM_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#define SLIM_VERSION "2.6.1"

#define EXTENSION_EXISTS(ext_name) \
		zend_hash_exists(&module_registry, )


#define SLIM_INIT_CLASS(class_ce, class_name, functions) \
		zend_class_entry ce;\
		INIT_CLASS_ENTRY(ce, class_name, functions);\
		class_ce = zend_register_internal_class(&ce TSRMLS_CC);

#define SLIM_MODULE_STARTUP(module) \
		ZEND_MODULE_STARTUP_N(module)(INIT_FUNC_ARGS_PASSTHRU);

#define GET_CLASS_PROPERTY(ce, property)  \
		zend_read_property(ce, getThis(), ZEND_STRL(property), 1 TSRMLS_CC);

void slim_debug(zval* data);

#define SLIM_STRACE(str, ...)    \
	{ php_printf("\nFile: %s \033[34m [Line:%d] \033[0m \nFunction: \033[31m [%s] \033[0m \nTraceInfo:\033[32m "str" \033[0m \n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); }


#ifdef ZTS
#define SLIM_G(v) TSRMG(slim_globals_id, zend_slim_globals *, v)
#else
#define SLIM_G(v) (slim_globals.v)
#endif

#endif


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

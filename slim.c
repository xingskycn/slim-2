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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_slim.h"
#include "slim_slim.h"
#include "slim_log.h"
#include "helper/set.h"


PHP_MINIT_FUNCTION(slim)
{
	SLIM_MODULE_STARTUP(slim_slim);
	SLIM_MODULE_STARTUP(slim_helper_set);
	SLIM_MODULE_STARTUP(slim_log);

	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(slim)
{
	return SUCCESS;
}



PHP_RINIT_FUNCTION(slim)
{
	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(slim)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(slim)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "slim support", "enabled");
	php_info_print_table_header(2, "slim version", SLIM_VERSION);
	php_info_print_table_end();
}


const zend_function_entry slim_functions[] = {
	PHP_FE_END
};


zend_module_entry slim_module_entry = {
	STANDARD_MODULE_HEADER,
	"slim",
	slim_functions,
	PHP_MINIT(slim),
	PHP_MSHUTDOWN(slim),
	PHP_RINIT(slim),	
	PHP_RSHUTDOWN(slim),
	PHP_MINFO(slim),
	PHP_SLIM_VERSION,
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_SLIM
ZEND_GET_MODULE(slim)
#endif

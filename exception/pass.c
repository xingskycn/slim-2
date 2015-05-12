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
#include "Zend/zend_exceptions.h"

zend_class_entry *slim_exception_pass_ce;

static zend_function_entry slim_exception_pass_methods[] = {
	NULL, NULL, NULL
};

ZEND_MINIT_FUNCTION(slim_exception_pass){
	SLIM_INIT_CLASS(slim_exception_pass_ce, "Slim\\Exception\\Pass", slim_exception_pass_methods);

	//class Pass extends \Exception
	zend_register_internal_class_ex(slim_exception_pass_ce, zend_exception_get_default(TSRMLS_CC), "Exception" TSRMLS_CC);

	return SUCCESS;
}


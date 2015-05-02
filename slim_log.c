/*
 * slim_log.c

 *
 *  Created on: 2015年4月30日
 *      Author: eagle
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_slim.h"
#include "slim_log.h"

zend_class_entry *slim_log_ce;

ZEND_METHOD(slim_log, __construct){

}

ZEND_METHOD(slim_log, getEnabled){

}

ZEND_METHOD(slim_log, setEnabled){

}

ZEND_METHOD(slim_log, setLevel){

}

ZEND_METHOD(slim_log, getLevel){

}

ZEND_METHOD(slim_log, setWriter){

}

ZEND_METHOD(slim_log, getWriter){

}

ZEND_METHOD(slim_log, isEnabled){

}

ZEND_METHOD(slim_log, debug){

}

ZEND_METHOD(slim_log, info){

}

ZEND_METHOD(slim_log, notice){

}

ZEND_METHOD(slim_log, warning){

}

ZEND_METHOD(slim_log, warn){

}

ZEND_METHOD(slim_log, error){

}

ZEND_METHOD(slim_log, critical){

}

ZEND_METHOD(slim_log, fatal){

}

ZEND_METHOD(slim_log, alert){

}

ZEND_METHOD(slim_log, emergency){

}

ZEND_METHOD(slim_log, log){

}

ZEND_METHOD(slim_log, write){

}

ZEND_METHOD(slim_log, interpolate){

}



static zend_function_entry slim_log_methods[] = {
	ZEND_ME(slim_log,    __construct,  	NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_ME(slim_log,    getEnabled,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    setEnabled,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    setLevel,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    getLevel,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    setWriter,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    getWriter,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    isEnabled,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    debug,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    info,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    notice,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    warning,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    warn,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    error,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    critical,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    fatal,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    alert,  		NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    emergency,  	NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    log,  			NULL,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_log,    write,  		NULL,   ZEND_ACC_PROTECTED)
	ZEND_ME(slim_log,    interpolate,  	NULL,   ZEND_ACC_PROTECTED)
	NULL, NULL, NULL
};

ZEND_MINIT_FUNCTION(slim_log){

	SLIM_INIT_CLASS(slim_log_ce, "Slim\\Log", slim_log_methods);

	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("EMERGENCY"), 	1 TSRMLS_CC);
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("ALERT"), 		2 TSRMLS_CC);
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("CRITICAL"), 	3 TSRMLS_CC);
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("FATAL"), 		3 TSRMLS_CC);  //DEPRECATED replace with CRITICAL
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("ERROR"), 		4 TSRMLS_CC);
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("WARN"), 		5 TSRMLS_CC);
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("NOTICE"), 		6 TSRMLS_CC);
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("INFO"), 		7 TSRMLS_CC);
	zend_declare_class_constant_long(slim_log_ce, ZEND_STRL("DEBUG"), 		8 TSRMLS_CC);


	zend_declare_property_null(slim_log_ce, ZEND_STRL("levels"), 	ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(slim_log_ce, ZEND_STRL("writer"), 	ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(slim_log_ce, ZEND_STRL("enabled"), 	ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(slim_log_ce, ZEND_STRL("level"), 	ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;
}


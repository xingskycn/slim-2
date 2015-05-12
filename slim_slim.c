/*
 * slim_slim.c
 *
 *  Created on: 2015年4月30日
 *      Author: eagle
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_slim.h"
#include "slim_slim.h"


zend_class_entry *slim_ce;


/**
 * __construct
 */
ZEND_METHOD(Slim, __construct)
{
	//__construct
	zval *user_settings;
	MAKE_STD_ZVAL(user_settings);
	array_init(user_settings);

	//default value of attribute apps
	zval *apps_array;
	MAKE_STD_ZVAL(apps_array);
	array_init(apps_array);
	add_next_index_long(apps_array, 100);

	//init default apps array
	zend_update_static_property(slim_ce, ZEND_STRL("apps"), apps_array);

	//default value of attribute apps hooks
	zval *hooks_default_val;
	MAKE_STD_ZVAL(hooks_default_val);
	array_init(hooks_default_val);

	zval *hooks_default_val_child;
	MAKE_STD_ZVAL(hooks_default_val_child);
	array_init(hooks_default_val_child);
	add_next_index_zval(hooks_default_val, hooks_default_val_child);

	zval *hooks_array;
	MAKE_STD_ZVAL(hooks_array);
	array_init(hooks_array);

	//init default hooks array(array())
	add_assoc_zval(hooks_array, "slim.before", hooks_default_val);
	add_assoc_zval(hooks_array, "slim.before.router", hooks_default_val);
	add_assoc_zval(hooks_array, "slim.before.dispatch", hooks_default_val);
	add_assoc_zval(hooks_array, "slim.after.dispatch", hooks_default_val);
	add_assoc_zval(hooks_array, "slim.after.router", hooks_default_val);
	add_assoc_zval(hooks_array, "slim.after", hooks_default_val);

	zend_update_property(slim_ce, getThis(), ZEND_STRL("hooks"), hooks_array);

	//Receive userSetting
	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &user_settings) == FAILURE){
		return ;
	}


	// Setup IoC container
	// Default environment
	// Default request
	// Default response
	// Default router
	// Default view
	// Default log writer
	// Default log
	// Default mode
	// Define default middleware stack
	// Make default if first instance
}

/**
 * Autoloader
 */
ZEND_METHOD(Slim, autoload)
{
	char *class_name;
	int class_name_len;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &class_name, &class_name_len) == FAILURE){
		return;
	}

	php_printf("TODO: Register namespace for user space.\n");

//	zval *tmp_apps;
//	tmp_apps = zend_read_static_property(slim_ce, ZEND_STRL("apps"), 0 TSRMLS_CC);
//
//	RETURN_ZVAL(tmp_apps, 1, 0);
}


static zend_function_entry slim_methods[] = {
	ZEND_ME(Slim,    __construct,  	NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_ME(Slim,    autoload,  	NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	NULL, NULL, NULL
};


ZEND_MINIT_FUNCTION(slim_slim){

	char *mcrypt_ext_name = "mcrypt";
	int mcrypt_ext_name_len = sizeof(mcrypt_ext_name);

	if(!zend_hash_exists(&module_registry, mcrypt_ext_name, mcrypt_ext_name_len + 1)){
		REGISTER_LONG_CONSTANT("MCRYPT_MODE_CBC", 0, CONST_CS | CONST_PERSISTENT);
		REGISTER_LONG_CONSTANT("MCRYPT_RIJNDAEL_256", 0, CONST_CS | CONST_PERSISTENT);
	}

	SLIM_REGISTER_INTERNAL_CLASS(slim_ce, "Slim\\Slim", slim_methods);

	//public
	zend_declare_property_null(slim_ce,"container", strlen("container"), ZEND_ACC_PUBLIC TSRMLS_CC);

	//protected
	zend_declare_property_null(slim_ce,"apps", strlen("apps"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);
	zend_declare_property_null(slim_ce,"name", strlen("name"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(slim_ce,"middleware", strlen("middleware"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(slim_ce,"error", strlen("error"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(slim_ce,"notFound", strlen("notFound"), ZEND_ACC_PROTECTED TSRMLS_CC);
	zend_declare_property_null(slim_ce,"hooks", strlen("hooks"), ZEND_ACC_PROTECTED TSRMLS_CC);

	//const
	zend_declare_class_constant_string(slim_ce, "VERSION", strlen("VERSION"), SLIM_VERSION TSRMLS_CC);

	return SUCCESS;
}


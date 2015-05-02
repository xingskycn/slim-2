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
#include "Helper/Set.h"

#include "zend_interfaces.h"

zend_class_entry *slim_helper_set_ce;


PHP_METHOD(slim_helper_set, __construct)
{
	zval *items;
	MAKE_STD_ZVAL(items);
	array_init(items);

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &items) == FAILURE){
		return;
	}

	zval *data_array;
	MAKE_STD_ZVAL(data_array);
	array_init(data_array);
	zend_update_property(slim_helper_set_ce, getThis(), ZEND_STRL("data"), data_array);

	//$this->replace($items);
	if(zend_hash_num_elements(Z_ARRVAL_P(items)) > 0){
		zend_call_method(&getThis(), slim_helper_set_ce, NULL, ZEND_STRL("replace"), NULL, 1, items, NULL TSRMLS_DC);
	}
}


PHP_METHOD(slim_helper_set, offsetExists)
{
	zval *index;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &index) == FAILURE) {
		return;
	}

	RETURN_BOOL(1);
}

PHP_METHOD(slim_helper_set, offsetGet)
{

}

PHP_METHOD(slim_helper_set, offsetSet)
{

}

PHP_METHOD(slim_helper_set, offsetUnset)
{

}


PHP_METHOD(slim_helper_set, normalizeKey)
{
	zval *key;
	MAKE_STD_ZVAL(key);

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key) == FAILURE){
		RETURN_FALSE;
	}

	RETURN_ZVAL(key, 0, 0);
}

PHP_METHOD(slim_helper_set, set)
{
	php_printf("in\n");

//	zval *key, *value, *data, *normalized_key;
//	MAKE_STD_ZVAL(key);
//	MAKE_STD_ZVAL(value);
//
//	if(zend_parse_parameters(ZEND_NUM_ARGS()TSRMLS_CC, "zz", &key, &value) == FAILURE){
//		RETURN_FALSE;
//	}
//
//	//get $this->data
//	data = zend_read_property(slim_helper_set_ce, getThis(), ZEND_STRL("data"), 1 TSRMLS_CC);
//
//	MAKE_STD_ZVAL(normalized_key);
//	//$this->normalizeKey($key)
//	zend_call_method(&getThis(), slim_helper_set_ce, NULL, ZEND_STRL("normalizekey"), &normalized_key, 1, key, NULL TSRMLS_DC);
//
//	if(!normalized_key){
//		RETURN_FALSE;
//	}
//
//	switch(Z_TYPE_P(normalized_key)){
//		case IS_LONG:
//			php_printf("num_index: %ld\n", Z_LVAL_P(normalized_key));
//
//			Z_ADDREF_P(value);
//			add_index_zval(data, Z_LVAL_P(normalized_key), value);
//
//			RETVAL_TRUE;
//			break;
//		case IS_STRING:
//			php_printf("str_index: %s\n", Z_STRVAL_P(normalized_key));
//			php_printf("value: %s \n", Z_STRVAL_P(value));
//
//			Z_ADDREF_P(value);
//			add_assoc_zval(data, Z_LVAL_P(normalized_key), value);
//
//			RETVAL_TRUE;
//			break;
//		default:
//			RETVAL_FALSE;
//	}

}

void debug(zval* data) {
    zval *function_name, *return_value;
    MAKE_STD_ZVAL(function_name);
    MAKE_STD_ZVAL(return_value);

    ZVAL_STRING(function_name, "var_dump", 1);

    zval* params = {data};

    call_user_function(CG(function_table), NULL, function_name, return_value, 1, &params TSRMLS_CC);
}

PHP_METHOD(slim_helper_set, replace)
{
	zval *items;
	int key_type;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &items) == FAILURE){
		RETURN_FALSE;
	}

	char *str_index;
	ulong num_index;

	HashTable *items_ht = Z_ARRVAL_P(items);

	zval **ppzval;

	zval *key_pzval;
	MAKE_STD_ZVAL(key_pzval);


	zval* params[2];
	params[0] = key_pzval;


	zval *set_method_name;
	zval *retval, *zvp;

	//INIT_ZVAL(set_method_name);
	MAKE_STD_ZVAL(set_method_name);
	MAKE_STD_ZVAL(retval);
	ZVAL_STRING(set_method_name, "set", 0); // $this->set(key, value);

	//call_user_function(NULL, &getThis(), set_method_name, retval, 2, params);

	zend_hash_internal_pointer_reset(items_ht);
	while(zend_hash_get_current_data(items_ht, (void **)&ppzval) == SUCCESS){

		zend_hash_get_current_key(items_ht, &str_index, &num_index, 0);  // get array key
		zend_hash_get_current_data(items_ht, (void **)&ppzval); // get array value

		key_type = zend_hash_get_current_key_type(items_ht);


		if( HASH_KEY_IS_LONG == key_type ){

			Z_LVAL_P(key_pzval) = num_index;
			Z_TYPE_P(key_pzval) = IS_LONG;

		} else if( HASH_KEY_IS_STRING == key_type ){

			Z_STRVAL_P(key_pzval) = str_index;
			Z_TYPE_P(key_pzval) = IS_STRING;

		} else {
			zend_hash_move_forward(items_ht);
			continue;
		}

		debug(*ppzval);

		params[0] = key_pzval;

		add_index_zval(params, 0, key_pzval);

		zvp = *ppzval;

		debug(zvp);

		params[1] = zvp;

		debug(params);

		call_user_function(NULL, &getThis(), set_method_name, retval, 2, params TSRMLS_CC);
		//zend_call_method(&getThis(), slim_helper_set_ce, NULL, ZEND_STRL("set"), NULL, 2, key_pzval, *ppzval TSRMLS_DC);

		zend_hash_move_forward(items_ht);
	}

	zend_hash_internal_pointer_reset(items_ht);
}


ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_offset_exists, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_offset_get, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_offset_set, 0, 0, 2)
	ZEND_ARG_INFO(0, offset)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_offset_unset, 0, 0, 1)
	ZEND_ARG_INFO(0, offset)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_set, 0, 0, 2)
ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_replace, 0, 0, 1)
	ZEND_ARG_INFO(0, items)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_normalize_key, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

static zend_function_entry slim_helper_set_methods[] = {
	ZEND_ME(slim_helper_set,    __construct,  	NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_ME(slim_helper_set,    offsetExists,  	slim_helper_set_offset_exists,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    offsetGet,  	slim_helper_set_offset_get,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    offsetSet,  	slim_helper_set_offset_set,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    offsetUnset,  	slim_helper_set_offset_unset,   ZEND_ACC_PUBLIC)

	ZEND_ME(slim_helper_set,    set,  			slim_helper_set_set,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    replace,  		slim_helper_set_replace,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    normalizeKey,  	slim_helper_set_normalize_key,   ZEND_ACC_PUBLIC)
	NULL, NULL, NULL
};


ZEND_MINIT_FUNCTION(slim_helper_set){

	SLIM_INIT_CLASS(slim_helper_set_ce, "Slim\\Helper\\Set", slim_helper_set_methods);

	zend_class_implements(slim_helper_set_ce TSRMLS_CC, 1, zend_ce_arrayaccess);

	zend_declare_property_null(slim_helper_set_ce, ZEND_STRL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;
}




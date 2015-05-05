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
#include "helper/set.h"

#include "zend_interfaces.h"
#include "ext/spl/spl_iterators.h"
#include "ext/spl/spl_array.h"

zend_class_entry *slim_helper_set_ce;

/**
 * Constructor
 */
PHP_METHOD(slim_helper_set, __construct)
{
	zval *items, *data_array, *function_name, *retval;
	zval *params[1];

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|z", &items) == FAILURE){
		return;
	}

	MAKE_STD_ZVAL(data_array);
	array_init(data_array);
	zend_update_property(slim_helper_set_ce, getThis(), ZEND_STRL("data"), data_array);

	//$this->replace($items);
	if(zend_hash_num_elements(Z_ARRVAL_P(items)) > 0){

		MAKE_STD_ZVAL(function_name);
		ZVAL_STRING(function_name, "replace", 0);
		params[0] = items;

		call_user_function(NULL, &getThis(), function_name, retval, 1, params TSRMLS_CC);
	}
}


PHP_METHOD(slim_helper_set, offsetExists)
{
	char *key_str;
	ulong key_len;
	zval *key, *data;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key_str, key_len) == FAILURE) {
		return;
	}

	MAKE_STD_ZVAL(key);
	ZVAL_STRING(key, key_str, 0);

	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	if(zend_hash_exists(Z_ARRVAL_P(data), key_str, key_len + 1)){
		RETURN_TRUE;
	}

	RETURN_FALSE;
}


PHP_METHOD(slim_helper_set, offsetGet)
{
	char *offset;
	uint offset_len;
	zval **ppzval, *data;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &offset, &offset_len) == FAILURE){
		return;
	}

	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	if(IS_ARRAY == Z_TYPE_P(data) ){
		if(zend_hash_find(Z_ARRVAL_P(data), offset, offset_len +1, (void **)&ppzval) == SUCCESS){
			RETURN_ZVAL(*ppzval, 1, 0);
		}
	}

	RETURN_NULL();
}


PHP_METHOD(slim_helper_set, offsetSet)
{
	char *offset;
	uint offset_len;
	zval *pzval, *data;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz", &offset, &offset_len, &pzval) == FAILURE){
		return;
	}

	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	Z_ADDREF_P(pzval);
	zend_hash_update(Z_ARRVAL_P(data), offset, offset_len + 1, (void *) &pzval, sizeof(zval *), NULL);

	RETURN_TRUE;
}


PHP_METHOD(slim_helper_set, offsetUnset)
{
	char *offset;
	uint offset_len;
	zval *pzval, *data;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &offset, &offset_len) == FAILURE){
		return;
	}

	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	zend_hash_del(Z_ARRVAL_P(data), offset, offset_len + 1);
}


PHP_METHOD(slim_helper_set, normalizeKey)
{
	zval *key;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &key) == FAILURE){
		RETURN_FALSE;
	}

	RETURN_ZVAL(key, 1, 0);
}


PHP_METHOD(slim_helper_set, set)
{
	char *key_str;
	ulong key_len;

	zval *key_pval, *value, *data;

	if(zend_parse_parameters(ZEND_NUM_ARGS()TSRMLS_CC, "sz", &key_str, &key_len, &value TSRMLS_CC) == FAILURE){
		RETURN_FALSE;
	}

	MAKE_STD_ZVAL(key_pval);
	ZVAL_STRING(key_pval, key_str, 1);

	zval *params[] = {key_pval};

	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	INIT_CALL_CLASS_USER_FUNCTION_PARAMS("normalizekey", function_name, retval_ptr);
	if(CALL_CLASS_USER_FUNCTION(function_name, retval_ptr, params) == SUCCESS){
		//dump_zval(retval_ptr);
		add_assoc_zval(data, Z_STRVAL_P(retval_ptr), value);
	}

	RETURN_TRUE;
}


PHP_METHOD(slim_helper_set, get)
{
	char *key_str;
	ulong key_len;

	zval *key_pzval, *_default, *data;
	zval **ppzval;
	zval *params_1[1], *params_2[2];

	zval *normalizekey_fun_name,  	*normalizekey_retval_ptr,
		 *method_exists_fun_name,	*method_exists_retval_ptr,
		 *has_fun_name, 			*has_retval_ptr,
		 *__invoke_fun_name,		*__invoke_retval_ptr;

	MAKE_STD_ZVAL(_default);
	Z_TYPE_P(_default) = IS_NULL;

	MAKE_STD_ZVAL(normalizekey_fun_name);
	MAKE_STD_ZVAL(normalizekey_retval_ptr);
	ZVAL_STRING(normalizekey_fun_name, "normalizekey", 0);

	MAKE_STD_ZVAL(method_exists_fun_name);
	MAKE_STD_ZVAL(method_exists_retval_ptr);
	ZVAL_STRING(method_exists_fun_name, "method_exists", 0);

	MAKE_STD_ZVAL(has_fun_name);
	MAKE_STD_ZVAL(has_retval_ptr);
	ZVAL_STRING(has_fun_name, "has", 0);

	MAKE_STD_ZVAL(__invoke_fun_name);
	MAKE_STD_ZVAL(__invoke_retval_ptr);
	ZVAL_STRING(__invoke_fun_name, "__invoke", 0);

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|z", &key_str, &key_len, &_default) == FAILURE){
		return;
	}

	MAKE_STD_ZVAL(key_pzval);
	ZVAL_STRING(key_pzval, key_str, 1);
	params_1[0] = key_pzval;

	call_user_function(NULL, &getThis(), has_fun_name, has_retval_ptr, 1, params_1 TSRMLS_CC);

#if ZEND_DEBUG
	if(IS_NULL == Z_TYPE_P(has_retval_ptr)){
		zend_error(E_WARNING, "Slim\\Helper\\Set::has() expects return value to be boolean, NULL given");
	}
#endif

	convert_to_boolean(has_retval_ptr);
	if(Z_BVAL_P(has_retval_ptr)){	// call $this->has() method return true

		//$this->normalizeKey($key);
		CALL_CLASS_USER_FUNCTION(normalizekey_fun_name, normalizekey_retval_ptr, params_1);

		data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

		//got it
		if(zend_hash_find(Z_ARRVAL_P(data), Z_STRVAL_P(normalizekey_retval_ptr), Z_STRLEN_P(normalizekey_retval_ptr) + 1, (void **) &ppzval) == SUCCESS){

			if(IS_OBJECT == Z_TYPE_PP(ppzval)){

				//SLIM_STRACE("Slim\\Helper\\Set::get(\"%s\") is Object", Z_STRVAL_P(normalizekey_retval_ptr));

				params_2[0] = *ppzval;
				params_2[1] = __invoke_fun_name;
				call_user_function(CG(function_table), NULL, method_exists_fun_name, method_exists_retval_ptr, 2, params_2 TSRMLS_CC);

				convert_to_boolean(method_exists_retval_ptr);
				if(Z_BVAL_P(method_exists_retval_ptr)){ // call method_exists() return true
					params_1[0] = getThis();
					call_user_function(NULL, ppzval, __invoke_fun_name, __invoke_retval_ptr, 1, params_1 TSRMLS_CC);

					RETURN_ZVAL(__invoke_retval_ptr, 0, 0);

					//SLIM_STRACE("Slim\\Helper\\Set::get(\"%s\") has __invoke method", Z_STRVAL_P(normalizekey_retval_ptr));

				}
			}
		}




		RETURN_ZVAL(*ppzval, 0, 0);
	}

	RETURN_ZVAL(_default, 0, 0);
}


PHP_METHOD(slim_helper_set, has)
{
	char *key_str;
	ulong key_len;
	zval *data;

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key_str, &key_len) == FAILURE){
		return;
	}

	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	if(zend_hash_exists(Z_ARRVAL_P(data), key_str, key_len + 1)){
		RETURN_TRUE;
	} else {
		RETURN_FALSE;
	}
}

PHP_METHOD(slim_helper_set, replace)
{
	zval *items, *key_pzval, *key, *value, *function_name, *retval, *tmp_ppzval;
	zval **ppzval;

	int key_type;
	char *str_index;
	ulong num_index;

	HashTable *items_ht;

	MAKE_STD_ZVAL(retval);
	MAKE_STD_ZVAL(function_name);
	ZVAL_STRING(function_name, "set", 1);

	if(zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &items) == FAILURE){
		RETURN_FALSE;
	}

	items_ht = Z_ARRVAL_P(items);
	MAKE_STD_ZVAL(key_pzval);

	zval *params[2] = { key_pzval };

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
			zend_error(E_WARNING, "invalid index type, expects string");
			zend_hash_move_forward(items_ht);
			continue;
		}

		tmp_ppzval = *ppzval;
		zval_copy_ctor(tmp_ppzval);
		INIT_PZVAL(tmp_ppzval);
		params[1] = tmp_ppzval;

		call_user_function(NULL, &getThis(), function_name, retval, 2, params);

		zend_hash_move_forward(items_ht);
	}

	zend_hash_internal_pointer_reset(items_ht);
}


PHP_METHOD(slim_helper_set, count)
{
	zval* data;
	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	RETURN_LONG(zend_hash_num_elements(Z_ARRVAL_P(data)));
}


PHP_METHOD(slim_helper_set, getIterator)
{
	zval *data, *retval, *function_name;
	MAKE_STD_ZVAL(function_name);
	ZVAL_STRING(function_name, "__construct", 1);

	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");

	zval *params[1] = { data };

	object_init_ex(return_value, spl_ce_ArrayIterator);
	call_user_function(NULL, &return_value, function_name, retval, 1, params);
}

/**
 * $this->all();
 */
PHP_METHOD(slim_helper_set, all)
{
	zval *data;
	data = GET_CLASS_PROPERTY(slim_helper_set_ce, "data");
	RETURN_ZVAL(data, 1, 0);
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

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_get, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, _default)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_has, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_replace, 0, 0, 1)
	ZEND_ARG_INFO(0, items)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_normalize_key, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_count, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_get_iterator, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(slim_helper_set_get_all, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry slim_helper_set_methods[] = {
	ZEND_ME(slim_helper_set,    __construct,  	NULL,   						ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	ZEND_ME(slim_helper_set,    offsetExists,  	slim_helper_set_offset_exists,	ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    offsetGet,  	slim_helper_set_offset_get,   	ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    offsetSet,  	slim_helper_set_offset_set,   	ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    offsetUnset,  	slim_helper_set_offset_unset,   ZEND_ACC_PUBLIC)

	ZEND_ME(slim_helper_set,    set,  			slim_helper_set_set,   			ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    get,  			slim_helper_set_get,   			ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    has,  			slim_helper_set_has,   			ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    replace,  		slim_helper_set_replace,   		ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    normalizeKey,  	slim_helper_set_normalize_key,	ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    count,  		slim_helper_set_count,   		ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    getIterator,  	slim_helper_set_get_iterator,   ZEND_ACC_PUBLIC)
	ZEND_ME(slim_helper_set,    all,  			slim_helper_set_get_all,   		ZEND_ACC_PUBLIC)
	NULL, NULL, NULL
};


ZEND_MINIT_FUNCTION(slim_helper_set){
	SLIM_INIT_CLASS(slim_helper_set_ce, "Slim\\Helper\\Set", slim_helper_set_methods);

	// implements ArrayAccess
	zend_class_implements(slim_helper_set_ce TSRMLS_CC, 1, zend_ce_arrayaccess);

	zend_class_implements(slim_helper_set_ce TSRMLS_CC, 1, spl_ce_Countable);
	zend_class_implements(slim_helper_set_ce TSRMLS_CC, 1, zend_ce_aggregate);

	zend_declare_property_null(slim_helper_set_ce, ZEND_STRL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;
}


/*
 * set.h
 *
 *  Created on: 2015年5月2日
 *      Author: eagle
 */

#ifndef EXT_SLIM_HELPER_SET_H_
#define EXT_SLIM_HELPER_SET_H_


ZEND_MINIT_FUNCTION(slim_helper_set);

#define INIT_DATA(data) \
        data = zend_read_property(slim_helper_set_ce, getThis(), ZEND_STRL("data"), 1 TSRMLS_CC);


#define OFFSET_FORWARD_ONE_PARAMS(_method) \
		zval *pzval, *function_name, *params[1]; \
		char *key_str; \
		ulong key_len; \
		\
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &key_str, &key_len) == FAILURE) { \
			return; \
		} \
		\
		MAKE_STD_ZVAL(function_name); \
		ZVAL_STRING(function_name, _method, 0); \
		\
		MAKE_STD_ZVAL(pzval); \
		ZVAL_STRING(pzval, key_str, 0); \
		params[0] = pzval; \
		call_user_function(NULL, &getThis(), function_name, return_value, 1, params TSRMLS_CC); \
		\
		efree(function_name); \
		efree(pzval);


#endif /* EXT_SLIM_HELPER_SET_H_ */

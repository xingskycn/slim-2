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



#endif /* EXT_SLIM_HELPER_SET_H_ */

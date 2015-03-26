
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/object.h"
#include "kernel/exit.h"


/**
 * Exception class.
 *
 * @package     Ice/Exception
 * @category    Error
 * @author      Ice Team
 * @copyright   (c) 2014-2015 Ice Team
 * @license     http://iceframework.org/license
 */
ZEPHIR_INIT_CLASS(Ice_Exception) {

	ZEPHIR_REGISTER_CLASS_EX(Ice, Exception, ice, exception, zend_exception_get_default(TSRMLS_C), ice_exception_method_entry, 0);

	return SUCCESS;

}

/**
 * Creates a new exception.
 * Translate exception's message using the [I18n] class.
 *
 * @param mixed message Error message
 * @param mixed code The exception code
 * @param Exception previous Previous exception
 */
PHP_METHOD(Ice_Exception, __construct) {

	zval *_9 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_2 = NULL, *_6 = NULL, *_7 = NULL;
	zval *message = NULL, *code = NULL, *previous = NULL, *di = NULL, *values = NULL, *str = NULL, _1 = zval_used_for_init, *_3 = NULL, *_4 = NULL, *_5 = NULL, *_8 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &message, &code, &previous);

	if (!message) {
		ZEPHIR_INIT_VAR(message);
		ZVAL_STRING(message, "", 1);
	} else {
		ZEPHIR_SEPARATE_PARAM(message);
	}
	if (!code) {
		ZEPHIR_INIT_VAR(code);
		ZVAL_LONG(code, 0);
	}
	if (!previous) {
		previous = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_CALL_CE_STATIC(&di, ice_di_ce, "fetch", &_0);
	zephir_check_call_status();
	if (Z_TYPE_P(message) == IS_ARRAY) {
		ZEPHIR_SINIT_VAR(_1);
		ZVAL_LONG(&_1, 1);
		ZEPHIR_CALL_FUNCTION(&values, "array_slice", &_2, message, &_1);
		zephir_check_call_status();
		ZEPHIR_OBS_VAR(str);
		zephir_array_fetch_long(&str, message, 0, PH_NOISY, "ice/exception.zep", 32 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(values);
		ZVAL_NULL(values);
		ZEPHIR_CPY_WRT(str, message);
	}
	ZEPHIR_INIT_VAR(_4);
	ZVAL_STRING(_4, "i18n", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_3, di, "has", NULL, _4);
	zephir_check_temp_parameter(_4);
	zephir_check_call_status();
	if (zephir_is_true(_3)) {
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_STRING(_4, "i18n", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_5, di, "get", NULL, _4);
		zephir_check_temp_parameter(_4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&message, _5, "translate", NULL, str, values);
		zephir_check_call_status();
	} else if (Z_TYPE_P(values) == IS_ARRAY) {
		ZEPHIR_INIT_NVAR(_4);
		zephir_array_keys(_4, values TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_1);
		ZVAL_STRING(&_1, "is_string", 0);
		ZEPHIR_CALL_FUNCTION(&_5, "array_filter", &_6, _4, &_1);
		zephir_check_call_status();
		if (zephir_fast_count_int(_5 TSRMLS_CC)) {
			ZEPHIR_CALL_FUNCTION(&message, "strtr", &_7, str, values);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_VAR(_8);
			ZEPHIR_SINIT_NVAR(_1);
			ZVAL_STRING(&_1, "sprintf", 0);
			ZEPHIR_CALL_USER_FUNC_ARRAY(_8, &_1, message);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(message, _8);
		}
	}
	zephir_get_strval(_9, message);
	ZEPHIR_INIT_NVAR(_8);
	ZVAL_LONG(_8, zephir_get_intval(code));
	ZEPHIR_CALL_PARENT(NULL, ice_exception_ce, this_ptr, "__construct", NULL, _9, _8, previous);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * PHP error handler, converts all errors into ErrorExceptions. This handler respects error_reporting settings.
 *
 * @throws ErrorException
 * @return true
 */
PHP_METHOD(Ice_Exception, errorHandler) {

	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *context = NULL;
	zval *message = NULL, *file = NULL;
	zval *code_param = NULL, *message_param = NULL, *file_param = NULL, *line_param = NULL, *context_param = NULL, *_0 = NULL, *_2, *_3, *_4, *_5;
	int code, line, ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 3, &code_param, &message_param, &file_param, &line_param, &context_param);

	code = zephir_get_intval(code_param);
	zephir_get_strval(message, message_param);
	if (!file_param) {
		ZEPHIR_INIT_VAR(file);
		ZVAL_EMPTY_STRING(file);
	} else {
		zephir_get_strval(file, file_param);
	}
	if (!line_param) {
		line = 0;
	} else {
		line = zephir_get_intval(line_param);
	}
	if (!context_param) {
		ZEPHIR_INIT_VAR(context);
		array_init(context);
	} else {
		zephir_get_arrval(context, context_param);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "error_reporting", &_1);
	zephir_check_call_status();
	if (((int) (zephir_get_numberval(_0)) & code)) {
		ZEPHIR_INIT_VAR(_2);
		object_init_ex(_2, zephir_get_internal_ce(SS("errorexception") TSRMLS_CC));
		ZEPHIR_INIT_VAR(_3);
		ZVAL_LONG(_3, code);
		ZEPHIR_INIT_VAR(_4);
		ZVAL_LONG(_4, 0);
		ZEPHIR_INIT_VAR(_5);
		ZVAL_LONG(_5, line);
		ZEPHIR_CALL_METHOD(NULL, _2, "__construct", NULL, message, _3, _4, file, _5);
		zephir_check_call_status();
		zephir_throw_exception_debug(_2, "ice/exception.zep", 64 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_MM_BOOL(1);

}

/**
 * Inline exception handler, displays the error message, source of the exception, and the stack trace of the error.
 *
 * @param Exception $e
 * @return void
 */
PHP_METHOD(Ice_Exception, handler) {

	zval *_2;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *e, *_0, *_1, *_3 = NULL, _4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &e);



	ZEPHIR_INIT_VAR(_0);
	ZEPHIR_INIT_VAR(_1);
	zephir_get_called_class(_1 TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	array_init_size(_2, 4);
	ZEPHIR_CALL_METHOD(&_3, e, "getmessage", NULL);
	zephir_check_call_status();
	zephir_array_fast_append(_2, _3);
	ZEPHIR_CALL_METHOD(&_3, e, "getcode", NULL);
	zephir_check_call_status();
	zephir_array_fast_append(_2, _3);
	zephir_array_fast_append(_2, e);
	ZEPHIR_LAST_CALL_STATUS = zephir_create_instance_params(_0, _1, _2 TSRMLS_CC);
	zephir_check_call_status();
	ZEPHIR_SINIT_VAR(_4);
	ZVAL_LONG(&_4, 1);
	zephir_exit(&_4);
	ZEPHIR_MM_RESTORE();
	ZEPHIR_MM_RESTORE();

}

/**
 * Catches errors that are not caught by the error handler, such as E_PARSE.
 *
 * @return  void
 */
PHP_METHOD(Ice_Exception, shutdownHandler) {

	zval *_3;
	zend_bool _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL, *_5 = NULL, *_6 = NULL;
	zval *e = NULL, *_2, *_4 = NULL, *_7, *_8, *_9, *_10, *_11, _12;

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(&e, "error_get_last", &_0);
	zephir_check_call_status();
	_1 = Z_TYPE_P(e) == IS_ARRAY;
	if (_1) {
		zephir_array_fetch_string(&_2, e, SL("type"), PH_NOISY | PH_READONLY, "ice/exception.zep", 93 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_3);
		array_init_size(_3, 4);
		ZEPHIR_INIT_VAR(_4);
		ZVAL_LONG(_4, 4);
		zephir_array_fast_append(_3, _4);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, 1);
		zephir_array_fast_append(_3, _4);
		ZEPHIR_INIT_NVAR(_4);
		ZVAL_LONG(_4, 256);
		zephir_array_fast_append(_3, _4);
		_1 = zephir_fast_in_array(_2, _3 TSRMLS_CC);
	}
	if (_1) {
		ZEPHIR_CALL_FUNCTION(NULL, "ob_get_level", &_5);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(NULL, "ob_clean", &_6);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(_4);
		object_init_ex(_4, zephir_get_internal_ce(SS("errorexception") TSRMLS_CC));
		zephir_array_fetch_string(&_7, e, SL("message"), PH_NOISY | PH_READONLY, "ice/exception.zep", 98 TSRMLS_CC);
		zephir_array_fetch_string(&_8, e, SL("type"), PH_NOISY | PH_READONLY, "ice/exception.zep", 98 TSRMLS_CC);
		zephir_array_fetch_string(&_9, e, SL("file"), PH_NOISY | PH_READONLY, "ice/exception.zep", 98 TSRMLS_CC);
		zephir_array_fetch_string(&_10, e, SL("line"), PH_NOISY | PH_READONLY, "ice/exception.zep", 98 TSRMLS_CC);
		ZEPHIR_INIT_VAR(_11);
		ZVAL_LONG(_11, 0);
		ZEPHIR_CALL_METHOD(NULL, _4, "__construct", NULL, _7, _8, _11, _9, _10);
		zephir_check_call_status();
		ZEPHIR_CALL_SELF(NULL, "handler", NULL, _4);
		zephir_check_call_status();
		ZEPHIR_SINIT_VAR(_12);
		ZVAL_LONG(&_12, 1);
		zephir_exit(&_12);
		ZEPHIR_MM_RESTORE();
	}
	ZEPHIR_MM_RESTORE();

}


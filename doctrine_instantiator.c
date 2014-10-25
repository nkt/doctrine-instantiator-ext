
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_doctrine_instantiator.h"

#ifdef HAVE_SPL
#include "ext/spl/spl_exceptions.h"
#endif

#include "zend.h"
#include "zend_API.h"
#include "zend_exceptions.h"
#include "zend_operators.h"
#include "zend_constants.h"
#include "zend_ini.h"
#include "zend_interfaces.h"
#include "zend_closures.h"
#include "zend_extensions.h"

PHPAPI zend_class_entry *doctrine_instantiator_instantiator_interface_ce;
PHPAPI zend_class_entry *doctrine_instantiator_instantiator_ce;
PHPAPI zend_class_entry *doctrine_instantiator_instantiator_exception_interface_ce;
PHPAPI zend_class_entry *doctrine_instantiator_instantiator_exception_invalid_argument_exception_ce;

ZEND_BEGIN_ARG_INFO(arginfo_doctrine_instantiator_instantiator_interface_instantiate, 0)
    ZEND_ARG_INFO(0, className)
ZEND_END_ARG_INFO();

static const zend_function_entry doctrine_instantiator_instantiator_interface_methods[] = {
    ZEND_ABSTRACT_ME(doctrine_instantiator_interface, instantiate, arginfo_doctrine_instantiator_instantiator_interface_instantiate)
    PHP_FE_END
};

PHP_METHOD(doctrine_instantiator, instantiate) {
    char *class_name;
    int class_name_len;
    zend_class_entry **ce;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &class_name, &class_name_len) == FAILURE) {
        return;
    }

    if (zend_lookup_class(class_name, class_name_len, &ce TSRMLS_CC) != SUCCESS) {
        zend_throw_exception(
            doctrine_instantiator_instantiator_exception_invalid_argument_exception_ce,
            "The provided class does not exist",
            0 TSRMLS_CC
        );
        return;
    }

    object_init_ex(return_value, *ce);
}

ZEND_BEGIN_ARG_INFO(arginfo_doctrine_instantiator_instantiator_instantiate, 0)
    ZEND_ARG_INFO(0, className)
ZEND_END_ARG_INFO();

static const zend_function_entry doctrine_instantiator_instantiator_methods[] = {
    ZEND_ME(doctrine_instantiator, instantiate, arginfo_doctrine_instantiator_instantiator_instantiate, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_MINIT_FUNCTION(doctrine_instantiator)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Doctrine\\Instantiator\\InstantiatorInterface", doctrine_instantiator_instantiator_interface_methods);
    doctrine_instantiator_instantiator_interface_ce = zend_register_internal_interface(&ce TSRMLS_CC);

    INIT_CLASS_ENTRY(ce, "Doctrine\\Instantiator\\Instantiator", doctrine_instantiator_instantiator_methods);
    doctrine_instantiator_instantiator_ce = zend_register_internal_class(&ce TSRMLS_CC);
    zend_class_implements(doctrine_instantiator_instantiator_ce TSRMLS_CC, 1, doctrine_instantiator_instantiator_interface_ce);

    INIT_CLASS_ENTRY(ce, "Doctrine\\Instantiator\\Exception\\ExceptionInterface", NULL);
    doctrine_instantiator_instantiator_exception_interface_ce = zend_register_internal_interface(&ce TSRMLS_CC);

    INIT_CLASS_ENTRY(ce, "Doctrine\\Instantiator\\Exception\\InvalidArgumentException", NULL);
#ifdef HAVE_SPL
    doctrine_instantiator_instantiator_exception_invalid_argument_exception_ce = zend_register_internal_class_ex(
        &ce, spl_ce_InvalidArgumentException, NULL TSRMLS_CC
    );
#else
    doctrine_instantiator_instantiator_exception_invalid_argument_exception_ce = zend_register_internal_class_ex(
        &ce, zend_exception_get_default(TSRMLS_C), NULL TSRMLS_CC
    );
#endif
    zend_class_implements(
        doctrine_instantiator_instantiator_exception_invalid_argument_exception_ce TSRMLS_CC, 1,
        doctrine_instantiator_instantiator_exception_interface_ce
    );

    return SUCCESS;
}

zend_module_entry doctrine_instantiator_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_DOCTRINE_INSTANTIATOR_EXTNAME,
    NULL,
    PHP_MINIT(doctrine_instantiator),
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_DOCTRINE_INSTANTIATOR_EXTVER,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DOCTRINE_INSTANTIATOR
ZEND_GET_MODULE(doctrine_instantiator)
#endif

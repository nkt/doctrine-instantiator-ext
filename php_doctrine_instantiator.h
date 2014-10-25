#ifndef PHP_DOCTRINE_INSTANTIATOR_H
#define PHP_DOCTRINE_INSTANTIATOR_H

#include "php.h"

#define PHP_DOCTRINE_INSTANTIATOR_EXTNAME "Doctrine Instantiator"
#define PHP_DOCTRINE_INSTANTIATOR_EXTVER  "0.1"

extern zend_module_entry doctrine_instantiator_module_entry;
#define phpext_zephir_parser_ptr &doctrine_instantiator_module_entry

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(doctrine_instantiator);

BEGIN_EXTERN_C()

extern PHPAPI zend_class_entry *doctrine_instantiator_instantiator_interface_ce;
extern PHPAPI zend_class_entry *doctrine_instantiator_instantiator_ce;

END_EXTERN_C()

#endif /* PHP_DOCTRINE_INSTANTIATOR_H */

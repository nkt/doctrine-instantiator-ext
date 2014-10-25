PHP_ARG_ENABLE(doctrine_instantiator,
    whether to enable Doctrine Instantiator [ --enable-doctrine-instantiator   Enable Doctrine Instantiator]
)

if test $PHP_DOCTRINE_INSTANTIATOR != "no"; then
    PHP_SUBST(DOCTRINE_INSTANTIATOR_SHARED_LIBADD)
    PHP_NEW_EXTENSION(doctrine_instantiator, doctrine_instantiator.c, $ext_shared)
fi

PHP_ARG_ENABLE(phpaci, for phpaci support,
[ --enable-phpaci   Build phpaci], yes, yes)

SAPI_PHPACI_PATH=sapi/phpaci
PHP_PHPACI_CFLAGS="-I$abs_srcdir/sapi/phpaci"
BUILD_BINARY="sapi/phpaci/phpaci"

BUILD_PHPACI="\$(LIBTOOL) --mode=link \
              \$(CC) -export-dynamic \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) \$(PHP_RPATHS) \
              \$(PHP_GLOBAL_OBJS) \
              \$(PHP_BINARY_OBJS) \
              \$(PHP_PHPACI_OBJS) \
              \$(EXTRA_LIBS) \
              \$(ZEND_EXTRA_LIBS) \
        -o \$(BUILD_BINARY)"

if test "$PHP_PHPACI" = "yes"; then
    PHP_ADD_MAKEFILE_FRAGMENT($abs_srcdir/sapi/phpaci/Makefile.frag)
    PHP_SELECT_SAPI(phpaci, program, phpaci.c, $PHP_PHPACI_CFLAGS, '$(SAPI_PHPACI_PATH)')
fi

PHP_SUBST(BUILD_BINARY)
PHP_SUBST(BUILD_PHPACI)

dnl ## Local Variables:
dnl ## tab-width: 4
dnl ## End:

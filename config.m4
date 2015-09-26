PHP_ARG_ENABLE(phpaci,,
[  --enable-aci           Enable building PHPACI)

AC_MSG_CHECKING(for PHPACI build)
if test "$PHP_PHPACI" != "no"; then
echo "RENZO QUI"
  PHP_ADD_MAKEFILE_FRAGMENT($abs_srcdir/sapi/phpaci/Makefile.frag)

  dnl Set filename
  SAPI_PHPACI_PATH=sapi/phpaci/phpaci

  dnl Select SAPI
  PHP_SELECT_SAPI(phpaci, program, phpaci.c, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1, '$(SAPI_PHPACI_PATH)')

  BUILD_PHPACI="\$(LIBTOOL) --mode=link \$(CC) -export-dynamic \$(CFLAGS_CLEAN) \$(EXTRA_CFLAGS) \$(EXTRA_LDFLAGS_PROGRAM) \$(LDFLAGS) \$(PHP_RPATHS) \$(PHP_GLOBAL_OBJS) \$(PHP_BINARY_OBJS) \$(PHP_PHPACI_OBJS) \$(EXTRA_LIBS) \$(ZEND_EXTRA_LIBS) -o \$(SAPI_PHPACI_PATH)"

  dnl Expose to Makefile
  PHP_SUBST(SAPI_PHPACI_PATH)
  PHP_SUBST(BUILD_PHPACI)
fi
AC_MSG_RESULT($PHP_PHPACI)

#include "php.h"
#include "SAPI.h"
#include "php_main.h"

#include "zend_language_scanner.h"
#include "zend_language_parser.h"

static int phpaci_startup(sapi_module_struct *sapi_module) /* {{{ */
{
	if (php_module_startup(sapi_module, NULL, 0)==FAILURE) {
		return FAILURE;
	}
	return SUCCESS;
}
/* }}} */

static int sapi_phpaci_deactivate(void) /* {{{ */
{
	return SUCCESS;
}
/* }}} */

static int sapi_phpaci_header_handler(sapi_header_struct *h, sapi_header_op_enum op, sapi_headers_struct *s) /* {{{ */
{
	return 0;
}
/* }}} */

static int sapi_phpaci_send_headers(sapi_headers_struct *sapi_headers) /* {{{ */
{
	return SAPI_HEADER_SENT_SUCCESSFULLY;
}
/* }}} */

static void sapi_phpaci_send_header(sapi_header_struct *sapi_header, void *server_context) /* {{{ */
{
}
/* }}} */

static char* sapi_phpaci_read_cookies(void) /* {{{ */
{
	return NULL;
}
/* }}} */

static void sapi_phpaci_register_variables(zval *track_vars_array) /* {{{ */
{
}
/* }}} */

static void sapi_phpaci_log_message(char *message) /* {{{ */
{
	fprintf(stderr, "%s\n", message);
}
/* }}} */

/* sapi_module_struct phpaci_sapi_module {{{ */
static sapi_module_struct phpaci_sapi_module = {
	"phpaci", /* name */
	"Application Completion Interface", /* pretty name */
	phpaci_startup, /* startup */
	php_module_shutdown_wrapper, /* shutdown */
	NULL, /* activate */
	sapi_phpaci_deactivate, /* deactivate */
	NULL, /* unbuffered write */
	NULL, /* flush */
	NULL, /* get uid */
	NULL, /* get env */
	php_error, /* error handler */
	sapi_phpaci_header_handler, /* header handler */
	sapi_phpaci_send_headers, /* send headers handler */
	sapi_phpaci_send_header, /* send header handler */
	NULL,   /* read POST data */
	sapi_phpaci_read_cookies, /* read Cookies */
	sapi_phpaci_register_variables, /* register server variables */
	sapi_phpaci_log_message, /* Log message */
	NULL,   /* Get request time */
	NULL,   /* Child terminate */
	STANDARD_SAPI_MODULE_PROPERTIES
};
/* }}} */

void get_ast() /* {{{ */
{
	zval source;
	zend_string *code = zend_string_init("<?php echo 'dummy php script that should just print this';", 4, 1);
	zend_lex_state original_lex_state;
	zend_bool original_in_compilation;
	int parse_result;

	ZVAL_STR_COPY(&source, code);
	original_in_compilation = CG(in_compilation);
	CG(in_compilation) = 1;
	zend_save_lexical_state(&original_lex_state);

	if (zend_prepare_string_for_scanning(&source, "") == FAILURE) {
		// do something on failure
	}
	CG(ast) = NULL;
	CG(ast_arena) = zend_arena_create(1024 * 32);
	parse_result = zendparse();
}
/* }}} */

int main(int argc, char *argv[]) /* {{{ */
{
#ifdef ZTS
	tsrm_startup(1, 1, 0, NULL);
	(void)ts_resource(0);
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

#ifdef ZEND_SIGNALS
	zend_signal_startup();
#endif
	sapi_module_struct *sapi_module = &phpaci_sapi_module;
	sapi_startup(sapi_module);
	get_ast();

#ifdef ZTS
	tsrm_shutdown();
#endif
	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

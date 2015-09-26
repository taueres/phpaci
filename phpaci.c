#include "php.h"
#include "SAPI.h"
#include "php_main.h"

static int phpaci_startup(sapi_module_struct *sapi_module)
{
    if (php_module_startup(sapi_module, NULL, 0)==FAILURE) {
        return FAILURE;
    }
    return SUCCESS;
}

static int sapi_phpaci_deactivate(void)
{
    return SUCCESS;
}

static int sapi_phpaci_header_handler(sapi_header_struct *h, sapi_header_op_enum op, sapi_headers_struct *s)
{
    return 0;
}

static int sapi_phpaci_send_headers(sapi_headers_struct *sapi_headers)
{
    return SAPI_HEADER_SENT_SUCCESSFULLY;
}

static void sapi_phpaci_send_header(sapi_header_struct *sapi_header, void *server_context)
{
}

static char* sapi_phpaci_read_cookies(void)
{
    return NULL;
}

static void sapi_phpaci_register_variables(zval *track_vars_array) /* {{{ */
{
}

static void sapi_phpaci_log_message(char *message) /* {{{ */
{
    fprintf(stderr, "%s\n", message);
}

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

int main(int argc, char *argv[])
{
    sapi_module_struct *sapi_module = &phpaci_sapi_module;
    sapi_startup(sapi_module);
    return SUCCESS;
}

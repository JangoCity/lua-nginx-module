#include "ngx_http_lua_directive.h"
#include "ngx_http_lua_conf.h"

static ngx_command_t ngx_http_lua_cmds[] = {
	/* set_by_lua $res <inline script> [$arg1 [$arg2 [...]]] */
	{
		ngx_string("set_by_lua"),
		NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_SIF_CONF |
		NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_2MORE,
		ngx_http_lua_set_by_lua,
		0,
		0,
		ngx_http_lua_filter_set_by_lua_inline
	},

	/* set_by_lua_file $res rel/or/abs/path/to/script [$arg1 [$arg2 [..]]] */
	{
		ngx_string("set_by_lua_file"),
		NGX_HTTP_MAIN_CONF | NGX_HTTP_SRV_CONF | NGX_HTTP_SIF_CONF |
		NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_2MORE,
		ngx_http_lua_set_by_lua,
		0,
		0,
		ngx_http_lua_filter_set_by_lua_file
	},

	/* content_by_lua <inline script> */
	{
		ngx_string("content_by_lua"),
		NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
		ngx_http_lua_content_by_lua,
		0,
		0,
		NULL
	},

	/* content_by_lua_file rel/or/abs/path/to/script */
	{
		ngx_string("content_by_lua_file"),
		NGX_HTTP_LOC_CONF | NGX_HTTP_LIF_CONF | NGX_CONF_TAKE1,
		ngx_http_lua_content_by_lua_file,
		0,
		0,
		NULL
	},

	ngx_null_command
};

ngx_http_module_t ngx_http_lua_module_ctx = {
	NULL,	// preconfiguration
	NULL,	// postconfiguration

	ngx_http_lua_create_main_conf,	// create main configuration
	ngx_http_lua_init_main_conf,	// init main configuration

    NULL,    // create server configuration
    NULL,    // merge server configuration

    NULL,    // create location configuration
    NULL    // merge location configuration
};

ngx_module_t ngx_http_lua_module = {
    NGX_MODULE_V1,
    &ngx_http_lua_module_ctx,    // module context
    ngx_http_lua_cmds,            // module directives
    NGX_HTTP_MODULE,            // module type
    NULL,                        // init master
    NULL,                        // init module
    NULL,                        // init process
    NULL,                        // init thread
    NULL,                        // exit thread
    NULL,                        // exit process
    NULL,                        // exit master
    NGX_MODULE_V1_PADDING
};


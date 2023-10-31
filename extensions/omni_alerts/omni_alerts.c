// clang-format off
#include <postgres.h>
#include <fmgr.h>
// clang-format on
#include <access/xact.h>
#include <utils/builtins.h>
#include <utils/guc.h>
#include <utils/hsearch.h>
#include <utils/lsyscache.h>
#include <utils/memutils.h>
#include "utils/elog.h"

#include <unistd.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(capture);
PG_FUNCTION_INFO_V1(log_warning);

static emit_log_hook_type prev_emit_log_hook = NULL;
static void  omni_alerts_log(ErrorData *edata);
static void  write_console(const char *line, int len);

static char global_str[1000] = {0};

void _PG_init() {
  prev_emit_log_hook = emit_log_hook;
  emit_log_hook   = omni_alerts_log;
}

void _PG_fini(void) {
  if (emit_log_hook == omni_alerts_log)
    emit_log_hook = prev_emit_log_hook;
}

Datum capture(PG_FUNCTION_ARGS) {
  PG_RETURN_TEXT_P(cstring_to_text(global_str));
}

void omni_alerts_log(ErrorData *edata) {
  if(edata->elevel == WARNING)
    sprintf(global_str, "message: %s", edata->message);
}

Datum log_warning(PG_FUNCTION_ARGS)
{
  ereport(WARNING, errmsg("%s", text_to_cstring(PG_GETARG_TEXT_PP(0))));
  PG_RETURN_NULL();
}

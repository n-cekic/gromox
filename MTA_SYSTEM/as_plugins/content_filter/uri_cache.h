#pragma once
#include "common_types.h"

enum {
	URI_CACHE_BLACK_SIZE,
	URI_CACHE_BLACK_INTERVAL
};

void uri_cache_init(int black_size, int black_interval);
extern int uri_cache_run(void);
extern int uri_cache_stop(void);
extern void uri_cache_free(void);
BOOL uri_cache_query(const char *uri, char *reason, int length);

void uri_cache_add(const char *uri, char *reason);

BOOL uri_cache_dump_black(const char *path);

void uri_cache_set_param(int type, int value);

int uri_cache_get_param(int type);

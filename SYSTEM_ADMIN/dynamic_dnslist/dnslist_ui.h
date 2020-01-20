#pragma once

void dnslist_ui_init(const char *list_path, const char *mount_path,
	const char *url_link, const char *resource_path);
extern int dnslist_ui_run(void);
extern int dnslist_ui_stop(void);
extern void dnslist_ui_free(void);

#include <errno.h>
#include <libHX/defs.h>
#include <gromox/socket.h>
#include "log_flusher.h"
#include "single_list.h"
#include "util.h"
#include "list_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

typedef struct CONSOLE_PORT {
	char smtp_ip[16];
	int smtp_port;
	char delivery_ip[16];
	int delivery_port;
} CONSOLE_PORT;

typedef struct CONSOLE_PNODE {
	SINGLE_LIST_NODE node;
	CONSOLE_PORT u;
} CONSOLE_PNODE;

static char g_list_path[256];
static SINGLE_LIST g_console_list;

static BOOL log_flusher_control(const char *ip, int port);

void log_flusher_init(const char *path)
{
	if (NULL != path) {
		strcpy(g_list_path, path);
	} else {
		g_list_path[0] = '\0';
	}
	single_list_init(&g_console_list);
}

int log_flusher_run()
{
	LIST_FILE *plist_file;
	int i, list_len;
	SINGLE_LIST_NODE *pnode;
	
	plist_file = list_file_init(g_list_path, "%s:16%d%s:16%d");
	if (NULL == plist_file) {
		printf("[log_flusher]: Failed to read console list from %s: %s. "
			"Will not flush logs.\n",
			g_list_path, strerror(errno));
		return 0;
	}
	
	const CONSOLE_PORT *pitem = reinterpret_cast(CONSOLE_PORT *, list_file_get_list(plist_file));
	list_len = list_file_get_item_num(plist_file);
	for (i=0; i<list_len; i++) {
		CONSOLE_PNODE *pport = malloc(sizeof(*pport));
		if (NULL== pport) {
			continue;
		}
		pport->node.pdata = pport;
		memcpy(&pport->u, &pitem[i], sizeof(*pitem));
		single_list_append_as_tail(&g_console_list, &pport->node);
	}
	list_file_free(plist_file);

	for (pnode=single_list_get_head(&g_console_list); NULL!=pnode;
		pnode=single_list_get_after(&g_console_list, pnode)) {
		const CONSOLE_PORT *pconsole = &static_cast(CONSOLE_PNODE *, pnode->pdata)->u;
		log_flusher_control(pconsole->smtp_ip, pconsole->smtp_port);
		log_flusher_control(pconsole->delivery_ip, pconsole->delivery_port);
	}
	return 0;
	
}

int log_flusher_stop()
{
	SINGLE_LIST_NODE *pnode;

	while ((pnode = single_list_get_from_head(&g_console_list)) != NULL)
		free(pnode->pdata);
	return 0;

}

void log_flusher_free()
{
	single_list_free(&g_console_list);

}

static BOOL log_flusher_control(const char *ip, int port)
{
	int read_len, offset;
	char temp_buff[1024];
	int sockd = gx_inet_connect(ip, port, 0);
	if (sockd < 0)
		return FALSE;
	offset = 0;
	memset(temp_buff, 0, 1024);
	/* read welcome information */
	do {
		read_len = read(sockd, temp_buff + offset, 1024 - offset);
		if (-1 == read_len || 0 == read_len) {
			close(sockd);
			return FALSE;
		}
		offset += read_len;
		if (NULL != search_string(temp_buff, "console> ", offset)) {
			break;
		}
	} while (offset < 1024);
	if (offset >= 1024) {
		close(sockd);
		return FALSE;
	}

	/* send command */
	static const char command[] = "libmtasvc_log_plugin.so flush\r\n";
	if (write(sockd, command, strlen(command)) != strlen(command)) {
		close(sockd);
		return FALSE;
	}
	read(sockd, temp_buff, 1024);
	write(sockd, "quit\r\n", 6);
	close(sockd);
	return TRUE;
}


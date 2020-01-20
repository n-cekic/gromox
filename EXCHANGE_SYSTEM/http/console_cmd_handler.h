#pragma once
#include "common_types.h"

BOOL cmd_handler_http_control(int argc, char** argv);

BOOL cmd_handler_rpc_control(int argc, char** argv);

BOOL cmd_handler_service_control(int argc, char** argv);

BOOL cmd_handler_proc_control(int argc, char** argv);

BOOL cmd_handler_hpm_control(int argc, char **argv);

BOOL cmd_handler_help(int argc, char** argv);

BOOL cmd_handler_server_control(int argc, char** argv);

BOOL cmd_handler_system_control(int argc, char** argv);

BOOL cmd_handler_proc_plugins(int argc, char** argv);

BOOL cmd_handler_hpm_plugins(int argc, char** argv);

BOOL cmd_handler_service_plugins(int argc, char** argv);

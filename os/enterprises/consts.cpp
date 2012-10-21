#include "consts.h"
#include "callbacks.h"

const char *USER_NAMES[ USERS_COUNT ] = {
	"user 1",
	"user 2"
};

const legal_cmd_info_t LEGAL_COMMANDS[ LEGAL_COMMANDS_COUNT ] = {
	{ .str = "help",   .type = cmd_help,   .callback = cb_help   },
	{ .str = "quit",   .type = cmd_quit,   .callback = cb_quit   },

	{ .str = "chuser", .type = cmd_chuser, .callback = cb_chuser },
	{ .str = "lock",   .type = cmd_lock,   .callback = cb_lock   }
};

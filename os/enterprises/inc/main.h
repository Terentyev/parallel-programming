#ifndef __INCLUDE_MAIN_H

#define __INCLUDE_MAIN_H

#include <string>
#include <vector>

using std::string;
using std::vector;

#define WHITESPACES " \t"
#define USERS_COUNT 2
#define LEGAL_COMMANDS_COUNT 3


/**
 * User types enumeration type.
 * Possible users in system.
 */
typedef enum USER_TYPE {
	user1 = 0,
	user2
} user_t, *puser_t;

/**
 * State definition of system.
 */
typedef struct STATE_TYPE {
	user_t current_user;
	bool halted;
} state_t, *pstate_t;

/**
 * Callback of command.
 */
typedef void (*callback_t)( state_t &state, const vector<string> args );

/**
 * Possible commands in system.
 */
typedef enum COMMAND_TYPE {
	cmd_help = 0,
	cmd_quit,
	cmd_chuser
} cmd_t, *pcmd_t;

/**
 * Command info structure.
 */
typedef struct COMMAND_INFO_TYPE {
	cmd_t type;
	callback_t callback;
	vector<string> args;
} cmd_info_t, *pcmd_info_t;

/**
 * Legal command info structure.
 */
typedef struct LEGAL_COMMAND_INFO {
	const char *str;
	cmd_t type;
	callback_t callback;
} legal_cmd_info_t, *plegal_cmd_info_t;

/**
 * Callback on help command.
 */
void cb_help( state_t &state, const vector<string> args );

/**
 * Callback on quit command.
 */
void cb_quit( state_t &state, const vector<string> args );

/**
 * Change current user on next.
 */
void cb_chuser( state_t &state, const vector<string> args );

/**
 * Users user-friendly names.
 */
const char *USER_NAMES[ USERS_COUNT ] = {
	"user 1",
	"user 2"
};

/**
 * Array of legal commands definitions.
 */
const legal_cmd_info_t LEGAL_COMMANDS[ LEGAL_COMMANDS_COUNT ] = {
	{ .str = "help",   .type = cmd_help,   .callback = cb_help   },
	{ .str = "quit",   .type = cmd_quit,   .callback = cb_quit   },
	{ .str = "chuser", .type = cmd_chuser, .callback = cb_chuser }
};

#endif // !__INCLUDE_MAIN_H

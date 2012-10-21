#ifndef __INCLUDE_MAIN_H

#define __INCLUDE_MAIN_H

#include <string>
#include <vector>

using std::string;
using std::vector;


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
	cmd_chuser,
	cmd_lock
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

#endif // !__INCLUDE_MAIN_H

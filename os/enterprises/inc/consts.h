#ifndef __INCLUDE_CONST_H

#define __INCLUDE_CONST_H

#include "types.h"

#define WHITESPACES " \t"
#define USERS_COUNT 2
#define LEGAL_COMMANDS_COUNT 4

/**
 * Users user-friendly names.
 */
extern const char *USER_NAMES[];

/**
 * Array of legal commands definitions.
 */
extern const legal_cmd_info_t LEGAL_COMMANDS[];

#endif // !__INCLUDE_CONST_H

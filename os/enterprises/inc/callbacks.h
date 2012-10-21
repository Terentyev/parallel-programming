#ifndef __INCLUDE_CALLBACKS_H

#define __INCLUDE_CALLBACKS_H

#include "types.h"

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
 * Try to lock balance.
 */
void cb_lock( state_t &state, const vector<string> args );

#endif // !__INCLUDE_CALLBACKS_H

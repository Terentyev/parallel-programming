#include "callbacks.h"
#include "consts.h"

void cb_quit( state_t &state, const vector<string> args )
{
	state.halted = true;
}

void cb_chuser( state_t &state, const vector<string> args )
{
	state.current_user = (user_t)( (state.current_user + 1) % USERS_COUNT );
}

void cb_lock( state_t &state, const vector<string> args )
{
}

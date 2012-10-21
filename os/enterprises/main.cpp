#include <iostream>
#include <pthread.h>
#include <stdlib.h>

#include "types.h"
#include "consts.h"

using std::cout;
using std::cin;
using std::cerr;
using std::clog;
using std::endl;

/**
 * Parse command line prompted by user on array of strings splitted by whitespaces.
 */
vector<string> parse_command_line( string cmd_line )
{
	vector<string> result;
	string::size_type a = 0;
	string::size_type b = 0;

	while ( 1 )
	{
		a = cmd_line.find_first_not_of( WHITESPACES, b );
		if ( string::npos == a )
		{
			break;
		}

		b = cmd_line.find_first_of( WHITESPACES, a );
		if ( string::npos == b )
		{
			b = cmd_line.size();
		}

		result.push_back( cmd_line.substr( a, b - a ) );
	}

	return result;
}

/**
 * Check command is legal and fill cmd_t struct.
 */
bool is_legal_command( vector<string> cmd_info, cmd_info_t &cmd )
{
	const legal_cmd_info_t *legal_cmd_info;
	for ( int i = 0; i < LEGAL_COMMANDS_COUNT; ++i )
	{
		legal_cmd_info = &LEGAL_COMMANDS[ i ];
		if ( cmd_info[0] == legal_cmd_info->str )
		{
			cmd.type = legal_cmd_info->type;
			cmd.callback = legal_cmd_info->callback;
			cmd.args = cmd_info;
			return true;
		}
	}

	return false;
}

void cb_help( state_t &state, const vector<string> args )
{
	cout
		<< "Available commands:" << endl
		<< "	help	show this help information"  << endl
		<< "	quit	quit from program"           << endl
		<<                                              endl
		<< "	chuser	change current user on next" << endl
		<< "	lock    try to lock a balance"       << endl
		<< endl;
}

/**
 * Print promt line, ask user a command and check legally of this command.
 */
cmd_info_t read_command( state_t state )
{
	string cmd_line;
	vector<string> cmd_info;
	cmd_info_t cmd;

	while ( 1 )
	{
		cout << USER_NAMES[ state.current_user ] << " $ ";
		cin >> cmd_line;

		cmd_info = parse_command_line( cmd_line );
		if ( is_legal_command( cmd_info, cmd ) )
		{
			break;
		}
		else
		{
			cout << "Not valid command. Please type 'help' to see a help by commands" << endl;
		}
	}

	return cmd;
}

/**
 * Dispatch command;
 */
bool dispatch_command( cmd_info_t cmd, state_t &state )
{
	cmd.callback( state, cmd.args );
	return !state.halted;
}

/**
 * Enterprise thread routine.
 */
void *thread_enterprise_routine( void *arg )
{
	for(;;);
	return NULL;
}

/**
 * Server thread routine.
 */
void *thread_server_routine( void *arg )
{
	for(;;);
	return NULL;
}

/**
 * Create thread.
 */
void init_thread( pthread_t &thread, void *(*thread_routine) (void *) )
{
	if ( 0 == pthread_create( &thread, NULL, thread_routine, NULL ) )
	{
		clog << "Successfully created thread" << endl;
	}
	else
	{
		cerr << "Failed to create a thread. Exit..." << endl;
		exit( 1 );
	}
}

/**
 * Create threads.
 */
inline void init_threads( pthread_t threads[] )
{
	init_thread( threads[0], thread_server_routine );
	for ( int i = 0; i < USERS_COUNT; ++i )
	{
		init_thread( threads[ i + 1 ], thread_enterprise_routine );
	}
}

/**
 * Destroy thread.
 */
void final_thread( pthread_t &thread )
{
	if ( 0 == pthread_cancel( thread ) )
	{
		clog << "Successfully destroyed thread" << endl;
	}
	else
	{
		cerr << "Failed to destroy a thread. Exit..." << endl;
		exit( 1 );
	}
}

/**
 * Destroy threads.
 */
inline void final_threads( pthread_t threads[] )
{
	final_thread( threads[0] );
	for ( int i = 0; i < USERS_COUNT; ++i )
	{
		final_thread( threads[ i + 1 ] );
	}
}

/**
 * Main function.
 */
int main( int argc, char **argv )
{
	state_t state = {
		.current_user = user1,
		.halted = false
	};
	pthread_t threads[ USERS_COUNT + 1 ];

	/* Initialize all threads */
	init_threads( threads );

	/* Read and dispatch user command */
	while ( dispatch_command( read_command( state ), state ) );

	/* Finalization all threads */
	final_threads( threads );

	return 0;
}

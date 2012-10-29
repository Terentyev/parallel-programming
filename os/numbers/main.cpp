#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "main.h"

pthread_mutex_t third_mutex;
int third_number = 0;

/**
 * Print numbers.
 */
void *print_number( void *arg )
{
	int first = (int)(long int) arg;

	printf( "%d ", first + 1 );
	fflush( stdout );

	return NULL;
}

/**
 * Fork and check returned value on negative.
 */
inline void safe_fork_impl(
	pthread_t *thread,
	void *(*start_routine) (void *),
	void *arg,
	const char *filename,
	int lineno
)
{
	if ( 0 != pthread_create( thread, NULL, start_routine, arg ) )
	{
		fprintf( stderr, "Error while fork: [%d] %s", lineno, filename );
		exit( 1 );
	}
}

/**
 * Lock mutex and check returned value.
 */
inline void safe_mutex_lock_impl(
	pthread_mutex_t *mutex,
	const char *filename,
	int lineno
)
{
	if ( 0 != pthread_mutex_lock( mutex ) )
	{
		fprintf( stderr, "Error while mutex lock: [%d] %s", lineno, filename );
		exit( 1 );
	}
}

/**
 * Unlock mutex and check returned value.
 */
inline void safe_mutex_unlock_impl(
	pthread_mutex_t *mutex,
	const char *filename,
	int lineno
)
{
	if ( 0 != pthread_mutex_unlock( mutex ) )
	{
		fprintf( stderr, "Error while mutex unlock: [%d] %s", lineno, filename );
		exit( 1 );
	}
}

/**
 * In first thread.
 * Should create second thread and launch print_number.
 */
void *_linear_first_child( void *arg )
{
	int i = (int)(long int) arg;
	pthread_t child;

	print_number( arg );

	++i;
	/* Create second thread */
	safe_fork( &child, &print_number, (void*) i );

	pthread_join( child, NULL );

	return NULL;
}

/**
 * Split thread in linear.
 */
void split_linear()
{
	for ( int i = 0; i < MAX_NUMBER / 2; ++i )
	{
		pthread_t child;

		/* Create first thread */
		safe_fork( &child, &_linear_first_child, (void*) (2 * i) );

		pthread_join( child, NULL );
	}
}

/**
 * Split thread as true parallels.
 */
void split_parallel()
{
	for ( int i = 0; i < MAX_NUMBER / 2; ++i )
	{
		pthread_t child1, child2;

		/* Create first thread */
		safe_fork( &child1, &print_number, (void *) (2 * i) );
		pthread_join( child1, NULL );

		/* Create second thread */
		safe_fork( &child2, &print_number, (void *) (2 * i + 1) );
		pthread_join( child2, NULL );
	}
}

/**
 * In parent thread.
 * Should wait other thread and launch print_number.
 */
void *_parallel_with_waiting_child( void *arg )
{
	int number = (int)(long int) arg;

	while ( number < MAX_NUMBER ) {
		safe_mutex_lock( &third_mutex );
		if ( third_number == number ) {
			print_number( (void*) number );
			++third_number;
			number += 2;
		}
		safe_mutex_unlock( &third_mutex );
	}

	return NULL;
}

/**
 * Split thread as parallels but each thread should wait of other thread ending.
 */
void split_parallel_with_waiting()
{
	pthread_t child1, child2;

	/* Initialize a mutex */
	pthread_mutex_init( &third_mutex, NULL );

	/* Create first thread */
	safe_fork( &child1, &_parallel_with_waiting_child, (void *) 0 );

	/* Create second thread */
	safe_fork( &child2, &_parallel_with_waiting_child, (void *) 1 );

	pthread_join( child1, NULL );
	pthread_join( child2, NULL );
}

/**
 * Main function
 */
int main( int argc, char **argv )
{
	split_t split_type = splitLinear;

	/* Try to determine a thread split type */
	if ( argc > 1 )
	{
		if ( 0 == strcmp( argv[1], SPLIT_LINEAR_CMD_ARG ) ) split_type = splitLinear;
		else if ( 0 == strcmp( argv[1], SPLIT_PARALLEL_CMD_ARG ) ) split_type = splitParallel;
		else if ( 0 == strcmp( argv[1], SPLIT_PARALLEL_WITH_WAITING_CMD_ARG ) ) split_type = splitParallelWithWaiting;
	}

	printf( "Welcome. Current mode: %s\n", SPLIT_TYPE_MODE[ split_type ] );
	fflush( stdout );

	switch ( split_type )
	{
		case splitLinear:
			split_linear();
			break;
		case splitParallel:
			split_parallel();
			break;
		case splitParallelWithWaiting:
			split_parallel_with_waiting();
			break;
	}

	return 0;
}

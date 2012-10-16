#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "main.h"

/**
 * Print numbers.
 */
void *print_numbers( void *arg )
{
	int first = (int)(long int)arg;

	for ( ; first < MAX_NUMBER; first += 2 )
	{
		printf( "%d ", first );
		fflush( stdout );
	}

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
 * In first thread.
 * Should create second thread and launch print_numbers.
 */
void *_linear_first_child( void *arg )
{
	pthread_t child;

	/* Create first thread */
	safe_fork( &child, &print_numbers, (void *)1 );

	print_numbers( 0 );

	pthread_join( child, NULL );

	return NULL;
}

/**
 * Split thread in linear.
 */
void split_linear()
{
	pthread_t child;

	/* Create first thread */
	safe_fork( &child, &_linear_first_child, NULL );

	pthread_join( child, NULL );
}

/**
 * Split thread as true parallels.
 */
void split_parallel()
{
	pthread_t child1, child2;

	/* Create first thread */
	safe_fork( &child1, &print_numbers, (void *)0 );

	/* Create second thread */
	safe_fork( &child2, &print_numbers, (void *)1 );

	pthread_join( child1, NULL );
	pthread_join( child2, NULL );
}

/**
 * In parent thread.
 * Should wait first thread and launch print_numbers.
 */
void *_parallel_with_waiting_second_child( void *arg )
{
	pthread_t *child1 = (pthread_t*)arg;

	/* Wait first thread */
	pthread_join( *child1, NULL );

	print_numbers( (void*) 1 );

	return NULL;
}

/**
 * Split thread as parallels but second thread should wait of first thread ending.
 */
void split_parallel_with_waiting()
{
	pthread_t child1, child2;

	/* Create first thread */
	safe_fork( &child1, &print_numbers, (void *)0 );

	/* Create second thread */
	safe_fork( &child2, &_parallel_with_waiting_second_child, (void *)&child1 );

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

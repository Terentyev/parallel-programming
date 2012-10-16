#ifndef __INCLUDE_MAIN_H

#define __INCLUDE_MAIN_H

#define SPLIT_LINEAR_CMD_ARG "linear"
#define SPLIT_PARALLEL_CMD_ARG "parallel"
#define SPLIT_PARALLEL_WITH_WAITING_CMD_ARG "parallel-with-waiting"

#define MAX_NUMBER 100

#define safe_fork( thread, start_routine, arg ) safe_fork_impl( thread, start_routine, arg, __FILE__, __LINE__ )

typedef enum SPLIT_TYPE
{
	splitLinear = 0,
	splitParallel,
	splitParallelWithWaiting
} split_t;

const char *SPLIT_TYPE_MODE[3] = {
	"linear",
	"true parallel",
	"parallel threads, but second wait ending of first"
};

#endif // !__INCLUDE_MAIN_H

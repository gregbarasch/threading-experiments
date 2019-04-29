#include <stdio.h>
#include <pthread.h>

#define NUM_EXECUTIONS 10

void create_n_threads(int n, volatile int *shared_variable);


int main(void)
{
	printf("\n");
	double total = 0;   // Running total execution time
	double average = 0; // Average time of each execution
	
	for (int i = 0; i < NUM_EXECUTIONS; i++) {
		volatile int shared_variable = 0;

		clock_t start = clock();
		create_n_threads(100, &shared_variable);
		clock_t stop = clock();

		printf("SHARED VARIABLE:%d\n", shared_variable);
        double time = (double)(stop - start) / CLOCKS_PER_SEC;
		total += time;
	}

	average = total/NUM_EXECUTIONS;
	printf("AVERAGE TIME FOR %i EXECUTIONS: %f SECONDS\n\n", NUM_EXECUTIONS, average);

	return 0;
}


/**
 * Function that increments a shared variable 1000 times. It will be passed
 * to the threads.
 */
void function(void * shared_variable)
{
	for (int i = 0; i < 1000; i++) {
		(*(int *)shared_variable)++;
	}
}


/**
 * Here we create n number of threads. First they are created, then they are
 * joined.
 */
void create_n_threads(int n, volatile int * shared_variable)
{
	pthread_t threads[n];
	
	/**
	 * Here we put the join in a separate for loop. This allows each thread
	 * to run concurrently. We do not wait until the thread finished to
	 * create the next one.
	 */
	for (int i = 0; i < n; i++) {
		pthread_create(&threads[i], NULL, (void *)function, (void *)shared_variable);
	}
	for (int i = 0; i < n; i++) {
		pthread_join(threads[i], NULL);
	}
}

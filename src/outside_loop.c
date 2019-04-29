#include <stdio.h>
#include <pthread.h>

#define NUM_EXECUTIONS 10

void create_n_threads(int n, volatile int *shared_variable);

pthread_mutex_t lock;


int main(void)
{
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\nMutex lock failure.\n");
		return 1;
	}

	printf("\n");
	double total = 0;   // Running total of execution times.
	double average = 0; // Average time of each execution

	for (int i = 0; i < NUM_EXECUTIONS; i++) {
		volatile int shared_variable = 0;

		clock_t start = clock();
		create_n_threads(100, &shared_variable);
		clock_t stop = clock();

		printf("SHARED VARIABLE: %d\n", shared_variable);
        double time = (double)(stop - start) / CLOCKS_PER_SEC;
        total += time;
	}

	average = total/NUM_EXECUTIONS;
	printf("AVERAGE TIME FOR %i EXECUTIONS: %f SECONDS\n\n", NUM_EXECUTIONS, average);

	pthread_mutex_destroy(&lock);
	return 0;
}


/**
 * Function that increments a shared variable 1000 times. It will be passed
 * to the threads. Mutex lock outside the for loop.
 */
void function(void * shared_variable)
{
	pthread_mutex_lock(&lock);
	
	for (int i = 0; i < 1000; i++) {
		(*(int *)shared_variable)++;
	}

	pthread_mutex_unlock(&lock);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 10:14:10 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/11 11:05:04 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#define NUM_LOOPS 100
long long sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*counting_thread(void *arg)
{
	int offset = *(int*)arg;
	for (long i = 0; i < NUM_LOOPS; i++)
	{
		pthread_mutex_lock(&mutex);
		sum += offset;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main(void)
{
	// spawn threads
	int offset = 1;
	pthread_t id1;
	pthread_create(&id1, NULL, counting_thread, &offset);
	

	int offset1 = -1;
	pthread_t id2;
	pthread_create(&id2, NULL, counting_thread, &offset1);

	// wait for threads to finish
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	// counting_function(-1);
	printf("Sum = %lld\n", sum);
	return(0);
}
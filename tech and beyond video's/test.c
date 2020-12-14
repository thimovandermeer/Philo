/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/10 10:16:15 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/10 10:28:31 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*workerThreadFunc(void *tid)
{
	long *myID = (long*) tid;
	printf("Hello world print this is thread %ld\n", myID);
}

int main()
{
	pthread_t tid0;
	pthread_t tid1;
	pthread_t tid2;
	pthread_t *pthreads[] = {&tid0, &tid1, &tid2};
	for (int i = 0; i < 3; i++)
		pthread_create(pthreads[i], NULL, workerThreadFunc, (void*)pthreads[i]);
	pthread_exit(NULL);
	return 0;
}
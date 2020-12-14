/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/10 10:32:35 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/10 11:27:55 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct sum_runner_struct
{
	long long limit;
	long long answer;
};
// computed by the  background thread
long long sum = 0;

void*	sum_runner(void* arg)
{
	struct sum_runner_struct *arg_struct = (struct sum_runner_struct*)arg;

	long long sum;
	for (long long i = 0; i <= arg_struct->limit; i++)
		sum += i;	
	arg_struct->answer = sum;
	pthread_exit(0);
}
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("usage: %s < num>\n", argv[0]);
		exit(-1);
	}

	int num_args = argc - 1;
	
	struct sum_runner_struct args[num_args];
	// launch thread
	pthread_t tids[num_args];
	
	for (int i = 0; i < num_args; i++)
	{
		args[i].limit = atoll(argv[i + 1]);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, sum_runner, &args[i]);
	}
	// on this null you can the thread return save
	for (int i = 0 ; i < num_args; i++)
	{
		pthread_join(tids[i], NULL);
		printf("sum is %lld\n", args[i].answer);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 14:11:19 by thvan-de      #+#    #+#                 */
/*   Updated: 2021/01/05 08:10:25 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_dead_lock(t_function_vars *vars)
{
	pthread_mutex_destroy(&vars->dead_lock);
}

void	free_write_lock(t_function_vars *vars)
{
	pthread_mutex_destroy(&vars->write_lock);
}

void	free_time_lock(t_function_vars *vars, t_philo *philos, int i)
{
	while (i)
	{
		i--;
		pthread_mutex_destroy(&philos[i].time_lock);
	}
	free_forks(vars);
}

void	free_forks(t_function_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->n_philos)
	{
		pthread_mutex_destroy(&vars->forks[i]);
		i++;
	}
	free(vars->forks);
	free_dead_lock(vars);
	free_write_lock(vars);
}

void	free_philos(t_philo *philos)
{
	int i;

	i = 0;
	while (&philos[i])
	{
		free(&philos[i]);
		i++;
	}
	free(philos);
}

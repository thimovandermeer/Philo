/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_philos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:08:29 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/05 09:08:42 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		create_philo(t_function_vars *vars, t_philo **philos)
{
	(*vars).forks = malloc(sizeof(pthread_mutex_t) * vars->n_philos);
	if (!(*vars).forks)
	{
		ft_putstr_fd("Something went wrong during malloc\n", 2);
		return (1);
	}
	(*philos) = malloc(sizeof(t_philo) * vars->n_philos);
	if (!philos)
	{
		ft_putstr_fd("something went wrong during mallocing philo's\n", 2);
		return (1);
	}
	return (0);
}

int		create_forks(t_function_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->n_philos)
	{
		if (pthread_mutex_init(&(*vars).forks[i], NULL) != 0)
		{
			free_forks(vars);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&(*vars).write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&(*vars).write_lock);
		return (1);
	}
	if (pthread_mutex_init(&(*vars).dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&(*vars).dead_lock);
		return (1);
	}
	(*vars).isdead = false;
	return (0);
}

int		init_philo(t_function_vars *vars, t_philo *philos)
{
	int i;

	i = 0;
	while (i < vars->n_philos)
	{
		philos[i].philo_num = i;
		philos[i].last_eaten = vars->start_time;
		philos[i].times_eaten = 0;
		philos[i].vars = vars;
		if (pthread_mutex_init(&philos[i].time_lock, NULL) != 0)
		{
			pthread_mutex_destroy(&philos[i].time_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	jointhreads(t_philo *philos, int i)
{
	while (i)
	{
		i--;
		pthread_join(philos[i].thread, NULL);
	}
	free_time_lock(philos->vars, philos, i);
}

int		start_threads(t_function_vars *vars, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < vars->n_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_loop, &philos[i]))
		{
			jointhreads(philos, i);
			return (1);
		}
		i++;
	}
	return (0);
}

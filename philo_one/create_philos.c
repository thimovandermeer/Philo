/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_philos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:08:29 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 14:31:48 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		create_philo(t_function_vars *vars, t_philo **philos)
{
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->n_philos);
	if (!vars->forks)
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
	unsigned int i;

	i = 0;
	while (i < vars->n_philos)
	{
		if (pthread_mutex_init(&(*vars).forks[i], NULL) != 0)
		{
			// free forks I suppose
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
	vars->isdead = false;
	return (0);
}

int		init_philo(t_function_vars *vars, t_philo *philos)
{
	unsigned int i;

	i = 0;
	while (i < vars->n_philos)
	{
		philos[i].philo_num = i;
		philos[i].last_eaten = vars->start_time;
		philos[i].times_eaten = 0;
		philos[i].vars = vars;
		// here we need to have some time management as well
		i++;
	}
	return (0);
}

int		start_threads(t_function_vars *vars, t_philo *philos)
{
	unsigned int		i;
	int					err;

	i = 0;
	while (i < vars->n_philos)
	{
		err = pthread_create(&philos[i].thread, NULL, philo_loop, &philos[i]);
		if (err != 0)
		{
			ft_putstr_fd("something went wrong when creating threads\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

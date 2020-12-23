/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_philos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:08:29 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/23 13:56:05 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		create_philo(t_function_vars *vars, t_philo **philos)
{
	(*philos) = malloc(sizeof(t_philo) * vars->n_philos);
	if (!philos)
	{
		ft_putstr_fd("something went wrong during mallocing philo's\n", 2);
		return (1);
	}
	return (0);
}

int		create_sems(t_function_vars *vars, t_philo *philos)
{
	int i;

	i = 0;
	vars->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, vars->n_philos);
	if (vars->forks == SEM_FAILED)
	{
		free(philos);
		return (1);
	}
	sem_unlink("forks");
	vars->write_lock = sem_open("write_lock", O_CREAT | O_EXCL, 0644, 1);
	if (vars->write_lock == SEM_FAILED)
	{
		free(philos);
		return (1);
	}
	sem_unlink("write_lock");
	vars->dead_lock = sem_open("dead_lock", O_CREAT | O_EXCL, 0644, 1);
	if (vars->dead_lock == SEM_FAILED)
	{
		free(philos);
		return (1);
	}
	sem_unlink("dead_lock");
	vars->time_lock = sem_open("time_lock", O_CREAT | O_EXCL, 0644, 1);
	if (vars->time_lock == SEM_FAILED)
	{
		free(philos);
		return (1);
	}
	sem_unlink("time_lock");
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
	free_sems(philos->vars);
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

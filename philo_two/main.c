/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 11:21:16 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/06 10:14:23 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

void	check_death(t_function_vars *vars, int i, t_philo *philos)
{
	if (philos[i].times_eaten != vars->a_eat)
	{
		write_lock(philos[i].vars, i, "Has died");
		(*vars).isdead = true;
	}
}

int		check_philo_status(t_philo *philos, t_function_vars *vars)
{
	int		i;
	bool	stop;

	i = 0;
	stop = false;
	while (i < (*vars).n_philos)
	{
		sem_wait(philos[i].vars->time_lock);
		if (gettime() - philos[i].last_eaten > philos[i].vars->t_die)
		{
			check_death(vars, i, philos);
			sem_post(philos[i].vars->time_lock);
			stop = true;
			break ;
		}
		sem_post(philos[i].vars->time_lock);
		i++;
	}
	usleep(200);
	if (stop)
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_function_vars vars;
	t_philo			*philos;

	if (validate_inputs(argc, argv, &vars))
		return (1);
	if (create_philo(&vars, &philos))
		return (1);
	if (create_sems(&vars, philos))
		return (1);
	if (init_philo(&vars, philos))
		return (1);
	if (start_threads(&vars, philos))
		return (1);
	while (!check_philo_status(philos, &vars))
		continue;
	jointhreads(philos, vars.n_philos);
	return (0);
}

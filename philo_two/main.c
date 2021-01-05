/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 11:21:16 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/05 09:42:02 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

int		check_philo_status(t_philo *philos, t_function_vars *vars)
{
	int		i;

	i = 0;
	while (i < (*vars).n_philos)
	{
		sem_wait(philos[i].vars->time_lock);
		if (gettime() - philos[i].last_eaten > philos[i].vars->t_die)
		{
			if (philos[i].times_eaten != vars->a_eat)
			{
				write_lock(philos[i].vars, i, "Has died");
				(*vars).isdead = true;
				sem_post(philos[i].vars->time_lock);
				return (1);
			}
			break ;
		}
		sem_post(philos[i].vars->time_lock);
		i++;
	}
	usleep(200);
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

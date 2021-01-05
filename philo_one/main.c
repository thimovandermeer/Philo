/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 11:21:16 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/05 07:34:15 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

void 	check_death(t_function_vars *vars, int i, t_philo *philos)
{
	if (philos[i].times_eaten != vars->a_eat)
	{
		write_lock(vars, i, "Has died");
		pthread_mutex_lock(&vars->dead_lock);
		(*vars).isdead = true;
		pthread_mutex_unlock(&vars->dead_lock);
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
		pthread_mutex_lock(&philos[i].vars->time_lock);
		if (gettime() - philos[i].last_eaten > vars->t_die)
		{
			check_death(vars, i, philos);
			pthread_mutex_unlock(&philos[i].vars->time_lock);
			stop = true;
			break ;
		}
		pthread_mutex_unlock(&philos[i].vars->time_lock);
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
	if (create_forks(&vars))
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


// so a bunch of things go wrong, the most important is the fact that it goes on after dying
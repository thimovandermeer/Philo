/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 11:21:16 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/22 13:50:55 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosophers.h"

int		check_philo_status(t_philo *philos, t_function_vars *vars)
{
	int		i;
	bool	stop;

	i = 0;
	stop = false;
	while (i < (*vars).n_philos)
	{
		pthread_mutex_lock(&philos[i].vars->time_lock);
		if (gettime() - philos[i].last_eaten > philos[i].vars->t_die)
		{
			write_lock(philos[i].vars, i, "Has died");
			(*vars).isdead = true;
			pthread_mutex_unlock(&philos[i].vars->time_lock);
			stop = true;
			break ;
		}
		pthread_mutex_unlock(&philos[i].vars->time_lock);
		i++;
	}
	usleep(500);
	if (stop)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
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
	return (0);
}

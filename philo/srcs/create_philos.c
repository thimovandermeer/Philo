/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_philos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:08:29 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 09:13:32 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		create_philo(t_function_vars *vars, t_philo **philo)
{
	// create the amount of forks
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->n_philos);
	if(!vars->forks)
	{
		ft_putstr_fd("Something went wrong during malloc\n", 2);
		// i suppose i have to delete something here in the near future
		return(1);
	}
	// create a struct which will contain all these philo's
	vars->philos = malloc(sizeof(t_philo) * vars->n_philos);
	if (!vars->philos)
	{
		ft_putstr_fd("something went wrong during mallocing individual philo's\n", 2);
		// i suppose i have to delete something here in the near future;
		return(1);
	}
}

int		create_forks(t_function_vars *vars)
{
	int i;

	i = 0;
	while(vars->forks[i])
	{
		if(pthread_mutex_init(&vars->forks[i], NULL) != 0)
		{
			// free forks I suppose
			return (1);
		}
		i++;
	}
	return (0);
}

int		init_philo(t_function_vars *vars, t_philo **philo)
{
	int i; 
	int err;
	i = 0;

	
	while(i < vars->n_philos)
	{
		// set philo number
		philo[i]->philo_num = i;
		philo[i]->last_eaten = 0;
		philo[i]->times_eaten = 0;
		
	}
	// set last eaten
	// set times eaten
	// activate thread
}


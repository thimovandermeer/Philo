/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 14:11:19 by thvan-de      #+#    #+#                 */
/*   Updated: 2020/12/23 13:37:01 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_sems(t_function_vars *vars)
{
	sem_close(vars->forks);
	sem_close(vars->time_lock);
	sem_close(vars->write_lock);
	sem_close(vars->dead_lock);
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
	free_sems(philos->vars);
}

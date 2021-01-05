/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/22 14:11:19 by thvan-de      #+#    #+#                 */
/*   Updated: 2021/01/05 15:41:22 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_sems(t_function_vars *vars)
{
	sem_close(vars->forks);
	sem_close(vars->write_lock);
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

int		create_sems(t_function_vars *vars, t_philo *philos)
{
	vars->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, vars->n_philos);
	sem_unlink("forks");
	vars->write_lock = sem_open("write_lock", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("write_lock");
	if (vars->write_lock == SEM_FAILED || vars->forks == SEM_FAILED)
	{
		free(philos);
		return (1);
	}
	(*vars).isdead = false;
	return (0);
}

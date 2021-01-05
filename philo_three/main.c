/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/05 10:40:10 by thvan-de      #+#    #+#                 */
/*   Updated: 2021/01/05 15:40:17 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(pid_t *pids, int i)
{
	while (i)
	{
		i--;
		kill(pids[i], SIGKILL);
	}
	exit(1);
}

void	soon_tobe_death(t_function_vars *vars, pid_t *pids)
{
	int		ret;
	int		i;

	i = 0;
	while (i < vars->n_philos)
	{
		waitpid(-1, &ret, WUNTRACED);
		if (WEXITSTATUS(ret) != 0)
			free_all(pids, vars->n_philos);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_function_vars vars;
	t_philo			*philos;
	pid_t			*pids;

	if (validate_inputs(argc, argv, &vars))
		return (1);
	if (create_philo(&vars, &philos, &pids))
		return (1);
	if (create_sems(&vars, philos))
		return (1);
	init_philo(&vars, philos);
	start_processes(&vars, philos, pids);
	soon_tobe_death(&vars, pids);
	exit(0);
}

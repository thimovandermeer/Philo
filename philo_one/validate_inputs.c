/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_inputs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:07:36 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/22 12:44:38 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_philos(t_function_vars *vars, char **input, int argc)
{
	(*vars).n_philos = ft_atoi(input[1]);
	(*vars).t_die = ft_atoi(input[2]);
	(*vars).t_eat = ft_atoi(input[3]);
	(*vars).t_sleep = ft_atoi(input[4]);
	if (argc == 6)
		(*vars).a_eat = ft_atoi(input[5]);
	else
		(*vars).a_eat = -1;
	(*vars).start_time = gettime();
}

int		validate_inputs(int argc, char **input, t_function_vars *vars)
{
	int		i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: not enough arguments are given\n", 2);
		return (1);
	}
	set_philos(vars, input, argc);
	printf("n_philos = %i\n", vars->t_sleep);
	if (vars->n_philos < 0 || vars->t_die < 0 || vars->t_eat < 0 || vars->t_sleep < 0)
	{
		printf("kom ik hier?\n");
		ft_putstr_fd("Error: please give positive inputs\n", 2);
		return (1);
	}
	if (vars->n_philos < 2)
	{
		ft_putstr_fd("Error: not enough philo's where given\n", 2);
		return (1);
	}
	return (0);
}
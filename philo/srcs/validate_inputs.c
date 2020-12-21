/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_inputs.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:07:36 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 08:08:08 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void 	set_philos(t_function_vars *vars, char **input, int argc)
{
	// set all values to approp struct
	vars->n_philos = ft_atoi(input[1]);
	vars->t_die = ft_atoi(input[2]);
	vars->t_eat = ft_atoi(input[3]);
	vars->t_sleep = ft_atoi(input[4]);
	if(argc == 6)
		vars->a_eat = ft_atoi(input[5]);
	else
		vars->a_eat = -1;
	
	// here start timing will implement this later one
}

int		validate_inputs(int argc , char **input, t_function_vars *vars)
{
	// validate inputs
	int		i;

	i = 0;
	// check amount of arguments
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: not enough arguments are given\n", 2);
		return(1);
	}
	// set all arguments
	set_philos(vars, input, argc);
	if (!vars->n_philos || !vars->t_die || !vars->t_eat || ! vars->t_sleep)
	{
		ft_putstr_fd("Error: please give positive inputs\n", 2);
		return (1);
	}
	if (vars->n_philos < 2)
	{
		ft_putstr_fd("Error: not enough philo's where given\n", 2);
		return (1);
	}
}
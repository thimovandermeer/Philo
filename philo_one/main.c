/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 11:21:16 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 14:33:02 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosopher.h"

int		check_philo_status()
{
	return(0);
}

int	main(int argc, char **argv)
{
	t_function_vars vars;
	t_philo			*philos;

	if (validate_inputs(argc, argv, &vars))
		return (0);
	if (create_philo(&vars, &philos))
		return (0);
	if (create_forks(&vars))
		return (0);
	if (init_philo(&vars, philos))
		return (0);
	if (start_threads(&vars, philos))
		return (0);
	while (check_philo_status())
		continue;
}

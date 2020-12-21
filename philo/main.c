/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 11:21:16 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 09:14:03 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philosopher.h"

int	create_threads()
{
	// create threads
		// create a thread for every philo and safe this thread to the struct
}

int	eat_function()
{
	// start eating
		// pass to the start eating via threadfunction
		// check if two forks are available
			// if yes start eating
				// eat as long as specified in the struct
				// create message saying: timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
			// if no wait until they become available
	// stop eating
		// drop forks
}

int	sleep_function()
{
	// start sleeping
		// sleep as long as the time suggests
}

int	think_function()
{
	// start thinking
}

// change this to command line args in future
int main(int argc, char **argv)
{
	t_function_vars *vars;
	t_philo			*philo;
	// check the inputs
	if (validate_inputs(argc, argv, vars))
		return(0);
	// set up the mallocing of the philo's
	if (create_philo(vars, philo))
		return(0); // something went wrong during malloc 
	// create and activate the forks
	if (create_forks(vars))
		// something went wrong while creating threads
	if (init_philo(&philo))
		//
	if (start_threads())
		
	if (check_philo_status())
}

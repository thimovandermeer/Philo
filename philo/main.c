/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/11 11:21:16 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/14 09:10:04 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


void	validate_inputs()
{
	// validate inputs
		// check if everything is only digits
		// check overflows
		// number of philo's not smaller than 2
		// time to die not smaller than 0
		// time to eat not smaller than 0
		// time to sleap not smaller than 0
		// times to eat nog smaller than 0 (only when its given)
	
}

void	create_philo()
{
	// create philo's
		// create struct per philo which holds all the times and its ID (see philo.h)
		// create one struct with all the arguments because a threaded function can only hold one argument
		// create one array with all the above named structs to iterate over
}

void	create_threads()
{
	// create threads
		// create a thread for every philo and safe this thread to the struct
}

void	eat_function()
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

void	sleep_function()
{
	// start sleeping
		// sleep as long as the time suggests
}

void	think_function()
{
	// start thinking
}

// change this to command line args in future
void 	philo_one(int number_of_philosopers, int time_to_die, int time_to_eat, int time_to_sleap, int number_of_times_each_philosoper_must_eat)
{
	validate_inputs();
	create_philo();
	create_threads();
	eat_function();
	sleep_function();
	think_function();
	

}

int main()
{
	int number_of_philosopers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleap;
	int number_of_times_each_philosoper_must_eat;
	
	philo_one(number_of_philosopers, time_to_die, time_to_eat, time_to_sleap, number_of_times_each_philosoper_must_eat);
}
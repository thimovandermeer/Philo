/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_philos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:08:29 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 13:04:11 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		create_philo(t_function_vars *vars, t_philo **philos)
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
	(*philos) = malloc(sizeof(t_philo) * vars->n_philos);
	if (!philos)
	{
		ft_putstr_fd("something went wrong during mallocing individual philo's\n", 2);
		// i suppose i have to delete something here in the near future;
		return(1);
	}
}

int		create_forks(t_function_vars *vars, t_philo *philos)
{
	int i;

	i = 0;
	while(i < vars->n_philos)
	{
		if(pthread_mutex_init(&(*vars).forks[i], NULL) != 0)
		{
			// free forks I suppose
			return (1);
		}
		i++;
	}
	if(pthread_mutex_init(&(*vars).write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&(*vars).write_lock);
		return(1);
	}
	return (0);
}

int		init_philo(t_function_vars *vars, t_philo *philos)
{
	int i;
 
	i = 0;
	while(i < vars->n_philos)
	{
		philos[i].philo_num = i;
		philos[i].last_eaten = vars->start_time;
		philos[i].times_eaten = 0;
		philos[i].vars = vars;
		// here we need to have some time management as well
		i++;
	}
}

// in this function the thread will be started and the threading function is called
int 	start_treads(t_function_vars *vars, t_philo *philos)
{
	// activate thread
	int 	i;
	int		err;

	i = 0;
	while(i < vars->n_philos)
	{
		err = pthread_create(&(philos[i].thread), NULL, philo_loop, &philos);
		if (err != 0)
		{
			ft_putstr_fd("something went wrong during the ceation of threads\n", 2);
			return(1);
		}
		i++;
	}
	return(0);
}

void	write_lock(t_function_vars *vars, unsigned int id)
{
	unsigned long time;
	time = gettime();
	// lock the write thread so only this philo can write
	pthread_mutex_lock(&vars->write_lock);
	// thinking
	// write about the is thinking part 
	ft_putnbr_fd(time, 2);
	ft_putstr_fd(" [", 2);
	ft_putnbr_fd(id, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd("is thinkig \n", 2);
	// unlockt the write thread so other can use it again
	pthread_mutex_unlock(&vars->write_lock);
}

void	eat_lock()
{
	// check if there are forks available

	// lock left and right fork

	// eat for the given time
		// check time when this function is started
		// check time after one loop
		// new time minus old time and compair this to the needed eating time
		
}

// this function is where the magic happens for every individual philo
void	philo_loop(void *phil_ptr)
{
	unsigned int 	id;
	t_philo			*philo;
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*right_fork;
	// dereference philo_ptr so you can use it again
	philo = (t_philo*)phil_ptr;
	// set id again so you can check which one it is
	id = philo->philo_num;
	// check for left fork
	left_fork = &philo->vars->forks[id];
	// check for right fork
	right_fork = &philo->vars->forks[id + 1];
	// put half of the philosopers to sleep for some time so the other half can use half the forks
	if (id % 2)
		usleep(200);
	int i;
	i = 0;
	// loop for at least the time they have to eat (if this number is given)
	while(i < philo->vars->a_eat)
	{
		//  create a write lock for the is thinking part
		write_lock(philo->vars, id);
		// eating 
		eat_lock();
		// in here we check if there are resources available for the philo to use 
		// if there are no resources available to use then they wait until they become available
		// 
		// sleeping
		
		
		
		// eating

		// continously check if someone died
	}
	
	
}

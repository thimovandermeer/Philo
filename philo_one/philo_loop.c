/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 13:51:03 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 14:37:31 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	write_lock(t_function_vars *vars, unsigned int id, char *str)
{
	unsigned long time;

	time = gettime();
	pthread_mutex_lock(&vars->write_lock);
	ft_putnbr_fd(time, 2);
	ft_putstr_fd(" [", 2);
	ft_putnbr_fd(id, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	pthread_mutex_unlock(&vars->write_lock);
}

void	eat_lock(t_philo *philo, pthread_mutex_t *left_fork,
		pthread_mutex_t *right_fork, unsigned int id)
{
	pthread_mutex_lock(left_fork);
	write_lock(philo->vars, id, "Picked up left fork");
	pthread_mutex_lock(right_fork);
	write_lock(philo->vars, id, "Picked up right fork");
	philo->last_eaten = gettime();
	write_lock(philo->vars, id, "is eating");
	waitingfunction(philo->vars->t_sleep);
	pthread_mutex_unlock(left_fork);
	write_lock(philo->vars, id, "Dropped left fork");
	pthread_mutex_unlock(right_fork);
	write_lock(philo->vars, id, "Dropped right fork");
}

void	sleep_lock(t_philo *philo, unsigned int id)
{
	write_lock(philo->vars, id, "is sleeping");
	waitingfunction(philo->vars->t_sleep);
}

void	waitingfunction(unsigned int waitingtime)
{
	unsigned long starttime;

	starttime = gettime();
	while (gettime() - starttime < waitingtime)
		usleep(200);
}

void	death_lock()
{
	
}

void	*philo_loop(void *phil_ptr)
{
	unsigned int	id;
	t_philo			*philo;
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*right_fork;
	unsigned int	i;

	philo = (t_philo*)phil_ptr;
	id = philo->philo_num;
	left_fork = &philo->vars->forks[id];
	right_fork = &philo->vars->forks[id + 1];
	if (id % 2)
		usleep(200);
	i = 0;
	while (i < philo->vars->a_eat)
	{
		write_lock(philo->vars, id, "is thinking");
		eat_lock(philo, left_fork, right_fork, id);
		sleep_lock(philo, id);
		death_lock();
	}
	return (0);
}

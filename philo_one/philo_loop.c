/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 13:51:03 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/05 07:42:30 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	write_lock(t_function_vars *vars, unsigned int id, char *str)
{
	unsigned long time;

	time = gettime() - vars->start_time;
	pthread_mutex_lock(&vars->write_lock);
	if (vars->isdead == true)
	{
		pthread_mutex_unlock(&vars->write_lock);
		return ;
	}
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
	philo->times_eaten++;
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
	while ((gettime() - starttime) < waitingtime)
		usleep(100);
}

int		death_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->dead_lock);
	if (philo->vars->isdead)
	{
		pthread_mutex_unlock(&philo->vars->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->vars->dead_lock);
	return (0);
}

void	*philo_loop(void *phil_ptr)
{
	int				id;
	t_philo			*philo;
	pthread_mutex_t *left_fork;
	pthread_mutex_t	*right_fork;
	int				i;

	philo = (t_philo*)phil_ptr;
	id = philo->philo_num;
	left_fork = &philo->vars->forks[id];
	right_fork = &philo->vars->forks[(id + 1) % philo->vars->n_philos];
	if (id % 2)
		usleep(100);
	i = 0;
	while (i != philo->vars->a_eat)
	{
		if (i)
			write_lock(philo->vars, id, "is thinking");
		eat_lock(philo, left_fork, right_fork, id);
		sleep_lock(philo, id);
		if (death_lock(philo))
			return (NULL);
		i++;
	}
	return (NULL);
}

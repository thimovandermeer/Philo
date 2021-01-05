/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 13:51:03 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/05 09:42:15 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_lock(t_function_vars *vars, unsigned int id, char *str)
{
	unsigned long time;

	time = gettime() - vars->start_time;
	sem_wait(vars->write_lock);
	if (vars->isdead == true)
	{
		sem_post(vars->write_lock);
		return ;
	}
	ft_putnbr_fd(time, 2);
	ft_putstr_fd(" [", 2);
	ft_putnbr_fd(id, 2);
	ft_putstr_fd("] ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	sem_post(vars->write_lock);
}

void	eat_lock(t_philo *philo, unsigned int id)
{
	sem_wait(philo->vars->forks);
	write_lock(philo->vars, id, "Picked up first fork");
	sem_wait(philo->vars->forks);
	write_lock(philo->vars, id, "Picked up second fork");
	philo->last_eaten = gettime();
	philo->times_eaten++;
	write_lock(philo->vars, id, "is eating");
	waitingfunction(philo->vars->t_eat);
	sem_post(philo->vars->forks);
	write_lock(philo->vars, id, "Dropped first fork");
	sem_post(philo->vars->forks);
	write_lock(philo->vars, id, "Dropped second fork");
}

void	sleep_lock(t_philo *philo, unsigned int id)
{
	write_lock(philo->vars, id, "is sleeping");
	waitingfunction(philo->vars->t_sleep);
}

int		death_lock(t_philo *philo)
{
	sem_wait(philo->vars->dead_lock);
	if (philo->vars->isdead)
	{
		sem_post(philo->vars->dead_lock);
		return (1);
	}
	sem_post(philo->vars->dead_lock);
	return (0);
}

void	*philo_loop(void *phil_ptr)
{
	int				id;
	t_philo			*philo;
	int				i;

	philo = (t_philo*)phil_ptr;
	id = philo->philo_num;
	if (id % 2)
		usleep(200);
	i = 0;
	while (i != philo->vars->a_eat)
	{
		if (i)
			write_lock(philo->vars, id, "is thinking");
		eat_lock(philo, id);
		sleep_lock(philo, id);
		if (death_lock(philo))
			return (NULL);
		i++;
	}
	return (NULL);
}

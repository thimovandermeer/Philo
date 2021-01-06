/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_philos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/21 08:08:29 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/06 10:40:04 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		create_philo(t_function_vars *vars, t_philo **philos, pid_t **pids)
{
	(*philos) = malloc(sizeof(t_philo) * vars->n_philos);
	if (!philos)
	{
		ft_putstr_fd("something went wrong during mallocing philo's\n", 2);
		return (1);
	}
	(*pids) = malloc(sizeof(pid_t) * vars->n_philos);
	if (!pids)
	{
		free(*philos);
		return (1);
	}
	return (0);
}

int		init_philo(t_function_vars *vars, t_philo *philos)
{
	int i;

	i = 0;
	while (i < vars->n_philos)
	{
		philos[i].philo_num = i;
		philos[i].last_eaten = vars->start_time;
		philos[i].times_eaten = 0;
		philos[i].vars = vars;
		i++;
	}
	return (0);
}

int		check_philo(t_philo philo)
{
	bool stop;

	stop = false;
	sem_wait(philo.dead_lock);
	if (gettime() - philo.last_eaten > philo.vars->t_die)
	{
		if (philo.times_eaten != philo.vars->a_eat)
		{
			write_lock(philo.vars, philo.philo_num, "Has died");
			sem_wait(philo.vars->write_lock);
			philo.vars->isdead = true;
			exit(1);
		}
		stop = true;
	}
	sem_post(philo.dead_lock);
	usleep(200);
	if (stop)
		return (1);
	return (0);
}

void	philo_start(t_philo philo)
{
	pthread_t		thread;

	philo.dead_lock = sem_open("dead_lock", O_CREAT | O_EXCL, 0644, 1);
	if (philo.dead_lock == SEM_FAILED)
		exit(1);
	sem_unlink("dead_lock");
	if (pthread_create(&thread, NULL, philo_loop, &philo))
		exit(1);
	while (!check_philo(philo))
		continue;
	pthread_join(thread, NULL);
	exit(0);
}

void	start_processes(t_function_vars *vars, t_philo *philos, pid_t *pids)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < vars->n_philos)
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			philo_start(philos[i]);
		else
			pids[i] = pid;
		usleep(10);
		i++;
	}
}

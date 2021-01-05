/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 08:41:27 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/05 15:41:04 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>

typedef struct	s_function_vars
{
	int					n_philos;
	int					t_eat;
	int					t_sleep;
	long				t_die;
	int					a_eat;
	unsigned long		start_time;
	sem_t				*forks;
	sem_t				*write_lock;

	bool				isdead;
}				t_function_vars;

typedef struct	s_philo
{
	int				philo_num;
	long			last_eaten;
	int				times_eaten;
	sem_t			*dead_lock;
	t_function_vars	*vars;
}				t_philo;

/*
** util functions
*/

long			gettime(void);
void			ft_putnbr_fd(unsigned long n, int fd);

/*
** validate inputs
*/

void			set_philos(t_function_vars *vars, char **input, int argc);
int				validate_inputs(int argc, char **input, t_function_vars *vars);

/*
** create philo's
*/

int				create_philo(t_function_vars *vars,
				t_philo **philos, pid_t **pids);
int				init_philo(t_function_vars *vars, t_philo *philos);
void			start_processes(t_function_vars *vars,
				t_philo *philos, pid_t *pids);
void			jointhreads(t_philo *philos, int i);
/*
** philo_loop
*/

void			write_lock(t_function_vars *vars,
				unsigned int id, char *str);
void			eat_lock(t_philo *philo, unsigned int id);
void			sleep_lock(t_philo *philo, unsigned int id);
void			*philo_loop(void *phil_ptr);
void			waitingfunction(unsigned int waitingtime);

/*
** Free functions
*/

void			free_sems(t_function_vars *vars);
void			free_philos(t_philo *philos);
int				create_sems(t_function_vars *vars, t_philo *philos);

/*
** libft functions
*/

int				ft_isdigit(int c);
int				ft_atoi(char *str);
size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
#endif
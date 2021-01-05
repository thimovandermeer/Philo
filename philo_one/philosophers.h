/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: thvan-de <thvan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 08:41:27 by thimovander   #+#    #+#                 */
/*   Updated: 2021/01/05 09:31:28 by thvan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_function_vars
{
	int					n_philos;
	int					t_eat;
	int					t_sleep;
	long				t_die;
	int					a_eat;
	unsigned long		start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		dead_lock;
	bool				isdead;
}				t_function_vars;

typedef struct	s_philo
{
	int					philo_num;
	long				last_eaten;
	int					times_eaten;
	pthread_t			thread;
	pthread_mutex_t		time_lock;
	t_function_vars		*vars;
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
void			waitingfunction(unsigned int waitingtime);

/*
** create philo's
*/

int				create_philo(t_function_vars *vars, t_philo **philos);
int				create_forks(t_function_vars *vars);
int				init_philo(t_function_vars *vars, t_philo *philos);
int				start_threads(t_function_vars *vars, t_philo *philos);
void			jointhreads(t_philo *philos, int i);
/*
** philo_loop
*/

void			write_lock(t_function_vars *vars,
				unsigned int id, char *str);
void			eat_lock(t_philo *philo, pthread_mutex_t *left_fork,
				pthread_mutex_t *right_fork, unsigned int id);
void			sleep_lock(t_philo *philo, unsigned int id);
void			*philo_loop(void *phil_ptr);

/*
** Free functions
*/

void			free_dead_lock(t_function_vars *vars);
void			free_write_lock(t_function_vars *vars);
void			free_time_lock(t_function_vars *vars, t_philo *philos, int i);
void			free_forks(t_function_vars *vars);
void			free_philos(t_philo *philos);

/*
** libft functions
*/

int				ft_isdigit(int c);
int				ft_atoi(char *str);
size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
#endif

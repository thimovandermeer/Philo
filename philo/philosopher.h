/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 08:41:27 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 09:07:23 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
// struct per philo
typedef struct s_philo
{
	// philo number is the index of this particular philo
	unsigned int 	philo_num;
	// last eaten contains the time this philo has last eaten
	unsigned long 	last_eaten;
	// int times_eaten this var contains the number of times the philo has eaten
	unsigned int	times_eaten;
	// thread init here the threads are being initialised for the first time
	pthread_t		thread;
}				t_philo;

// main struct for passing to thread functions
typedef struct s_function_vars
{
	unsigned int 		n_philos;
	// int time to eat
	unsigned int 		t_eat;
	// int time to sleep
	unsigned int 		t_sleep;
	// int time to die
	unsigned int 		t_die;
	// int number of times each philo should eat
	unsigned int 		a_eat;
	// amount of forks;
	phthread_mutex_t 	*forks;
	t_philo				*philos;
}				t_function_vars;
	
/*
* util functions
*/

int		ft_isdigit(int c);
int		ft_atoi(char *str);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

/*
* validate inputs
*/

void 	set_philos(t_function_vars *vars, char **input, int argc);
int		validate_inputs(int argc , char **input, t_function_vars *vars);

/*
* create philo's
*/
int		create_philo(t_function_vars *vars, t_philo **philo);
int		create_forks(t_function_vars *vars);
int		init_philo(t_function_vars *vars, t_philo **philo);

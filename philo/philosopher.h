/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: thimovandermeer <thimovandermeer@studen      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/14 08:41:27 by thimovander   #+#    #+#                 */
/*   Updated: 2020/12/21 12:51:16 by thimovander   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
// struct per philo
typedef struct s_philo
{
	unsigned int 	philo_num;
	unsigned long 	last_eaten;
	unsigned int	times_eaten;
	pthread_t		thread;
	t_function_vars	*vars;
}				t_philo;

// main struct for passing to thread functions
typedef struct s_function_vars
{
	// isdead boolean mutex lock hier ook voor gebruiken
	
	unsigned int 		n_philos;
	unsigned int 		t_eat;
	unsigned int 		t_sleep;
	unsigned int 		t_die;
	unsigned int 		a_eat;
	unsigned long		start_time;
	pthread_mutex_t 	*forks;
	pthread_mutex_t		write_lock;
	// write mutex hier bouwen
}				t_function_vars;
	
/*
* util functions
*/

int				ft_isdigit(int c);
int				ft_atoi(char *str);
size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
unsigned long	gettime(void);
void			ft_putnbr_fd(int n, int fd);

/*
* validate inputs
*/

void 	set_philos(t_function_vars *vars, char **input, int argc);
int		validate_inputs(int argc , char **input, t_function_vars *vars);

/*
* create philo's
*/
int		create_philo(t_function_vars *vars, t_philo **philos);
int		create_forks(t_function_vars *vars, t_philo *philos);
int		init_philo(t_function_vars *vars, t_philo *philos);
int 	start_treads(t_function_vars *vars, t_philo *philos);

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_arg
{
	int				philo;
	long long int	eat_time;
	long long int	die_time;
	long long int	sleep_time;
	long long int	eat_count;
}			t_arg;

typedef struct s_philo
{
	int				number;
	int				*die;
	long long int	*eat_number;
	unsigned long	time;
	int				**eat;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long long int	sleep_start;
	long long int	eat_start;
	long long int	eat_count;
	t_arg			arg;
}					t_philo;

unsigned long	get_time(void);
void			ft_sleep(long long int time);
void			ft_exit(t_philo	**philo);
void			ft_die(t_philo	**philo);
int				ft_print_utils(t_philo *philo, int i);
int				ft_print(t_philo *philo, int i);
void			*simulation(void *a);
long long int	int_init(char *argv);
int				init_arg(t_arg *arg, int args, char **argv);
int				init_philo_params(t_arg arg, t_philo **philo,
					pthread_mutex_t **fort, int i);
void			ft_start_thread(t_arg arg, t_philo **philo);
int				init_philo(t_arg arg);
int				main(int args, char **argv);

#endif

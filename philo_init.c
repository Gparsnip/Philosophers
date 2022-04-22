
#include "philo.h"

long long int	int_init(char *argv)
{
	long int	mean;
	int			j;

	j = 0;
	mean = 0;
	while (argv[j] != '\0')
	{
		if (argv[j] >= '0' && argv[j] <= '9')
		{
			mean *= 10;
			mean = mean + ((argv[j] - '0'));
		}
		else
			return (-1);
		j++;
	}
	return (mean);
}

int	init_arg(t_arg *arg, int args, char **argv)
{
	(*arg).philo = int_init(argv[1]);
	(*arg).die_time = int_init(argv[2]);
	(*arg).eat_time = int_init(argv[3]);
	(*arg).sleep_time = int_init(argv[4]);
	if (args == 6)
		(*arg).eat_count = int_init(argv[5]);
	else
		(*arg).eat_count = -2;
	if ((*arg).philo == -1 || (*arg).die_time == -1 || (*arg).eat_count == -1
		|| (*arg).eat_time == -1 || (*arg).sleep_time == -1)
		return (0);
	if ((*arg).philo == 0 || (*arg).eat_count == 0)
		return (0);
	return (1);
}

int	init_philo_params(t_arg arg, t_philo **philo,
pthread_mutex_t	**fort, int i)
{
	int				*die;
	long long int	*eat_count;

	die = malloc(sizeof(int));
	eat_count = malloc(sizeof(long long int));
	if (!die || !eat_count)
		return (0);
	*eat_count = (long long int)arg.philo;
	*die = 0;
	while (i != arg.philo)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].left_fork = &((*fort)[i]);
		(*philo)[i].die = die;
		(*philo)[i].time = get_time();
		(*philo)[i].eat_number = eat_count;
		(*philo)[i].eat_start = get_time();
		if (i + 1 == arg.philo)
			(*philo)[i].right_fork = &((*fort)[0]);
		else
			(*philo)[i].right_fork = &((*fort)[i + 1]);
		(*philo)[i].number = i;
		i++;
	}
	return (1);
}

int	init_philo(t_arg arg)
{
	t_philo			*philo;
	pthread_mutex_t	*fort;
	int				i;

	i = 0;
	philo = malloc(sizeof(t_philo) * arg.philo);
	fort = malloc(sizeof(pthread_mutex_t) * arg.philo);
	if (!philo || !fort)
		return (0);
	while (i != arg.philo)
	{
		if (pthread_mutex_init(&fort[i], NULL) != 0)
			return (0);
		i++;
	}
	if (init_philo_params(arg, &philo, &fort, 0) == 0)
		return (0);
	ft_start_thread(arg, &philo);
	ft_die(&philo);
	usleep(10000);
	free(fort);
	free(philo);
	return (1);
}

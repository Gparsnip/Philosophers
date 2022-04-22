
#include "philo.h"

unsigned long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(long long int time)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < (unsigned long)time)
		usleep(100);
}

void	ft_exit(t_philo	**philo)
{
	int	i;

	i = 0;
	free((*philo)[0].eat_number);
	free((*philo)[0].die);
	while (i != (*philo)[0].arg.philo)
	{
		pthread_mutex_destroy((*philo)[i].left_fork);
		i++;
	}
}

int	main(int args, char **argv)
{
	t_arg	arg;

	if (args != 5 && args != 6)
	{
		printf("Error\nInvalid number of arguments\n");
		return (0);
	}
	if (init_arg(&arg, args, argv) == 0)
	{
		printf("Error\nError in arguments\n");
		return (0);
	}
	if (init_philo(arg) == 0)
	{
		printf("Error\nMemory allocation error\n");
		return (0);
	}
	return (1);
}

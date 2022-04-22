
#include "philo.h"

void	ft_start_thread(t_arg arg, t_philo **philo)
{
	int	i;

	i = 0;
	while (i != arg.philo)
	{
		if (i % 2 == 0)
			pthread_create(&(((*philo)[i]).philo), NULL,
				simulation, &(*philo)[i]);
		i++;
	}
	usleep(100);
	i = 0;
	while (i != arg.philo)
	{
		if (i % 2 == 1)
			pthread_create(&(((*philo)[i]).philo), NULL,
				simulation, &(*philo)[i]);
		i++;
	}
	i = 0;
	while (i != arg.philo)
	{
		pthread_detach((*philo)[i].philo);
		i++;
	}
}

void	*simulation(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	while ((*(*philo).die) != 1)
	{
		if ((*philo).number % 2 != 1)
		{
			pthread_mutex_lock((*philo).left_fork);
			ft_print(philo, 0);
			pthread_mutex_lock((*philo).right_fork);
			ft_print(philo, 0);
		}
		else if ((*philo).number % 2 != 0)
		{
			pthread_mutex_lock((*philo).right_fork);
			ft_print(philo, 0);
			pthread_mutex_lock((*philo).left_fork);
			ft_print(philo, 0);
		}
		ft_print(philo, 1);
		ft_print_utils(philo, 2);
		ft_print_utils(philo, 3);
	}
	return (NULL);
}

int	ft_print(t_philo *philo, int i)
{
	unsigned long	time;

	time = get_time() - (*philo).time;
	if ((*(*philo).die) == 1)
		return (0);
	if (i == 0)
	{
		if ((*(*philo).die) != 1)
			printf ("%lums %d has taken a fork\n", time, (*philo).number + 1);
	}
	if (i == 1)
	{
		printf ("%lums %d is eating\n", time, (*philo).number + 1);
		(*philo).eat_start = get_time();
		ft_sleep((*philo).arg.eat_time);
		pthread_mutex_unlock((*philo).left_fork);
		pthread_mutex_unlock((*philo).right_fork);
		(*philo).arg.eat_count--;
		if ((*philo).arg.eat_count == 0)
			(*(*philo).eat_number)--;
	}
	return (0);
}

int	ft_print_utils(t_philo *philo, int i)
{
	unsigned long	time;

	time = get_time() - (*philo).time;
	if ((*(*philo).die) == 1)
		return (0);
	if (i == 2)
	{
		printf ("%lums %d is sleeping\n", time, (*philo).number + 1);
		ft_sleep((*philo).arg.sleep_time);
	}
	if (i == 3)
	{
		printf ("%lums %d is thinking\n", time, (*philo).number + 1);
		usleep(500);
	}
	return (0);
}

void	ft_die(t_philo	**philo)
{
	int					i;
	unsigned long		time;
	unsigned long		time_die;

	i = 0;
	while (*(*philo)[0].die != 1)
	{
		i = 0;
		while (i != (*philo)[0].arg.philo)
		{
			time_die = get_time() - (*philo)[i].eat_start;
			if ((time_die >= (unsigned long)(*philo)[i].arg.die_time
				&& (*(*philo)[i].die) != 1) || *((*philo)[i].eat_number) == 0)
			{
				(*(*philo)[i].die) = 1;
				time = get_time() - (*philo)[i].time;
				usleep(1000);
				if ((*(*philo)[i].eat_number) != 0)
					printf("%lums %d died\n", time, (*philo)[i].number + 1);
			}
			i++;
		}
		usleep(100);
	}
	ft_exit(philo);
}

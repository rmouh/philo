#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

int	ft_sleep(t_philo *philo)
{
	if (ft_check_status(philo) != 0)
		return (-1);
	if (ft_update_time(philo) != 0)
		return (-1);
	int time = ft_get_time(philo);
	pthread_mutex_lock(&philo->data->print);
	printf("[%7dms] %3d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);

	if (usleep(philo->data->time_to_sleep * 1000) != 0)
		return (-1);
	if (ft_update_time(philo) != 0)
		return (-1);
	if (ft_check_status(philo) != 0)
		return (-1);
	time = ft_get_time(philo);
	pthread_mutex_lock(&philo->data->print);
	printf("[%7dms] %3d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}
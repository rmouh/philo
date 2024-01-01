#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

void	ft_lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->next_philo->fork);
	pthread_mutex_lock(&philo->fork);
}

void	ft_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->next_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

int	ft_check_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->exit);
	if (philo->exit_code != 0)
	{
		pthread_mutex_unlock(&philo->exit);
		return (-1);
	}
	pthread_mutex_unlock(&philo->exit);
	return (0);
}

int take_fork (t_philo *philo)
{
	ft_lock_forks(philo);
	if (ft_check_status(philo) != 0)//peurt pas manger si il a fini /mort /sleeping
	{
		ft_unlock_forks(philo);
		return (-1);
    }
	if (ft_update_time(philo) != 0)//
	{
		ft_unlock_forks(philo);
		return (-1);
	}
    int time = ft_get_time(philo);
    pthread_mutex_lock(&philo->data->print);
	printf("[%7dms] %3d has taken fork!\n", time , philo->id);
    pthread_mutex_unlock(&philo->data->print);
	return (0);
}
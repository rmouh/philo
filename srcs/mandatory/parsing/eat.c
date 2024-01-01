#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

void	ft_update_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	philo->time_to_eat = philo->current_time;
	pthread_mutex_unlock(&philo->meal);
}

int ft_eat(t_philo *philo)
{
	if (ft_check_status(philo) != 0)
		return (ft_unlock_forks(philo), -1);
    if (ft_update_time(philo) != 0)
		return (ft_unlock_forks(philo), -1);
	int time = ft_get_time(philo);
	pthread_mutex_lock(&philo->data->print);
	printf("[%7dms] %3d is eating\n",time , philo->id);
	pthread_mutex_unlock(&philo->data->print);
	philo->current_meal++;
	if (philo->current_meal == philo->data->nb_of_meals)
	{
		pthread_mutex_lock(&philo->exit);
		philo->exit_code = -4;
		pthread_mutex_unlock(&philo->exit);
	}
	ft_update_time_last_meal(philo);
	if (usleep(philo->data->time_to_eat * 1000) != 0)
		return (ft_unlock_forks(philo), -1);

		// return (ft_update_time(philo),ft_unlock_forks(philo), -1);
	// usleep(philo->data->time_to_eat * 1000);
			// printf("current time %d\n", philo->current_time);
	// ft_update_time(philo);
			// printf("current time after update eat %d\n", philo->current_time);
	// return (ft_update_time(philo), ft_unlock_forks(philo), 0);
	return (ft_unlock_forks(philo), 0);
}
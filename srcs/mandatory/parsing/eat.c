#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

void	ft_update_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	philo->last_time_meal = philo->current_time;
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
	// printf("[%7dms] %3d is eating\n",time , philo->id);
	philo_print(" is eating", philo,1);

	pthread_mutex_unlock(&philo->data->print);
	// pthread_mutex_lock(&philo->meal);
	philo->current_meal++;
	// pthread_mutex_unlock(&philo->meal);
	if (philo->current_meal == philo->data->nb_of_meals)
	{
		pthread_mutex_lock(&philo->exit);
		philo->exit_code = -4;
		pthread_mutex_unlock(&philo->exit);
	}
	ft_update_time_last_meal(philo);
	if (usleep(philo->data->time_to_eat * 1000) != 0)
		return (ft_unlock_forks(philo), -1);
	return (ft_unlock_forks(philo), 0);
}
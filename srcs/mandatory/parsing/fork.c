#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
void	philo_print(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;
    long int time;

    time =(gettime() - philo->data->general_time);
	timestamp = ft_itoa(time);
    philo->current_time = time;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld [%d] %s\n", time, philo->id, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->data->print);
	free(timestamp);
}
long int	philo_printf(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;
    long int time;

    time =(gettime() - philo->data->general_time);
	timestamp = ft_itoa(time);
    // philo->current_time = time;
    // printf("current time = %ld\n", philo->current_time);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld [%d] %s\n", time, philo->id, msg);
    printf("%ld [%d] %s\n", time, philo->id, "is eating");
	if (unlock)
		pthread_mutex_unlock(&philo->data->print);
	free(timestamp);
    return (time);
}

long int	ft_lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next_philo->fork);
    return( philo_printf(" has taken a fork ", philo,1));
    // philo_print(" is eating", philo,1);
}

void	ft_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next_philo->fork);
}

int	ft_check_status(t_philo *philo)
{
    int tmp;

	pthread_mutex_lock(&philo->data->exit);
    pthread_mutex_lock(&philo->exit);
    tmp = philo->data->exit_var;
	if (tmp == 1 || philo->exit_code != 0)
	{
		pthread_mutex_unlock(&philo->data->exit);
		pthread_mutex_unlock(&philo->exit);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->exit);
	pthread_mutex_unlock(&philo->exit);
	return (0);
}

long int take_fork (t_philo *philo)
{
	long int y = ft_lock_forks(philo);
	if (ft_check_status(philo) != 0)//peurt pas manger si il a fini /mort /sleeping
	{
		ft_unlock_forks(philo);
		return (-1);
    }
	// if (ft_update_time(philo) != 0)//
	// {
	// 	ft_unlock_forks(philo);
	// 	return (-1);
	// }
    // pthread_mutex_lock(&philo->data->print);
    // ft_update_time(philo);
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
	return (ft_unlock_forks(philo),y );
    
    
	// return (0);
}
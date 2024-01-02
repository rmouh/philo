#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

void	philo_prints(char *msg, t_philo *philo, int unlock)
{
    long int time;

    time  = philo->current_time + philo->data->time_to_eat;
	philo->current_time = time;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld [%d] %s\n", time, philo->id, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->data->print);
	// free(timestamp);
}
void	philo_printt(char *msg, t_philo *philo, int unlock)
{
	// char	*timestamp;
    long int time;

    // time =(gettime() - philo->data->general_time);
	// timestamp = ft_itoa(time);
    time  = philo->current_time + philo->data->time_to_sleep;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld [%d] %s\n", time, philo->id, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->data->print);
	// free(timestamp);
}
int	ft_sleep(t_philo *philo)
{
	if (ft_check_status(philo) != 0)
		return (-1);
	philo_prints(" is sleeping", philo,1);
	if (usleep(philo->data->time_to_sleep * 1000) != 0)
		return (-1);
	if (ft_check_status(philo) != 0)
		return (-1);
	// if (ft_update_time(philo) != 0)
	// 	return (-1);
	philo_printt(" is thinking", philo,1);
	
	// time = ft_get_time(philo);
	// pthread_mutex_lock(&philo->data->print);
	// printf("[%7dms] %3d is thinking\n", time, philo->id);
	// pthread_mutex_unlock(&philo->data->print);
	return (0);
}
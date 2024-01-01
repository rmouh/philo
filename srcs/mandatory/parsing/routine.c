#include "philo.h"
#include <stdio.h>
#include <sys/time.h>


int	ft_get_time(t_philo *philo)
{
	return (philo->current_time - philo->data->general_time);
}

int	ft_update_time(t_philo *philo)
{
	// philo->current_time = -1;
	if (gettimeofday(&philo->tv, NULL) != 0)
		return (-2);
	philo->current_time = (philo->tv.tv_sec * 1000) + (philo->tv.tv_usec / 1000);
	return (0);
}

int	ft_start_schedule(t_philo *philo)
{
	if (ft_update_time(philo) != 0)
	{
		printf("TIME ERROR\n");
		philo->exit_code = -2;
		return (-1);
	}
	// printf("%d", (philo->current_meal - philo->current_time) * 1000);
	// usleep((philo->current_meal - philo->current_time) * 1000);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_sleep * 1000);
	if (philo->data->nb_philo % 2 == 1)
		if (philo->id == philo->data->nb_philo)
			usleep(1000);
	return (0);
}

void	ft_handle_error_time(t_general *data)
{
	// pthread_mutex_lock(&data->exit);
	// data->time_error = -2;
	ft_set_all_statuses_2(data);
	// pthread_mutex_unlock(&data->exit);
}

// void ft_set_end_status(t_general *data)
// 	pthread_mutex_lock(&philo->exit);
// 	data->exit_code = 0;
// 	pthread_mutex_unlock(&philo->exit);
// }
void    *my_fonction(void *arg)
{
    t_philo *philo ;
    // write(2, "philo routine\n", 14);
    philo  = (t_philo *)arg;
	// printf("philo %d\n", philo->id);
    if (ft_start_schedule(philo) != 0)
		{
        return NULL;
		}
		// return (ft_handle_error(philo), NULL);
 
    while (1)
    {
        if (take_fork(philo) == -1)
            break;
        if(ft_eat(philo) == -1)
            break;
        if(ft_sleep(philo) == -1)
            break;
        
        // usleep(1000);
        // printf("time = %li\n", gettimstamp(philo->data));
        // pthread_mutex_lock(&(philo->data->print));
        // printf("time /gettime= %li\n", gettime());
        // pthread_mutex_unlock(&(philo->data->print));
    }
    if (philo->exit_code == -2)
		ft_handle_error_time(philo->data);
	    // ft_set_end_status(data);
    // exit(1);
    return NULL;
}	
#include "philo.h"
#include <stdio.h>
#include <sys/time.h>


int	ft_get_time(t_philo *philo)
{
	return (philo->current_time - philo->data->general_time);
}

int	ft_update_time(t_philo *philo)
{
	philo->current_time = gettime();
	return (0);
}

int	ft_start_schedule(t_philo *philo)
{
	ft_update_time(philo);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_sleep * 1000);
	// if (philo->data->nb_philo % 2 == 1)
	// 	if (philo->id == philo->data->nb_philo)
	// 		usleep(1000);
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
void	philo_printone(char *msg, t_philo *philo, int unlock)
{
    long int time;

    time  =  philo->data->time_to_die;
	philo->current_time = time;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld [%d] %s\n", time, philo->id, msg);
	if (unlock)
		pthread_mutex_unlock(&philo->data->print);
	// free(timestamp);
}

void	ft_handle_one_philo(t_philo *philo)
{
	usleep(philo->data->time_to_die * 1000 + 1000);
	philo_printone(" died ", philo,1);
}
void    *my_fonction(void *arg)
{
    t_philo *philo ;
	long int y;
    philo  = (t_philo *)arg;
    if (ft_start_schedule(philo) != 0)
        return NULL; 
	if(philo->data->nb_philo  == 1)
		return(ft_handle_one_philo(philo), NULL);
	
    while (1)
    {	
		y=take_fork(philo);
        if ((y== -1))
            break;
		philo->current_time = y;
        // if(ft_eat(philo) == -1)
        //     break;
		// y= 
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
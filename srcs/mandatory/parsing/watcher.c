#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

/*
exit code
 0 = ok 
-1 = error
-2 = time error
-3 = death of someone
-4 = all meals eaten all philos 


*/


int	ft_is_game_finished(t_general *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&(data->philo_tab[i].exit));
        i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo_tab[i].exit_code != -4)
			return (0);
        i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_unlock(&(data->philo_tab[i].exit));
        i++;
	}
	return (1);
}

int	ft_check_death(t_general *data,  int time)
{
	int	i;
    int time_meal;

	i = 0;
	while (i < data->nb_philo )
	{
		pthread_mutex_lock(&data->philo_tab[i].meal);
        time_meal = data->philo_tab[i].time_to_eat; 
		pthread_mutex_unlock(&data->philo_tab[i].meal);
        if (time - time_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->exit);
			ft_set_all_statuses_2(data);
			printf("[%7ldms] %3d died\n", time - data->general_time, data->philo_tab[i].id);
			pthread_mutex_unlock(&data->exit);
			return (0);
		}
		usleep(100);
		i++;
	}
	return (1);
}

void	ft_set_all_statuses_2(t_general *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&(data->philo_tab[i].exit));
        i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo_tab[i].exit_code = -3;
        i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_unlock(&(data->philo_tab[i].exit));
        i++;
	}
}
int ft_chrck_time(t_general *data)
{
    pthread_mutex_lock(&data->exit);
    if (data->time_error == -2)
    {
        printf("time error\n");
        ft_set_all_statuses_2(data);
        pthread_mutex_unlock(&data->exit);
        return (0);
    }
    pthread_mutex_unlock(&data->exit);
    return (1);
}

void ft_watch(t_general *data)
{
    struct timeval	tv;
	int				time;
    while (1)
    {
        if (gettimeofday(&tv, NULL) != 0)
            break ;
        time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
        if (ft_is_game_finished(data) == 1)
            break ;//partie fini tlmns a mange 
        if (ft_check_death(data, time) == 0)
                break ;
        if(ft_chrck_time(data) == 0)
        break;
    }
        // usleep(10000);
    
}


int	ft_close_threads( t_general *data)
{
	int		i;

	i = 0;
    for (int i = 0; i < data->nb_philo; i++)
        pthread_join(data->philo_tab[i].thread, NULL);
	free(data->philo_tab);
    free(data->tab);
    free(data);
    return (0);
}
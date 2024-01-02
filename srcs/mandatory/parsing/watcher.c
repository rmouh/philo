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
    int cpt = 0;

	// i = 0;
	// while (i < data->nb_philo)
	// {
	// 	pthread_mutex_lock(&(data->philo_tab[i].exit));
    //     printf("%d  took mutex exit \n", data->philo_tab[i].id);
    //     i++;
	// }
	i = 0;
	while (i < data->nb_philo)
	{
        pthread_mutex_lock(&(data->philo_tab[i].exit));
        // printf("%d  took mutex exit \n", data->philo_tab[i].id);
        // printf("%d  verified exit== %d \n", data->philo_tab[i].id, data->philo_tab[i].exit_code);
		if (data->philo_tab[i].exit_code == -4)
            cpt++;
		// {
        //     pthread_mutex_unlock(&(data->philo_tab[i].exit));
        // printf("%d  returend mutex exit \n", data->philo_tab[i].id);
        //     return (0);}
		pthread_mutex_unlock(&(data->philo_tab[i].exit));
        // printf("%d  returend mutex exit \n", data->philo_tab[i].id);
        i++;
	}
    return (cpt == data->nb_philo);
	// i = 0;
	// while (i < data->nb_philo)
	// {
	// 	pthread_mutex_unlock(&(data->philo_tab[i].exit));
    //     i++;
	// }
    // printf("all meals eaten\n");
	// return (1);

}

int	ft_check_death(t_general *data,  long int time)
{
	int	i;
    long int time_meal;

	i = 0;
	while (i < data->nb_philo )
	{
		pthread_mutex_lock(&data->philo_tab[i].meal);
        time_meal = data->philo_tab[i].last_time_meal; 
		pthread_mutex_unlock(&data->philo_tab[i].meal);
        // prin
        if (time - time_meal >= data->time_to_die)
		{
			pthread_mutex_lock(&data->exit);
			// ft_set_all_statuses_2(data);
            pthread_mutex_lock(&data->print);
            int tm = ft_get_time(&data->philo_tab[i]);
			printf("%ld [%d] has died\n", gettime() - data->general_time , data->philo_tab[i].id);
            pthread_mutex_unlock(&data->print);
			data->exit_var=1;
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
		data->philo_tab[i].exit_code = -2;
        i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_unlock(&(data->philo_tab[i].exit));
        i++;
	}
}
// int ft_chrck_time(t_general *data)
// {
//     pthread_mutex_lock(&data->exit);
//     if (data->time_error == -2)
//     {
//         printf("time error\n");
//         ft_set_all_statuses_2(data);
//         pthread_mutex_unlock(&data->exit);
//         return (0);
//     }
//     pthread_mutex_unlock(&data->exit);
//     return (1);
// }

void ft_watch(t_general *data)
{
    struct timeval	tv;
	long int				time;
    while (1)
    {
        if (gettimeofday(&tv, NULL) != 0)
            break ;
        time = gettime();
        // printf("watcher 1\n");
        if (ft_is_game_finished(data) == 1)
           {printf("all meals eaten\n");    
             break ;}//partie fini tlmns a mange 
        // printf("watcher2\n");
        if (ft_check_death(data, time) == 0)
                break ;
        // printf("watcher end \n");

        // if(ft_chrck_time(data) == 0)
        // break;
    }
    printf("end of game\n");
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
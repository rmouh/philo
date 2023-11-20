/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:22:45 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/11/20 16:47:52 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>

int is_not_integer(char *str)
{
    int		i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') || str[i] == '-')
			return (1);
		else
			i++;
	}
	return (0);
}
/*
    parse the nb of philo :
        their time to eat
        their tme to sleep
        their time to die
        

*/
int *parse_input(char *argv[], int size)
{
    int i;
    int *tab;

    i = 0;
    if (size != 4)
        return(write(2, "ERROR\n", 6), NULL);
    tab = (int*)ft_callloc_tab(size); 
    if (!tab)
        return NULL;   
    while(i < size)
    {
        if(is_not_integer(argv[i+1]))
            return (free(tab), write(2, "ERROR\n", 6), NULL);
        tab[i] = ft_atoi(argv[i+1]);
        i++;
    }
    return(tab);
} 
void    print_tab(int *tab, int size)
{
    int i;
    
    i = 0;
    while (i < size)
    {
        ft_printf("%d  ", tab[i]);
        i++;
    }
    printf("\n");
}

void free_data(t_general *data)
{
    free(data->tab);
    free(data->philo_tab);
}
void init_general(t_general *data, int size, char *argv[])
{
    // data = malloc(sizeof(t_general));
    struct timeval tv;
    if(!data)
        //return 
    data->tab = parse_input(argv, size);
    if (data->tab != NULL)
    //if parse faild has to free data 
    {
        data->nb_philo = data->tab[0];
        data->time_to_die = data->tab[1];
        data->time_to_eat = data->tab[2];
        data->time_to_sleep = data->tab[3];
        if (data->time_to_die <= data->time_to_eat + data->time_to_sleep)   
            //return(NULL, ft_printf("No enough time te eat and sleep !! add me some more\n"));
        if (gettimeofday(&tv, NULL)!= 0)
            return(NULL, ft_printf("timing wrong \n"));
        // data->general_time = 

    }
}
/*
    creating philos and initialising their data
    creating mutex for fork 
*/
int    create_philos(t_general *data)
{
    int i;
    
    i = 0;
    data->philo_tab = malloc(sizeof(t_philo )* data->nb_philo);
    if (!data->philo_tab)
        return(0);//have to free 
    printf("%i\n", data->nb_philo);
    while (i < data->nb_philo)
    {
        // data->philo_tab[i] = malloc(sizeof(t_philo));
        printf("i = %i\n", i);
        // prin
        data->philo_tab[i].id = i+1;
        data->philo_tab[i].time_to_die = data->tab[1];
        data->philo_tab[i].time_to_eat = data->tab[2];
        data->philo_tab[i].time_to_sleep = data->tab[3];
        if (i < data->nb_philo - 1)
            data->philo_tab[i].next_philo = &(data->philo_tab[i + 1]);
        else 
            data->philo_tab[i].next_philo = &(data->philo_tab[0]);
        if (pthread_mutex_init(&data->philo_tab[i].fork, NULL) != 0)
            return 0; 
        //if (pthread_mutex_init())
        i++;
    }
    return(1);
}
/*
    Hi im a philo and i'll try to :
        -take my two forks
        -eat 
        -sleep/
    if i cant take my forks;
        -I wait until i can /think
        -If my thinking time ends before i eat i DIE!!!!!


*/
void    *my_fonction(void *arg)
{
    t_philo *args;
    write(2, "philo routine\n", 14);
    args = (t_philo *)arg;
    if ()
    pthread_mutex_lock(&(args->fork));
    pthread_mutex_lock(&(args->next_philo->fork));
    exit(1);
    return NULL;
}
// void init_philo(t_general *data)
// {
//     int i;
    
//     i = 0;
//     while (i < data->nb_philo)
//     {
//         if (pthread_mutex_init(data->philo_tab[i].fork, NULL))
//             //return (free())
//     }
// }
/*
    I parse the input
    I create my general data
    I create my philo 
*/
int main(int argc, char *argv[])
{
    int i = 0;
    t_general   data;
    // data = malloc(sizeof(t_general));
    
    // data = NULL;
    //data = malloc(sizeof(t_general));
    //data->tab = parse_input(argv, argc-1);
    //print_tab(data->tab, argc-1);
    init_general(&data, argc-1, argv);
    printf("create philo = %i\n", create_philos(&data));
    while(i < data.nb_philo)
    {
        if (pthread_create(&data.philo_tab[i].thread, NULL, &my_fonction, &data.philo_tab[i]) != 0)
			break ;
		i++;
    }
    for (int i = 0; i < data.nb_philo; i++)
    {
        pthread_join(data.philo_tab[i].thread, NULL);
        /* code */
    }
    
    //have to destroy my mutex     pthread_mutex_destroy(&myMutex);
    // //have to join the threads 
    // free_data(data);
    return 1;
}
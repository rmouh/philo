/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:22:45 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/11/20 18:14:53 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>


long int	gettime(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

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
// void    print_tab(int *tab, int size)
// {
//     int i;
//     tab = 
    
//     i = 0;
//     while (i < size)
//     {
//         print_philo( tab[i]);
//         printf("\n");
//         // ft_printf("%d  ", tab[i]);
//         // i++;
//     }
//     printf("\n");
// }
void    print_philo(t_philo philo)
{
    ft_printf("philo N %d | time to eat  %d | time to sleep  %d | time to die  %d ", philo.id, philo.time_to_eat, philo.time_to_sleep, philo.time_to_die);
}
void    print_tab(t_general data)
{
    int i;
    t_philo *tab = data.philo_tab;
    
    i = 0;
    ft_printf("nb philos %d  \n", data.nb_philo);
    while (i < data.nb_philo)
    {
        print_philo( tab[i++]);
        printf("\n");
        // ft_printf("%d  ", tab[i]);
        // i++;
    }
    ft_printf("data philo N %d | time to eat  %d | time to sleep  %d | time to die  %d ", tab[1].id, tab[1].data->time_to_eat, tab[1].data->time_to_sleep,tab[1].data->time_to_die);

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
    // if(!data)
        //return 
    data->tab = parse_input(argv, size);
    //if parse faild has to free data 
    if (data->tab != NULL)
    {
        data->nb_philo = data->tab[0];
        data->time_to_die = data->tab[1];
        data->time_to_eat = data->tab[2];
        data->time_to_sleep = data->tab[3];
        pthread_mutex_init(&data->print, NULL);
            // return 0; 
            //return(NULL, ft_printf("No enough time te eat and sleep !! add me some more\n"));
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
        data->philo_tab[i].data = data;
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
    t_philo *philo ;
    write(2, "philo routine\n", 14);
    philo  = (t_philo *)arg;
    if (philo->id%2 == 0)
        usleep(1000);
    // while (1){
    //     // usleep(1000);
    // printf("time = %li\n", gettimstamp(philo->data));
    pthread_mutex_lock(&(philo->data->print));
    printf("time /gettime= %li\n", gettime());
    pthread_mutex_unlock(&(philo->data->print));
    // }
    
        
    // pthread_mutex_lock(&(philo->fork));
    // pthread_mutex_lock(&(philo->next_philo->fork));
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

long int	gettimstamp(t_general *data)
{
	struct timeval	current;

	return (((current.tv_sec * 1000) + (current.tv_usec / 1000) ) - (data->general_time));
}


// void print(char *msg, t_general *data)
// {
    
// }
int main(int argc, char *argv[])
{
    int i = 0;
    t_general   data;
    // data = malloc(sizeof(t_general));
    
    // data = NULL;
    //data = malloc(sizeof(t_general));
    //data->tab = parse_input(argv,
    //pthread_mutex_t my argc-1);
    //print_tab(data->tab, argc-1);
    init_general(&data, argc-1, argv);
    // printf("create philo = %i\n", create_philos(&data));
    create_philos(&data);
    print_tab(data);
    data.general_time = gettime();
    printf("time /gettime= %li\n", data.general_time);

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:25:02 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/11/20 17:11:33 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <threads.h>
#include <pthread.h>

typedef struct t_general t_general;

typedef struct s_philo
{
    int id;
    pthread_t thread;
    int last_time_meal;
    // int time_to_sleep;
    // int time_to_die;
    long int current_time;
    int current_meal;
    int exit_code;
    struct timeval	tv;
    pthread_mutex_t	fork;
    pthread_mutex_t exit;
    pthread_mutex_t meal;

    struct s_philo *next_philo;
    t_general *data;
    //pthread_mutex_t my_time;
}               t_philo;


typedef struct t_general
{
    int     *tab;
    int     nb_philo;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int nb_of_meals;
    int exit_var;
    pthread_mutex_t print;
    pthread_mutex_t exit;
    int time_error;
    long int general_time;
    t_philo *philo_tab;
    
}               t_general;
int *parse_input(char *argv[], int size);
int is_not_integer(char *str);
long int	gettime(void);



/*
    the routine of the philo
*/
void    ft_update_time_last_meal(t_philo *philo);
int     ft_eat(t_philo *philo);
void	philo_print(char *msg, t_philo *philo, int unlock);
int     ft_sleep(t_philo *philo);

long int    ft_lock_forks(t_philo *philo);
void    ft_unlock_forks(t_philo *philo);
int     ft_check_status(t_philo *philo);
long int     take_fork (t_philo *philo);

int     ft_get_time(t_philo *philo);
void    *my_fonction(void *arg);
int     ft_update_time(t_philo *philo);
long int    gettimstamp(t_general *data);

void	ft_handle_error_time(t_general *data);
int	ft_close_threads( t_general *data);
void ft_watch(t_general *data);
void	ft_set_all_statuses_2(t_general *data);
int	ft_check_death(t_general *data,  long int time);
int	ft_is_game_finished(t_general *data);
#endif
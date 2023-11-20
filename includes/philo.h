/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:25:02 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/11/20 16:19:51 by rmouhoub         ###   ########.fr       */
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
typedef struct s_philo
{
    int id;
    pthread_t thread;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    pthread_mutex_t	fork;
    struct s_philo *next_philo;
    //pthread_mutex_t my_time;
}               t_philo;


typedef struct s_general
{
    int     *tab;
    int     nb_philo;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    t_philo *philo_tab;
    
}               t_general;
int *parse_input(char *argv[], int size);
int is_not_integer(char *str);
#endif
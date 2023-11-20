/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:25:02 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/11/10 17:37:36 by rmouhoub         ###   ########.fr       */
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
    pthread_t id;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    pthread_mutex_t	fork;
    t_philo *next_philo;
    //pthread_mutex_t my_time;
}               t_philo;


typedef struct s_general
{
    int     *tab;
    int     nb_philo;
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    int general_time;
    t_philo *philo_tab;
    
}               t_general;
int *parse_input(char *argv[], int size);
int is_not_integer(char *str);
#endif
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
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
    pthread_mutex_t	fork;
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
    pthread_mutex_t print;
    long int general_time;
    t_philo *philo_tab;
    
}               t_general;
int *parse_input(char *argv[], int size);
int is_not_integer(char *str);
long int	gettime(void);
long int	gettimstamp(t_general *data);
#endif
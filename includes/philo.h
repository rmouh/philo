/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:25:02 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/11/04 12:31:03 by rmouhoub         ###   ########.fr       */
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
    int time_to_eat;
    int time_to_sleep;
    int time_to_die;
}               t_philo;


typedef struct s_general
{
    int     *tab;
    int     nb_philo;
    t_philo *philo_tab;
    
}               t_general;
int *parse_input(char *argv[], int size);
int is_not_integer(char *str);
#endif
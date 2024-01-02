/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalimol <akalimol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:33:02 by akalimol          #+#    #+#             */
/*   Updated: 2023/06/30 19:24:27 by akalimol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_time.h"

int	ft_update_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->time_curr = (time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000);
	return (0);
}

void	ft_update_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal);
	philo->time_eat = philo->time_curr;
	pthread_mutex_unlock(&philo->meal);
}

int	ft_get_time(t_philo *philo)
{
	return (philo->time_curr - philo->rules->time_start);
}

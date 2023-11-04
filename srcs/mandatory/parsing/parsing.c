/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:22:45 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/11/04 12:32:56 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int *parse_input(char *argv[], int size)
{
    int i;
    int *tab;

    i = 0;
    if (size != 4)
        return(write(2, "ERROR\n", 6), NULL);
    tab = (int*)ft_callloc_tab(size);    
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

int    create_philos(t_general *data)
{
    int i;
    
    i = 0;
    data->philo_tab = malloc(sizeof(t_philo)*data->nb_philo);
    if (!data->philo_tab)
        return(0);
    while (i < data->nb_philo)
    {
        data->philo_tab[i].id = i;
        data->philo_tab[i].time_to_die = data->tab[1];
        data->philo_tab[i].time_to_eat = data->tab[2];
        data->philo_tab[i].time_to_sleep = data->tab[3];
        i++;
    }
    return(1);
}

int main(int argc, char *argv[])
{
    t_general   *data;
    data = malloc(sizeof(t_general));
    data->tab = parse_input(argv, argc-1);
    data->nb_philo = argc-1;
    print_tab(data->tab, argc-1);
    free_data(data);
    
}
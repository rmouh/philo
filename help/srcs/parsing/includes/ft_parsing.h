/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalimol <akalimol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:09:34 by akalimol          #+#    #+#             */
/*   Updated: 2023/06/28 12:47:48 by akalimol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "ft_error.h"
# include "libft.h"
# include "struct_rules.h"
# include <stdio.h>

void	ft_parsing_num_philo(char **argv, t_rules *rules);
void	ft_parsing_time_to_die(char **argv, t_rules *rules);
void	ft_parsing_time_to_eat(char **argv, t_rules *rules);
void	ft_parsing_time_to_sleep(char **argv, t_rules *rules);
void	ft_parsing_num_success(int argc, char **argv, t_rules *rules);

#endif

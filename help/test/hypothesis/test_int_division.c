/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_int_division.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akalimol <akalimol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:10:35 by akalimol          #+#    #+#             */
/*   Updated: 2023/06/21 12:06:26 by akalimol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

/*
    Check the division operators
*/

int main(void)
{
    int a = 7;
    int b = 2;
    int c;

    c = a / b;
    printf("%d\n", c);
    return (0);
}
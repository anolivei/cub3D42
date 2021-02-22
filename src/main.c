/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/02/21 23:00:01 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int initializeWindow()
{
    void *window;

    window = mlx_init();
    mlx_new_window(window, 1080, 720, "anolivei");
    mlx_loop(window);
    return (0);
}

int main()
{
    initializeWindow();
    printf("ola\n");
//    setup();
//    while (1)
//    {
       //processImput();
       //update();
       //render();
//    }
    return(0);
}

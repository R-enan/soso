/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:03:47 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/10/21 20:58:13 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	next_pos(t_game_status *st, int y, int x)
{
	if (st -> map[y][x] != '1')
	{
		if (st -> map[y][x] == 'E')
		{
			if (st -> c_count)
				ft_printf ("Door locked, get all collectables to open.\n");
			else
				error_management (st);
		}
		else
		{
			if (st -> map[y][x] == 'C')
				st -> c_count--;
			st -> map[st -> p_y][st -> p_x] = '0';
			st -> p_y = y;
			st -> p_x = x;
			st -> mv_count++;
			st -> map[st -> p_y][st -> p_x] = 'P';
		}
	}
}

int	get_key(int key_code, t_game_status *st)
{
	if (key_code == ESC_KEY)
		ft_close (st);
	else
	{
		if (key_code == W_KEY || key_code == Z_KEY || key_code == UP_KEY)
			next_pos (st, st -> p_y - 1, st -> p_x);
		if (key_code == A_KEY || key_code == Q_KEY || key_code == LEFT_KEY)
			next_pos (st, st -> p_y, st -> p_x - 1);
		if (key_code == S_KEY || key_code == DOWN_KEY)
			next_pos (st, st -> p_y + 1, st -> p_x);
		if (key_code == D_KEY || key_code == RIGHT_KEY)
			next_pos (st, st -> p_y, st -> p_x + 1);
	}
	return (0);
}

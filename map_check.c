/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:37:32 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/10/22 23:52:55 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_elements(t_game_status *st)
{
	int	x_pos;
	int	y_pos;
	int	p_count;
	int	e_count;

	y_pos = 0;
	p_count = 0;
	e_count = 0;
	while (st -> map[y_pos])
	{
		x_pos = 0;
		while (st -> map[y_pos][x_pos])
		{
			st -> c_count += (st -> map[y_pos][x_pos] == 'C');
			p_count += (st -> map[y_pos][x_pos] == 'P');
			e_count += (st -> map[y_pos][x_pos] == 'E');
			st -> p_x += x_pos * (st -> map[y_pos][x_pos] == 'P');
			st -> p_y += y_pos * (st -> map[y_pos][x_pos] == 'P');
			x_pos++;
		}
		y_pos++;
	}
	st -> error |= (1 << 4) * (p_count > 1);
	st -> error |= (1 << 7) * (e_count > 1);
	st -> error |= (1 << 9) * !(st -> c_count);
}

int	check_characters(t_game_status *st)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (st -> map[y])
	{
		x = 0;
		while (st -> map[y][x])
		{
			if (!ft_strchr ("01CEP\r\n", st -> map[y][x]))
				st -> error |= (1 << 17);
			x++;
		}
		y++;
	}
	return (st -> error);
}

void	check_walls(t_game_status *st)
{
	int	x_pos;
	int	y_pos;

	y_pos = 0;
	x_pos = 0;
	while (x_pos < st -> size_x)
	{
		if (st->map[0][x_pos] != '1' || st->map[st->size_y - 1][x_pos] != '1')
			st -> error |= (1 << 6);
		x_pos++;
	}
	x_pos = 0;
	while (y_pos < st -> size_y)
	{
		if (st->map[y_pos][0] != '1' || st->map[y_pos][st->size_x - 1] != '1')
			st -> error |= (1 << 6);
		y_pos++;
	}
}

static int	get_next_path(t_game_status *st, int y, int x)
{
	return (st -> map[y][x] != '1' && st -> map[y][x] != 'X');
}

void	check_valid_path(t_game_status *st, int y, int x)
{
	if (st -> map[y][x] == 'C')
		st -> c_remain--;
	if (st -> map[y][x] == 'E')
		st -> exit = 'y';
	st -> map[y][x] = 'X';
	if (get_next_path (st, y - 1, x) && (st -> c_count || st -> exit == 'n'))
		check_valid_path (st, y - 1, x);
	if (get_next_path (st, y + 1, x) && (st -> c_count || st -> exit == 'n'))
		check_valid_path (st, y + 1, x);
	if (get_next_path (st, y, x - 1) && (st -> c_count || st -> exit == 'n'))
		check_valid_path (st, y, x - 1);
	if (get_next_path (st, y, x + 1) && (st -> c_count || st -> exit == 'n'))
		check_valid_path (st, y, x + 1);
}

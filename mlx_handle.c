/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:32:22 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/10/22 21:31:43 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_sprites(t_game_status *st, int *w, int *h)
{
	st -> player = mlx_xpm_file_to_image (st -> mlx, P_SPRITES, w, h);
	st -> collectible = mlx_xpm_file_to_image (st -> mlx, C_SPRITES, w, h);
	st -> exit_closed = mlx_xpm_file_to_image (st -> mlx, EX_C_SPRITES, w, h);
	st -> exit_opened = mlx_xpm_file_to_image (st -> mlx, EX_O_SPRITES, w, h);
	st -> wall = mlx_xpm_file_to_image (st -> mlx, W_SPRITES, w, h);
	st -> floor = mlx_xpm_file_to_image (st -> mlx, F_SPRITES, w, h);
	if (!st -> player || !st -> collectible || !st -> exit_closed)
	{
		st -> error |= (1 << 13);
		error_management (st);
	}
	if (!st -> exit_opened || !st -> wall || !st -> floor)
	{
		st -> error |= (1 << 13);
		error_management (st);
	}
}

static void	show_sprite(t_game_status *st, int x, int y)
{
	int	sx;
	int	sy;

	sx = x * SPRITE_SIZE;
	sy = y * SPRITE_SIZE;
	if (st -> map[y][x] == 'P')
		mlx_put_image_to_window (st -> mlx, st -> win, st -> player, sx, sy);
	else if (st -> map[y][x] == 'C')
		mlx_put_image_to_window(st->mlx, st->win, st->collectible, sx, sy);
	else if (st -> map[y][x] == 'E' && (st -> c_count) > 0)
		mlx_put_image_to_window(st->mlx, st->win, st->exit_closed, sx, sy);
	else if (st -> map[y][x] == 'E' && (st -> c_count) <= 0)
		mlx_put_image_to_window(st->mlx, st->win, st->exit_opened, sx, sy);
	else if (st -> map[y][x] == '0')
		mlx_put_image_to_window (st -> mlx, st -> win, st -> floor, sx, sy);
	else
		mlx_put_image_to_window (st -> mlx, st -> win, st -> wall, sx, sy);
}

static int	render_next_frame(t_game_status *st)
{
	int		x;
	int		y;
	char	*str_mv_count;

	y = 0;
	while (st -> map[y])
	{
		x = 0;
		while (st -> map[y][x])
		{
			show_sprite (st, x, y);
			x++;
		}
		y++;
	}
	str_mv_count = ft_itoa (st -> mv_count);
	mlx_string_put (st -> mlx, st -> win, 16, 12, 0xffffff, "Moves:");
	mlx_string_put (st -> mlx, st -> win, 56, 13, 0xffffff, str_mv_count);
	free (str_mv_count);
	return (0);
}

void	init_mlx(t_game_status *st)
{
	int	sp_size;
	int	width;
	int	height;

	sp_size = SPRITE_SIZE;
	st -> mlx = mlx_init();
	if (!st -> mlx)
		st -> error |= (1 << 14);
	width = (st -> size_x) * SPRITE_SIZE;
	height = (st -> size_y) * SPRITE_SIZE;
	if (width > MAX_WIDTH || height > MAX_HEIGHT)
	{
		st -> error |= (1 << 15);
		error_management (st);
	}
	st -> win = mlx_new_window (st -> mlx, width, height, "so_long");
	if (!st -> win)
		st -> error |= (1 << 16);
	if (st -> error)
		error_management (st);
	load_sprites (st, &sp_size, &sp_size);
	mlx_hook (st -> win, 2, (1L << 0), get_key, st);
	mlx_hook (st -> win, 17, 0, ft_close, st);
	mlx_loop_hook(st -> mlx, render_next_frame, st);
	mlx_loop (st -> mlx);
}

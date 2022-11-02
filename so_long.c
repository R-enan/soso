/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:25:11 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/10/23 00:52:38 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_values(t_game_status *st)
{
	st -> mlx = NULL;
	st -> win = NULL;
	st -> player = NULL;
	st -> collectible = NULL;
	st -> exit_closed = NULL;
	st -> exit_opened = NULL;
	st -> wall = NULL;
	st -> floor = NULL;
	st -> map = NULL;
	st -> map_file = NULL;
	st -> exit = 'n';
	st -> c_count = 0;
	st -> c_remain = 0;
	st -> mv_count = 0;
	st -> p_x = 0;
	st -> p_y = 0;
	st -> size_x = 0;
	st -> size_y = 0;
	st -> error = 0;
}

static void	get_errors(char	**error_list)
{
	error_list[0] = "You Win!\n";
	error_list[1] = "Invalid number of arguments\n";
	error_list[2] = "Invalid map extension\n";
	error_list[3] = "Invalid map format\n";
	error_list[4] = "Multiple player start points\n";
	error_list[5] = "Player start point not found\n";
	error_list[6] = "Invalid walls\n";
	error_list[7] = "Multiple exit points\n";
	error_list[8] = "Exit point not found\n";
	error_list[9] = "No collectibles\n";
	error_list[10] = "Unreachable collectibles found\n";
	error_list[11] = "Unreachable exit\n";
	error_list[12] = "Unable to read the map\n";
	error_list[13] = "Unable to load sprite\n";
	error_list[14] = "Unable to allocate memory for mlx pointer.\n";
	error_list[15] = "Map too big.\n";
	error_list[16] = "Unable to allocate memory for mlx windows pointer.\n";
	error_list[17] = "Invalid map element.\n";
	error_list[18] = "Invalid path.\n";
}

void	error_management(t_game_status *st)
{
	char	*error_list[19];
	int		aux;

	aux = -1;
	get_errors (error_list);
	if (st -> error == 0)
		ft_printf ("%s", error_list[0]);
	else
		ft_printf ("Error\n");
	while (aux++ < 25)
	{
		if ((st -> error >> (aux - 1)) % 2 == 1)
			ft_printf ("%s", error_list[aux - 1]);
	}
	ft_close (st);
}

int	ft_close(t_game_status *st)
{
	int	i;

	i = 0;
	if (st -> win)
	{
		mlx_destroy_image (st -> mlx, st -> player);
		mlx_destroy_image (st -> mlx, st -> collectible);
		mlx_destroy_image (st -> mlx, st -> exit_closed);
		mlx_destroy_image (st -> mlx, st -> exit_opened);
		mlx_destroy_image (st -> mlx, st -> wall);
		mlx_destroy_image (st -> mlx, st -> floor);
		mlx_destroy_window (st -> mlx, st -> win);
		mlx_destroy_display (st -> mlx);
	}
	while (i < st -> size_y && st -> map)
	{
		free (st -> map[i]);
		st -> map[i] = NULL;
		i++;
	}
	free (st -> map);
	free (st -> mlx);
	exit (0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game_status	st;

	init_values (&st);
	st.error |= (1 << 1) * (argc != 2);
	if (st.error)
		error_management (&st);
	else
		st.map_file = argv[1];
	load_map (&st);
	init_mlx (&st);
	error_management (&st);
	return (0);
}

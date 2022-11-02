/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:19:45 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/10/23 03:11:25 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	x_len(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] != '\r' && line[i] != '\n')
		i++;
	return (i);
}

static void	get_map_size(t_game_status *st)
{
	int		fd;
	char	*line;

	fd = open (st -> map_file, O_RDONLY);
	if (fd < 0)
	{
		st -> error |= (1 << 12);
		error_management (st);
	}
	line = get_next_line (fd);
	if (line[0] == '\r' || line[0] == '\n')
		st -> error |= (1 << 3);
	st -> size_x = x_len (line);
	if (!(st -> size_x))
		st -> error |= (1 << 3);
	while (line)
	{
		if (st -> size_x != x_len(line) || line[0] == '\r' || line[0] == '\n')
			st -> error |= (1 << 3);
		else
			st -> size_y++;
		free (line);
		line = get_next_line (fd);
	}
	close (fd);
}

static void	copy_map(t_game_status *st, char first_run)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open (st -> map_file, O_RDONLY);
	line = get_next_line (fd);
	while (line)
	{
		if (line[0] != '\r' && line[0] != '\n' && first_run == 1)
			st -> map[i++] = ft_strdup (line);
		else if (line[0] != '\r' && line[0] != '\n' && first_run == 0)
			ft_strlcpy (st -> map[i++], line, ft_strlen (line) - 1);
		free (line);
		line = get_next_line (fd);
	}
	close (fd);
}

static void	convert_map(t_game_status *st, char first_run)
{
	int		i;

	i = 0;
	get_map_size (st);
	if (st -> error)
		error_management (st);
	if (first_run == 1)
	{
		st -> map = malloc ((st -> size_y + 1) * sizeof (char **));
		while (i <= st -> size_y)
			st -> map[i++] = NULL;
	}
	copy_map (st, first_run);
}

void	load_map(t_game_status *st)
{
	int	check_ext;

	check_ext = ((ft_strncmp(ft_strrchr(st->map_file, '.'), ".ber\0", 5)) != 0);
	st->error |= (check_ext << 2);
	if (st -> error)
		error_management (st);
	convert_map (st, 1);
	if (!(st -> map) || st -> error)
		error_management (st);
	if (check_characters (st))
		error_management (st);
	check_map_elements (st);
	if (st -> error)
		error_management (st);
	st -> c_remain = st -> c_count;
	check_walls (st);
	check_valid_path (st, st -> p_y, st -> p_x);
	st->error |= (st -> c_remain > 0 || st -> exit != 'y') << 18;
	if (st -> error)
		error_management (st);
	st -> size_y = 0;
	st -> size_x = 0;
	convert_map (st, 0);
	if (st -> error)
		error_management (st);
}

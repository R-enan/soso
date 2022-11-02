/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 02:44:21 by rapdos-s          #+#    #+#             */
/*   Updated: 2022/10/22 22:42:15 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <mlx.h>

# define SPRITE_SIZE 16
# define MAX_WIDTH 1250
# define MAX_HEIGHT 940

# define P_SPRITES "sprites/player.xpm"
# define C_SPRITES "sprites/collectible.xpm"
# define EX_C_SPRITES "sprites/exit_closed.xpm"
# define EX_O_SPRITES "sprites/exit_opened.xpm"
# define W_SPRITES "sprites/wall.xpm"
# define F_SPRITES "sprites/floor.xpm"

# define ESC_KEY 65307

# define UP_KEY 65362
# define LEFT_KEY 65361
# define DOWN_KEY 65364
# define RIGHT_KEY 65363

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

# define Z_KEY 122
# define Q_KEY 113

typedef struct s_game_status
{
	void	*mlx;
	void	*win;
	void	*player;
	void	*collectible;
	void	*exit_closed;
	void	*exit_opened;
	void	*wall;
	void	*floor;
	char	**map;
	char	*map_file;
	char	exit;
	int		c_count;
	int		c_remain;
	int		mv_count;
	int		p_x;
	int		p_y;
	int		size_x;
	int		size_y;
	int		error;
}	t_game_status;

void	error_management(t_game_status *st);
int		ft_close(t_game_status *st);
void	load_map(t_game_status *st);
void	init_mlx(t_game_status *st);
void	check_map_elements(t_game_status *st);
void	check_walls(t_game_status *st);
void	check_valid_path(t_game_status *st, int y, int x);
int		get_key(int key_code, t_game_status *st);
int		check_characters(t_game_status *st);

#endif

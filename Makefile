# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 10:58:02 by rapdos-s          #+#    #+#              #
#    Updated: 2022/10/18 10:58:02 by rapdos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long
LIBFT_DIR	=	libft/
MLX_DIR		=	mlx/
LIBFT_NAME	=	${LIBFT_DIR}libft.a
MLX_NAME	=	libmlx_Linux.a libmlx.a
MLX_NAME	:=	${addprefix ${MLX_DIR}, ${MLX_NAME}}
SRC			=	map_check.c map_utils.c mlx_handle.c movement.c so_long.c
OBJ			=	${SRC:%.c=%.o}
CC			=	cc
CFLAGS		=
#-Wall -Werror -Wextra
MLXFLAGS	=	-lX11 -lXext -lmlx -Imlx
INCLUDES	=	 -I so_long.h -I ./mlx
RM			=	rm -f
AR			=	ar rcs

all: ${NAME}

${NAME}: ${OBJ}
	make -C ${LIBFT_DIR}
	make -C ${MLX_DIR}
	${CC} ${CFLAGS} $(INCLUDES) $(MLXFLAGS) ${OBJ} ${LIBFT_NAME} -o ${NAME}

clean:
	${RM} ${OBJ}
	make clean -C ${LIBFT_DIR}
	make clean -C ${MLX_DIR}

fclean: clean
	${RM} ${NAME} ${MLX_NAME}
	make fclean -C ${LIBFT_DIR}

re: fclean all

bonus: all

%.o: %.c
	${CC} -c ${CFLAGS} $(INCLUDES) $(MLXFLAGS) $< -o $@

.PHONY: all clean fclean re

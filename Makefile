# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 20:32:43 by mrosario          #+#    #+#              #
#    Updated: 2020/07/24 20:00:09 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out

SRC = rotation.c ./config/cub.c ./config/getscreenres.c ./config/getwallparams.c ./config/getspriteparams.c ./config/getceilingfloorparams.c cub3d.c ./config/iamerror.c ./config/printnotifications.c ./config/mapcheck/map_phase1.c

BSRC =

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

LIBFT = ./libft/libft.a

CFLAG = -Wall -Werror -Wextra

FRMWRK = -framework OpenGL -framework AppKit

LIBS = -I /usr/local/include/mlx.h -I ./libft/libft.h cub3d.h -L./libft/ -lft -L /usr/local/lib/ -lmlx

all: $(NAME)

$(NAME): $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC)

debug: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC) -g

$(LIBFT):
	make -C ./libft
	make clean -C ./libft

bonus:

clean:
	rm -f *.o
	make clean -C ./libft

fclean: clean
	rm -f $(NAME) libcub3d.a libcub3d.h
	make fclean -C ./libft

cleanexe:
	rm $(NAME)

re: fclean all

recub: clean cleanexe all

.PHONY: all clean fclean re bonus debug ./libft/libft.a recub cleanexe
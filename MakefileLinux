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

LIBS =  mlx.h ./libft/libft.h -L. -lmlx_Linux -lm -lXext -lX11 -lbsd -L ./libft -lft

all: $(NAME)

$(NAME): $(LIBFT)
	gcc $(CFLAG) $(SRC) $(LIBS)

debug: $(LIBFT)
	gcc $(CFLAG) $(SRC) $(LIBS) -g

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
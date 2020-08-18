# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 20:32:43 by mrosario          #+#    #+#              #
#    Updated: 2020/08/18 18:49:13 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = rotation.c freeme.c ./toolkit.c ./config/cub.c ./config/getscreenres.c ./config/getwallparams.c ./config/getspriteparams.c ./config/getceilingfloorparams.c cub3d.c ./config/iamerror.c ./config/printnotifications.c ./config/mapcheck/map_phase1.c ./config/maperrors.c ./config/texerrors.c ./config/mapcheck/map_phase2.c ./config/maplistfunctions.c ./config/spritelistfunctions.c ./config/spritecounter.c ./config/printlinkedlists.c ./config/initialize.c ./config/makeimages.c ./graphicsengine/raycaster.c ./graphicsengine/dda.c ./graphicsengine/drawframeline.c ./graphicsengine/calculateframeline.c ./graphicsengine/drawsprites.c ./graphicsengine/playermovement.c ./graphicsengine/keychecks.c ./config/maparray.c ./graphicsengine/sortsprites.c ./graphicsengine/fpscounter_bonus.c ./graphicsengine/graphicsmodes_bonus.c

BSRC =

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

LIBFT = ./libft/libft.a

CFLAG = -Wall -Werror -Wextra

FRMWRK = -framework OpenGL -framework AppKit

LIBS = -I /usr/local/include/ -I ./libft/ -L./libft/ -lft -L /usr/local/lib/ -lmlx

all: $(NAME)

$(NAME): $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC) -o cub3d

debug: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC) -g -o cub3d

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

.PHONY: all clean fclean re bonus debug cleanexe
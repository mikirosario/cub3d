# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 20:32:43 by mrosario          #+#    #+#              #
#    Updated: 2020/09/10 17:22:38 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = cub3d.c rotation.c freeme.c ./toolkit.c ./config/cub.c \
./config/getscreenres.c ./config/getwallparams.c ./config/getspriteparams.c \
./config/getceilingfloorparams.c ./config/iamerror.c \
./config/printnotifications.c ./config/mapcheck/map_phase1.c \
./config/maperrors.c ./config/texerrors.c ./config/mapcheck/map_phase2.c \
./config/maplistfunctions.c ./config/spritelistfunctions.c \
./config/spritecounter.c ./config/printlinkedlists.c ./config/initialize.c \
./config/makeimages.c ./graphicsengine/raycaster.c ./graphicsengine/dda.c \
./graphicsengine/drawframeline.c ./graphicsengine/calculateframeline.c \
./graphicsengine/drawsprites.c ./graphicsengine/playermovement.c \
./graphicsengine/keychecks.c ./config/maparray.c \
./graphicsengine/sortsprites.c ./graphicsengine/screenshots/bmpgenerator.c \
./graphicsengine/screenshots/bmperror.c

BSRC = cub3d_bonus.c rotation.c freeme_bonus.c ./toolkit_bonus.c ./config/cub_bonus.c \
./config/getscreenres.c ./config/getwallparams.c ./config/getspriteparams_bonus.c \
./config/getceilingfloorparams_bonus.c ./config/iamerror_bonus.c \
./config/printnotifications_bonus.c ./config/mapcheck/map_phase1_bonus.c \
./config/maperrors.c ./config/texerrors_bonus.c ./config/mapcheck/map_phase2_bonus.c \
./config/maplistfunctions_bonus.c ./config/spritelistfunctions.c \
./config/spritecounter.c ./config/printlinkedlists.c ./config/initialize_bonus.c \
./config/makeimages_bonus.c ./graphicsengine/raycaster_bonus.c ./graphicsengine/dda_bonus.c \
./graphicsengine/drawframeline_bonus.c ./graphicsengine/calculateframeline_bonus.c \
./graphicsengine/drawsprites_bonus.c ./graphicsengine/playermovement_bonus.c \
./graphicsengine/keychecks.c ./config/mapsprarrays_bonus.c \
./graphicsengine/sortsprites_bonus.c ./graphicsengine/screenshots/bmpgenerator.c \
./graphicsengine/screenshots/bmperror.c ./graphicsengine/graphicsmodes_bonus.c \
./graphicsengine/fpscounter_bonus.c ./graphicsengine/drawceilingfloor_bonus.c \
./config/raycaster_start_bonus.c ./config/makeanimationimgs_bonus.c \
./config/animationerrors_bonus.c ./graphicsengine/modifysprite.c \
./config/doorcounter_bonus.c

LBSRC = cub3d_linux.c rotation.c freeme_bonus.c ./toolkit_bonus.c ./config/cub_bonus.c \
./config/getscreenres.c ./config/getwallparams.c ./config/getspriteparams_bonus.c \
./config/getceilingfloorparams_bonus.c ./config/iamerror_bonus.c \
./config/printnotifications_bonus.c ./config/mapcheck/map_phase1_bonus.c \
./config/maperrors.c ./config/texerrors_bonus.c ./config/mapcheck/map_phase2_bonus.c \
./config/maplistfunctions_bonus.c ./config/spritelistfunctions.c \
./config/spritecounter.c ./config/printlinkedlists.c ./config/initialize_linux.c \
./config/makeimages_bonus.c ./graphicsengine/raycaster_bonus.c ./graphicsengine/dda_bonus.c \
./graphicsengine/drawframeline_bonus.c ./graphicsengine/calculateframeline_bonus.c \
./graphicsengine/drawsprites_bonus.c ./graphicsengine/playermovement_bonus.c \
./graphicsengine/keychecks_linux.c ./config/mapsprarrays_bonus.c \
./graphicsengine/sortsprites_bonus.c ./graphicsengine/screenshots/bmpgenerator.c \
./graphicsengine/screenshots/bmperror.c ./graphicsengine/graphicsmodes_bonus.c \
./graphicsengine/fpscounter_bonus.c ./graphicsengine/drawceilingfloor_bonus.c \
./config/raycaster_start_bonus.c ./config/makeanimationimgs_bonus.c \
./config/animationerrors_bonus.c ./graphicsengine/modifysprite.c \
./config/doorcounter_bonus.c

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

LIBFT = ./libft/libft.a

CFLAG = -Wall -Werror -Wextra

FRMWRK = -framework OpenGL -framework AppKit

LIBS = -I /usr/local/include/ -I ./libft/ -L./libft/ -lft -L /usr/local/lib/ -lmlx

LINUXLIBS = -I ./ -I ./libft/ -L. -lmlx_Linux -lm -lXext -lX11 -lbsd -L ./libft -lft

$(NAME): $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC) -o cub3d

$(LIBFT):
	make -C ./libft
	make clean -C ./libft

all: $(NAME)

debug: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC) -g -o cub3d

bonus: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(BSRC) -o cub3d

bdebug: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(BSRC) -g -o cub3d

linux: $(LIBFT)
	gcc $(CFLAG) $(LBSRC) $(LINUXLIBS) -g -o cub3d


clean:
	rm -f *.o
	make clean -C ./libft

fclean: clean
	rm -f $(NAME) libcub3d.a libcub3d.h screenie.bmp
	make fclean -C ./libft

cleanexe:
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus debug cleanexe
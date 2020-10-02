# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miki <miki@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/15 20:32:43 by mrosario          #+#    #+#              #
#    Updated: 2020/10/02 15:41:58 by miki             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = cub3d.c ./utils/rotation.c ./utils/freeme.c ./utils/toolkit.c ./config/cub.c \
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
./graphicsengine/screenshots/bmperror.c ./config/raycaster_start.c \
./config/playercounter.c ./config/gatekeeper.c ./config/cuberrors.c

BSRC = cub3d_bonus.c ./utils/rotation.c ./utils/bonus/freeme_bonus.c \
./utils/bonus/toolkit_bonus.c ./config/bonus/cub_bonus.c \
./config/getscreenres.c ./config/getwallparams.c ./config/bonus/getspriteparams_bonus.c \
./config/bonus/getceilingfloorparams_bonus.c ./config/bonus/iamerror_bonus.c \
./config/bonus/printnotifications_bonus.c ./config/mapcheck/bonus/map_phase1_bonus.c \
./config/maperrors.c ./config/bonus/texerrors_bonus.c ./config/mapcheck/bonus/map_phase2_bonus.c \
./config/bonus/maplistfunctions_bonus.c ./config/spritelistfunctions.c \
./config/spritecounter.c ./config/printlinkedlists.c ./config/bonus/initialize_bonus.c \
./config/bonus/makeimages_bonus.c ./graphicsengine/bonus/raycaster_bonus.c ./graphicsengine/bonus/dda_bonus.c \
./graphicsengine/bonus/drawframeline_bonus.c ./graphicsengine/bonus/calculateframeline_bonus.c \
./graphicsengine/bonus/drawsprites_bonus.c ./graphicsengine/bonus/playermovement_bonus.c \
./graphicsengine/bonus/keychecks_bonus.c ./config/bonus/mapsprarrays_bonus.c \
./graphicsengine/bonus/sortsprites_bonus.c ./graphicsengine/screenshots/bmpgenerator.c \
./graphicsengine/screenshots/bmperror.c ./graphicsengine/bonus/graphicsmodes_bonus.c \
./graphicsengine/bonus/fpscounter_bonus.c ./graphicsengine/bonus/drawceilingfloor_bonus.c \
./config/bonus/raycaster_start_bonus.c ./config/bonus/makeanimationimgs_bonus.c \
./config/bonus/animationerrors_bonus.c ./graphicsengine/bonus/modifysprite_bonus.c \
./config/bonus/doorcounter_bonus.c ./graphicsengine/bonus/doorcaster_bonus.c \
./graphicsengine/bonus/castoneray_bonus.c ./graphicsengine/bonus/timer_bonus.c \
./graphicsengine/bonus/dooranimator_bonus.c ./graphicsengine/bonus/spraycat_bonus.c \
./config/mapcheck/bonus/specialdoors_bonus.c ./graphicsengine/bonus/teleportplayer_bonus.c \
./config/bonus/makespecialanimationimgs_bonus.c ./graphicsengine/bonus/monologue_bonus.c \
./graphicsengine/bonus/ending_bonus.c ./graphicsengine/bonus/castwall_bonus.c \
./graphicsengine/bonus/hud_bonus.c ./graphicsengine/bonus/choosetexture_bonus.c \
./graphicsengine/bonus/mouse_bonus.c ./sounds/music_bonus.c ./graphicsengine/bonus/drawtobuffer_bonus.c \
./graphicsengine/bonus/skybox_bonus.c ./config/bonus/makemoreimages_bonus.c \
./config/bonus/getbonusimgaddresses_bonus.c ./config/playercounter.c \
./config/mapcheck/bonus/unflood_bonus.c ./config/gatekeeper.c ./config/cuberrors.c

LSRC = cub3d.c ./utils/rotation.c ./utils/freeme.c ./utils/toolkit.c ./config/cub.c \
./config/getscreenres.c ./config/getwallparams.c ./config/getspriteparams.c \
./config/getceilingfloorparams.c ./config/iamerror.c \
./config/printnotifications.c ./config/mapcheck/map_phase1.c \
./config/maperrors.c ./config/texerrors.c ./config/mapcheck/map_phase2.c \
./config/maplistfunctions.c ./config/spritelistfunctions.c \
./config/spritecounter.c ./config/printlinkedlists.c ./config/initialize_linux.c \
./config/makeimages.c ./graphicsengine/raycaster.c ./graphicsengine/dda.c \
./graphicsengine/drawframeline.c ./graphicsengine/calculateframeline.c \
./graphicsengine/drawsprites.c ./graphicsengine/playermovement.c \
./graphicsengine/keychecks_linux.c ./config/maparray.c \
./graphicsengine/sortsprites.c ./graphicsengine/screenshots/bmpgenerator.c \
./graphicsengine/screenshots/bmperror.c ./config/raycaster_start.c \
./config/playercounter.c ./config/gatekeeper.c ./config/cuberrors.c

LBSRC = cub3d_bonus.c ./utils/rotation.c ./utils/bonus/freeme_bonus.c \
./utils/bonus/toolkit_bonus.c ./config/bonus/cub_bonus.c \
./config/getscreenres.c ./config/getwallparams.c ./config/bonus/getspriteparams_bonus.c \
./config/bonus/getceilingfloorparams_bonus.c ./config/bonus/iamerror_bonus.c \
./config/bonus/printnotifications_bonus.c ./config/mapcheck/bonus/map_phase1_bonus.c \
./config/maperrors.c ./config/bonus/texerrors_bonus.c ./config/mapcheck/bonus/map_phase2_bonus.c \
./config/bonus/maplistfunctions_bonus.c ./config/spritelistfunctions.c \
./config/spritecounter.c ./config/printlinkedlists.c ./config/bonus/initialize_linux_bonus.c \
./config/bonus/makeimages_bonus.c ./graphicsengine/bonus/raycaster_bonus.c ./graphicsengine/bonus/dda_bonus.c \
./graphicsengine/bonus/drawframeline_bonus.c ./graphicsengine/bonus/calculateframeline_bonus.c \
./graphicsengine/bonus/drawsprites_bonus.c ./graphicsengine/bonus/playermovement_bonus.c \
./graphicsengine/bonus/keychecks_linux_bonus.c ./config/bonus/mapsprarrays_bonus.c \
./graphicsengine/bonus/sortsprites_bonus.c ./graphicsengine/screenshots/bmpgenerator.c \
./graphicsengine/screenshots/bmperror.c ./graphicsengine/bonus/graphicsmodes_bonus.c \
./graphicsengine/bonus/fpscounter_bonus.c ./graphicsengine/bonus/drawceilingfloor_bonus.c \
./config/bonus/raycaster_start_bonus.c ./config/bonus/makeanimationimgs_bonus.c \
./config/bonus/animationerrors_bonus.c ./graphicsengine/bonus/modifysprite_bonus.c \
./config/bonus/doorcounter_bonus.c ./graphicsengine/bonus/doorcaster_bonus.c \
./graphicsengine/bonus/castoneray_bonus.c ./graphicsengine/bonus/timer_bonus.c \
./graphicsengine/bonus/dooranimator_bonus.c ./graphicsengine/bonus/spraycat_bonus.c \
./config/mapcheck/bonus/specialdoors_bonus.c ./graphicsengine/bonus/teleportplayer_bonus.c \
./config/bonus/makespecialanimationimgs_bonus.c ./graphicsengine/bonus/monologue_bonus.c \
./graphicsengine/bonus/ending_bonus.c ./graphicsengine/bonus/castwall_bonus.c \
./graphicsengine/bonus/hud_bonus.c ./graphicsengine/bonus/choosetexture_bonus.c \
./graphicsengine/bonus/mouse_bonus.c ./sounds/music_bonus_linux.c ./graphicsengine/bonus/drawtobuffer_bonus.c \
./graphicsengine/bonus/skybox_bonus.c ./config/bonus/makemoreimages_bonus.c \
./config/bonus/getbonusimgaddresses_bonus.c ./config/playercounter.c \
./config/mapcheck/bonus/unflood_bonus.c ./config/gatekeeper.c ./config/cuberrors.c

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

LIBFT = ./libft/libft.a

CFLAG = -Wall -Werror -Wextra

FRMWRK = -framework OpenGL -framework AppKit

LIBS = -I ./Includes -I /usr/local/include/ -I ./libft/ -L./libft/ -lft -L /usr/local/lib/ -lmlx

LINUXLIBS = -I ./Includes -I ./libft/ -L. -lmlx_Linux -lm -lXext -lX11 -lbsd -L ./libft -lft

$(NAME): $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC) -o cub3D

$(LIBFT):
	make -C ./libft
	make clean -C ./libft

all: $(NAME)

debug: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(SRC) -g -o cub3D

bonus: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(BSRC) -o cub3D

bdebug: $(LIBFT)
	gcc $(CFLAG) $(LIBS) $(FRMWRK) $(BSRC) -g -o cub3D

linux: $(LIBFT)
	gcc $(CFLAG) $(LSRC) $(LINUXLIBS) -g -o cub3D

linuxbonus: $(LIBFT)
	gcc $(CFLAG) $(LBSRC) $(LINUXLIBS) -g -O0 -o cub3D


clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) libcub3d.a screenie.bmp
	make fclean -C ./libft

cleanexe:
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus debug cleanexe
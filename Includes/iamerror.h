/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iamerror.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:29:20 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/02 04:22:08 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IAMERROR_H
# define IAMERROR_H

# define REDERROR "\nError\n"
# define YELLOWERROR "\nError\n"
# define CUBNOTFOUND "FILE NOT FOUND, CHECK YOUR .CUB FILE PATH\n"
# define WEIRDFD "THE GAME TRIED TO READ FROM STDIN, STDOUT OR STDERR... O_O\n"
# define COULDNOTCLOSE "ONE OR MORE FILES COULD NOT BE CLOSED\n"
# define MALLOCFAIL "MEMORY ALLOCATION FAILURE; CHECK YOUR AVAILABLE MEMORY\n"
# define GETRESFAIL "INVALID RESOLUTION; USING DEFAULT RESOLUTION\n"
# define BADRESSYN "BAD RESOLUTION SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define BADRESSIZE "RESOLUTION BELOW 240 OR ABOVE DISPLAY RESOLUTION\n"
# define GETNOFAIL "NORTH WALL (NO) TEXTURE FILE PATH RETRIEVAL FAILED\n"
# define BADNOSYN "BAD NORTH WALL SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define PATHNOFAIL "NORTH WALL FILE (NO) DOES NOT EXIST AT SPECIFIED PATH:\n"
# define GETSOFAIL "SOUTH WALL (SO) TEXTURE FILE PATH RETRIEVAL FAILED\n"
# define BADSOSYN "BAD SOUTH WALL SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define PATHSOFAIL "SOUTH WALL FILE (SO) DOES NOT EXIST AT SPECIFIED PATH:\n"
# define GETWEFAIL "WEST WALL (WE) TEXTURE FILE PATH RETRIEVAL FAILED\n"
# define BADWESYN "BAD WEST WALL SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define PATHWEFAIL "WEST WALL FILE (WE) DOES NOT EXIST AT SPECIFIED PATH:\n"
# define GETEAFAIL "EAST WALL (EA) TEXTURE FILE PATH RETRIEVAL FAILED\n"
# define BADEASYN "BAD EAST WALL SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define PATHEAFAIL "EAST WALL FILE (EA) DOES NOT EXIST AT SPECIFIED PATH:\n"
# define GETSPRFAIL "SPRITE (S) TEXTURE FILE PATH RETRIEVAL FAILED\n"
# define BADSPRSYN "BAD SPRITE TEXTURE SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define PATHSPRFAIL "SPRITE FILE (S) DOES NOT EXIST AT SPECIFIED PATH:\n"
# define TEXSIZEFAIL "TEXTURE SIZE NOT FOUND; YOU MUST USE XPM 1.0 FILES\n"
# define WALLTEXSIZEDIF "ALL SURFACE TEXTURES MUST BE THE SAME SIZE\n"
# define OPENXPMFAIL "UNABLE TO OPEN THIS XPM FILE; CHECK YOUR MEMORY\n"
# define FCOLORINVALID "INVALID FLOOR COLOR; USING DEFAULT COLOR\n"
# define BADFCOLORSYN "BAD FLOOR COLOR SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define CCOLORINVALID "INVALID CEILING COLOR; USING DEFAULT COLOR\n"
# define BADCCOLORSYN "BAD CEILING COLOR SYNTAX; JUST FOLLOW THE INSTRUCTIONS\n"
# define BADCOLORRANGE "EACH RGB COLOR VALUE MAY NOT BE HIGHER THAN 255\n"
# define OUTOFBOUNDS "THE PLAYER MUST BE IN AN AREA BOUNDED BY WALLS\n"
# define NOMAPFOUND "MAP NOT FOUND\n"
# define BADMAP3LINE "MAP NEEDS AT LEAST THREE ROWS TO MAKE A BOUNDED AREA\n"
# define NOPLAYER "NO PLAYER FOUND; MAP MUST HAVE A PLAYER STARTING LOCATION\n"
# define TOOMANYPLAYERS "MULTIPLE PLAYERS FOUND; MAP MAY ONLY HAVE ONE\n"
# define MAPTOOBIG "YOU REALLY NEED A MAP THAT HUGE? NO. IT'S OVER  BYTES!\n"
# define BMPCREATEFAIL "COULD NOT CREATE SCREENSHOT FILE!\n"
# define BMPWRITEFAIL "COULD NOT WRITE TO SCREENSHOT FILE!\n"
# define BMPCLOSEFAIL "UNABLE TO CLOSE SCREENSHOT FILE\n"
# define TOOMANYARGS "EXECUTE WITH ./CUB3D \"PATH.CUB\" [OPTIONAL]\"--SAVE\"\n"
# define BADCUB "BAD CUB FILE\n"
# define BADLINE "COULD NOT UNDERSTAND THIS LINE\n"
# define DUPPARAM "DUPLICATE PARAMETER\n"
# define BADCUBEND "END CUB FILE WITH MAP OR A SINGLE EMPTY LINE\n"
# define MISSINGPARAM "MISSING PARAMETERS: "
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iamerror.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:29:20 by mrosario          #+#    #+#             */
/*   Updated: 2020/03/08 19:51:44 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_AM_ERROR_H
# define I_AM_ERROR_H

#define cubFileNotFound RED"Error\nCHECK YOUR .CUB FILE PATH\n"RESET
#define weirdFD RED"Error\nYOUR GAME IS TRYING TO READ FROM STDIN, STDOUT OR STDERR... THIS SHOULD NOT BE HAPPENING O_O\n"RESET
#define couldNotClose RED"Error\nFILE COULD NOT CLOSE\n"RESET
#define mallocFail RED"Error\nMEMORY ALLOCATION FAILURE; CHECK YOUR AVAILABLE MEMORY\n"RESET
#define getResFail YELLOW"Error\nINVALID RESOLUTION; CHECK YOUR MAP FILE; SWITCHING TO DEFAULT RESOLUTION\n"RESET
#define badResSyn YELLOW"Error\nUSE ONLY 'R' OR 'r' SPECIFIER TO PASS SCREEN RESOLUTION; CHECK YOUR MAP FILE\n"RESET
#define getNOFail RED"Error\nINVALID NORTH WALL (NO) TEXTURE FILE PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define pathNOFail RED"Error\nNORTH WALL FILE (NO) DOES NOT EXIST AT SPECIFIED PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define getSOFail RED"Error\nINVALID SOUTH WALL (SO) TEXTURE FILE PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define pathSOFail RED"Error\nSOUTH WALL FILE (SO) DOES NOT EXIST AT SPECIFIED PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define getWEFail RED"Error\nINVALID WEST WALL (WE) TEXTURE FILE PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define pathWEFail RED"Error\nWEST WALL FILE (WE) DOES NOT EXIST AT SPECIFIED PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define getEAFail RED"Error\nINVALID EAST WALL (EA) TEXTURE FILE PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define pathEAFail RED"Error\nEAST WALL FILE (EA) DOES NOT EXIST AT SPECIFIED PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define getSprFail RED"Error\nINVALID SPRITE (S) TEXTURE FILE PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define pathSprFail RED"Error\nSPRITE FILE (S) DOES NOT EXIST AT SPECIFIED PATH; SEE QUANTUM PATH INFO AND CHECK YOUR MAP FILE\n"RESET
#define wallTexSizeFail YELLOW"Error\nWALL TEXTURE SIZE NOT FOUND, DEFAULTING TO 64; YOUR IMAGE MAY NOT DISPLAY CORRECTLY!!\n"RESET
#define wallTexSizeDif RED"Error\nDIFFERENT WALL TEXTURE SIZES! YOUR WALL TEXTURE SIZES MUST ALL BE THE SAME BY ORDER OF UN SECURITY COUNCIL; ABORTING PROGRAM\n"RESET
#define sprTexSizeFail YELLOW"Error\nSPRITE TEXTURE SIZE NOT FOUND, DEFAULTING TO 64; YOUR IMAGE MAY NOT DISPLAY CORRECTLY!!\n"RESET
#define FColorInvalid YELLOW"Error\nINVALID FLOOR COLOR; USING DEFAULT COLOR\n"RESET
#define badFColorSyn YELLOW"Error\nUSE ONLY 'F' OR 'f' SPECIFIER TO PASS FLOOR COLOR; CHECK YOUR MAP FILE\n"RESET
#define CColorInvalid YELLOW"Error\nINVALID CEILING COLOR; USING DEFAULT COLOR\n"RESET
#define badCColorSyn YELLOW"Error\nUSE ONLY 'C' OR 'c' SPECIFIER TO PASS CEILING COLOR; CHECK YOUR MAP FILE\n"RESET

#endif
/*
** JUST READ THE INSTRUCTIONS
**
** HOW TO WRITE A .CUB FILE WITH A GAME MAP
**
** // FOR THE STANDARD COMPILATION: \\
** R    screenWidth screenHeight (ex. 1920 1080)
** NO   ./north_wall_path.XPM
** SO   ./south_wall_path.XPM
** WE   ./west_wall_path.XPM
** EA   ./east_wall_path.XPM
** S    ./sprite_path.XPM
** F    R,G,B color value for floor (ex. 102,153,153)
** C    R,G,B color value for ceiling (ex. 102,0,255)
** MAP
**
** - Separate screenWidth and screenHeight with spaces, 'x' or ','.	Example: R 1920 1080
** - Separate RGB color values with spaces or ','.					Example: F 102,0,75
** - Texture files must be in the game's root directory.			Example: NO ./nwall.XPM
** - Do *NOT* put characters before or after values					Example: F ,102,0,75,
**
** // FOR THE BONUS COMPILATION: \\
** R    screenWidth screenHeight (ex. 1920 1080)
** NO   ./north_wall_path.XPM
** SO   ./south_wall_path.XPM
** WE   ./west_wall_path.XPM
** EA   ./east_wall_path.XPM
** S    2./sprite_2_path.XPM 3./sprite_3_path.XPM... (up to 9./sprite_9_path.XPM)
** F    ./floor_path.XPM
** C    ./ceiling_path.XPM
** MAP
**
** Check test.cub for an example of the standard compilation cub file, and
** bonus.cub for an example of the bonus compilation cub file.
**
** All file paths must be within the program directory.
**
** All texture files MUST be XPM1 format. If you have an image that isn't,
** convert it.
**
** All texture paths are mandatory except sprite textures, which are only
** mandatory for maps with sprites.
**
** The program should be tolerant of file names with spaces in the STANDARD
** compilation, but you should probably avoid them anyway. Bad practice,
** you know. ;)
**
** To draw a map, write 0 for a floor, 1 for a wall, 2 for a sprite and
** N, S, E or W for the player starting location, where the letter will
** specify which direction the player will be facing at the start.
**
** Any map shape is fine, but the player MUST be within an area bounded by
** walls. You MUST use only the space bar to shape your map. Tabs will NOT be
** accepted.
**
** Trailing spaces are OK for any of the parameters, but any other trailing
** characters will cause a syntax error.
**
** // BONUS COMPILATION ONLY \\
** Every sprite path MUST be separated by spaces, and therefore spaces CANNOT
** be used within the sprite texture file names! You can use as many or as few
** spaces as you want.
**
** Sprite texture paths must be numbered in ascending order from 2 - 9, placing
** the number right before the ./ as in the example above. Number 2 on the map
** will get the texture at sprite_2_path, number 3 will get the texture at
** sprite_3_path, and so on.
**
** You can use up to eight unique sprite textures in total for sprites numbered
** from 2 - 9 on the map.
**
** If you have sprites on the map that lack a sprite texture, the program will
** abort with a missing sprite texture error. If you have textures loaded that
** lack a sprite, the program will ignore them and execute normally.
**
**
** - YOU MUST PASS THE PROGRAM A VALID MAP FILE WHEN YOU EXECUTE IT.
** - AT THE COMMAND LINE, INSIDE THE GAME'S ROOT DIRECTORY, TYPE:
** 
** ./cub3d "YOURMAPFILE.CUB"
**
** IF YOUR NAME IS MOULINETTE AND YOU WANT A .BMP SCREENSHOT OF THE FIRST FRAME
** THEN TYPE:
**
** ./cub3d "YOURMAPFILE.CUB" "--save"
*/
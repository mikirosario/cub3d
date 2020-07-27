** HOW TO PLAY **

- YOU MUST PASS THE PROGRAM A VALID MAP FILE WHEN YOU EXECUTE IT.
- AT THE COMMAND LINE, INSIDE THE GAME'S ROOT DIRECTORY, TYPE:

./a.out "YOURMAPFILE.CUB"

** HOW TO WRITE A .CUB FILE **

- FOLLOW THIS PATTERN:

R    screenWidth screenHeight
NO   ./My_North_Wall_Texture.XPM
SO   ./My_South_Wall_Texture.XPM
WE   ./My_West_Wall_Texture.XPM
EA   ./My_East_Wall_Texture.XPM
S    ./My_Sprite_Texture.XPM
F    R,G,B
C    R,G,B

- Separate screenWidth and screenHeight with spaces, 'x' or ','.	Example:	R 1920 1080
- Separate RGB color values with spaces or ','.						Example:	F 102,0,75
- Texture files must be in the game's root directory.				Example:	NO ./My_North_Wall_Texture.XPM
- Do *NOT* put characters before or after values					Example:	F ,102,0,75,


** MAP
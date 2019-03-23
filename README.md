# League of Quake
Spring 2019 IT266 Quake 4 Modifications

# How to install (Windows):
* Clone/Download repository
* Open q4sdk.sln in Visual Studio 2013 (tested on Ultimate edition)
* Compile the idLib project FIRST, it is required to compile the Game project
* Then compile the Game project
* Take the new Gamex86.dll and rename it to gamex86.dll 
* Create a binary.conf file (an empty text file with a modified extension will do fine)
* Put 0 in binary.conf
* Put binary.conf and gamex86.dll into a zip folder named game000.zip
* Change the extension of game000.zip to .pk4 (resulting in game000.pk4)
* Go to your Quake 4 directory 
** (for default Steam this is "C:\Program Files (x86)\Steam\steamapps\common\Quake 4")
* Create a new folder for the mod in this directory
* Place game000.pk4 in this new folder
* Copy the folders def, guis, scripts, and strings from the repository into this new folder

# How to open:
## Method 1: Create a shortcut (Steam)
* Go to your desktop and create a new shortcut to Steam.exe
* After the path to Steam and the final quotation mark in the "Target" category of the shortcut, add:
** -applaunch 2210 +set fs_game <name of folder in Quake 4 directory>
** Replace <name of folder in Quake 4 directory> with the name of the mod folder in the Quake 4 base directory
* When you use this shortcut to launch the game, League of Quake will be loaded!
## Method 1.5: Create a shortcut (Other)
* Go to your desktop and create a new shortcut to Quake4.exe
* After the final quotation mark in the "Target" category of the shortcut, add:
** +set fs_game <name of folder in Quake 4 directory>
** Replace <name of folder in Quake 4 directory> with the name of the mod folder in the Quake 4 base directory
* When you use this shortcut to launch the game, League of Quake will be loaded!
## Method 2: In-Game:
* After loading Quake 4, click the mods button on the bottom left
* Then select the name of the subdirectory you put League of Quake's game000.pk4 in
* The game will restart and your mod will be loaded!
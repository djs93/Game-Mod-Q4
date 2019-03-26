# League of Quake
Spring 2019 IT266 Quake 4 Modifications

# Quick Notes:
* To open the buy menu bind a key to "Buy Menu" in Settings -> Controls -> Weapons

# How to install (Windows):
* Clone/Download repository
* Go to your Quake 4 directory 
  * (for default Steam this is "C:\Program Files (x86)\Steam\steamapps\common\Quake 4")
* Create a new folder for the mod in this directory
* Place game000.pk4 in this new folder
* Copy the folders def, guis, scripts, and strings from the repository into this new folder
* (Or just directly clone the repository into that new folder)

# How to open:
## Method 1: Create a shortcut (Steam)
* Go to your desktop and create a new shortcut to Steam.exe
* After the path to Steam and the final quotation mark in the "Target" category of the shortcut, add:
  * -applaunch 2210 +set fs_game <name of folder in Quake 4 directory>
  * Replace <name of folder in Quake 4 directory> with the name of the mod folder in the Quake 4 base directory
* When you use this shortcut to launch the game, League of Quake will be loaded!
## Method 1.5: Create a shortcut (Other)
* Go to your desktop and create a new shortcut to Quake4.exe
* After the final quotation mark in the "Target" category of the shortcut, add:
  * +set fs_game <name of folder in Quake 4 directory>
  * Replace <name of folder in Quake 4 directory> with the name of the mod folder in the Quake 4 base directory
* When you use this shortcut to launch the game, League of Quake will be loaded!
## Method 2: In-Game:
* After loading Quake 4, click the mods button on the bottom left
* Then select the name of the subdirectory you put League of Quake's game000.pk4 in
* The game will restart and your mod will be loaded!

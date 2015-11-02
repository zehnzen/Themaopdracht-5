//File Enums.h

#ifndef _Enums_H
#define _Enums_H

enum class textureID { GRASS, ROAD, UNIT, DRAGON, 
	FACTORY, RESOURCE,
	BACKGROUND, START, OPTION, EXIT, MUTE, BACK,
	ENDTURN
};
enum class musicID {MENUTHEME, MISSIONTHEME, BB, NONE};
enum class soundID {SELECTUNIT, WALKUNIT};
enum {TILESIZE = 50, SpriteOffset = 1, ScreenWidth = 1050, ScreenHeight = 550};
enum class buttonID { NONE, ENDTURN};
enum class commandID { NONE, LEFTCLICK, RIGHTCLICK, SPAWNUNIT, SPAWNBOMBER, SPAWNFACTORY, SPAWNRESOURCE, SWITCHPLAYER, OPENMENU};

#endif
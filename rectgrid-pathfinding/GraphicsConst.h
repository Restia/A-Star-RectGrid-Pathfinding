#ifndef _GRAPHICSCONST_H_
#define _GRAPHICSCONST_H_

#include <allegro5\allegro.h>

#define GRAPHICS_INIT_FAILED	0x00
#define GRAPHICS_INIT_SUCCESS	0x01

#define FLAT_TOPPED				0x00
#define POINTY_TOPPED			0x01

#define GRID_SIZE				20
#define	UP						0x00
#define	RIGHT					0x02
#define LEFT					0x01
#define DOWN					0x03

#define COLOR_FIELD_GRID		al_map_rgb(153, 255, 255)
#define	COLOR_WALL_GRID			al_map_rgb(64, 64, 64)
#define	COLOR_CLOSED_GRID		al_map_rgb(153, 76, 0)
#define	COLOR_OPEN_GRID			al_map_rgb(0, 102, 0)
#define	COLOR_END_GRID			al_map_rgb(0, 139, 255)
#define	COLOR_START_GRID		al_map_rgb(255, 0, 139)
#define	COLOR_PATH				al_map_rgb(255, 255, 0)		


#define	GRID_WALL				0x00
#define	GRID_FIELD				0x01
#define GRID_STATUS_FREE		0x00
#define GRID_STATUS_OPEN		0x01
#define	GRID_STATUS_CLOSE		0xFF
#define GRID_END				0x22
#define	GRID_START				0x11
#define GRID_PATH				0x10

#endif _GRAPHICSCONST_H_
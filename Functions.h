#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "Stats.h"
#include <map>

const unsigned short int tilesize = 4;
const unsigned short int chunksize = 4;

struct Unit
{
	Texture2D tex;
	Vector2 pos;
	unsigned int atk;
	unsigned int range;
	unsigned int hp;
	unsigned int mp;
	unsigned int mvp;
};

struct Troop
{
	Unit u1;
	Unit u2;
	Unit u3;
	Unit u4;
	Unit u5;
	Unit u6;
	Unit u7;
	Unit u8;
};


struct Tile
{
	Troop troop;
	Vector2 coord;
	Vector2 pos;
	Vector2 center;
	Texture2D tex;
	Rectangle rect;
	Color col = WHITE;
	const char* biome;
	unsigned int elevation;
	unsigned int movecost;
	bool water;
	bool underground;
};

struct Chunk
{
	Tile tilearray[tilesize * tilesize];
	Vector2 pos;
};

struct Coord
{
	int x, y;

	bool operator==(const Coord& o) const
	{
		return x == o.x && y == o.y;
	}

	bool operator<(const Coord& o)  const
	{
		return x < o.x || (x == o.x && y < o.y);
	}
};

RMDEF bool CoordEqual(Coord v1, Coord v2)
{
	if (v1.x == v2.x && v1.y == v2.y) return true;
	else return false;
}

std::map<Coord, Coord> m;

Unit selectedunit;
Chunk chunkarray[chunksize * chunksize];
Rectangle tilerect = { 1,64,128,69 };
Vector2 tilepos;
Vector2 chunkpos;
Vector2 coord;
const char* biome;
int cc;
int tc;
int r;
bool alternator = true;


std::vector<Tile> pathtiles;
std::vector<Unit> unitvector;
double basetime = GetTime();
double nexttime = GetTime();
float zoomlevel;

std::vector<Coord> frontier;
std::vector<Coord> old;
std::vector<Coord> next;
Coord et[6];
bool add;
int tiles;

int screenwidth = 800;
int screenheight = 800;
Vector2 screensize;
Vector2 screencenter;
Rectangle frustrum = { 0, 0, screenwidth, screenheight };

Tile selectedtile;
Vector2 chunkcoord;
Tile closesttile;
float distance = 1000;
Vector2 mp;











void PathFind(Tile ta, Tile tb)
{
	Vector2 a = ta.coord; Vector2 b = tb.coord;
	Vector2 diff = Vector2Subtract(a, b);


	int dist = (abs(diff.x) + abs(diff.y)) / 2;



	

	std::cout << "First tile : " << a.x << " " << a.y << std::endl;
	std::cout << "Second tile: " << b.x << " " << b.y << std::endl;
	std::cout << "Difference : " << diff.x << " " << diff.y << std::endl;
	std::cout << "Distance : " << dist << std::endl;
	
	
	
	// WIP BIAS SYSTEM 

	bool North = false;
	bool NorthEast = false;
	bool SouthEast = false;
	bool South = false;
	bool SouthWest = false;
	bool NorthWest = false;

	//if ((a.y < b.y && a.z > b.z) ||
	//	()
	//	
	//	
	//	
	//	North = true;   // DETECT NORTH


	//if (a.y > b.y && a.z < b.z) w = "South";   // DETECT JUST SOUTH

	//if (a.x < b.x) w = "East";

	//if (a.x > b.x) w = "West";

	//std::cout << "North: " << North << std::endl;
	//std::cout << "NorEa: " << NorthEast << std::endl;
	//std::cout << "SouEa: " << SouthEast << std::endl;
	//std::cout << "South: " << South << std::endl;
	//std::cout << "SouWe: " << SouthWest << std::endl;
	//std::cout << "NorWe: " << NorthWest << std::endl;












	//const char* m1 = "null"; const char* m2 = "null"; const char* m3 = "null"; const char* m4 = "null";
	//
	//if (a.y < b.y && a.z > b.z) m1 = "Yes";
	//else m1 = "No";
	//if (a.y > b.y && a.z < b.z) m2 = "Yes";
	//else m2 = "No";
	//if (a.x < b.x) m3 = "Yes";
	//else m3 = "No";
	//if (a.x > b.x) m4 = "Yes";
	//else m4 = "No";
	//
	//std::cout << "North " << m1 << std::endl;
	//std::cout << "South " << m2 << std::endl;
	//std::cout << "East " << m3 << std::endl;
	//std::cout << "West " << m4 << std::endl;
	

}







//void FindTilesInRange(Tile selectedtile)
//{
//    pathtiles.clear();
//    for (int i = 0; i < size * size; i++)
//    {
//        if (tilearray[i].coord.x < selectedtile.coord.x + range &&
//            tilearray[i].coord.x > selectedtile.coord.x - range &&
//            tilearray[i].coord.y < selectedtile.coord.y + range &&
//            tilearray[i].coord.y > selectedtile.coord.y - range &&
//            tilearray[i].coord.z < selectedtile.coord.z + range &&
//            tilearray[i].coord.z > selectedtile.coord.z - range)
//        {
//            pathtiles.push_back(tilearray[i]);
//        }
//    }
//    std::cout << "y:" << selectedtile.coord.y << " " << "x:" << selectedtile.coord.x << " " << "z:" << selectedtile.coord.z << std::endl;
//}
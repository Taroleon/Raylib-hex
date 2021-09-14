#pragma once

#include "raylib.h"

Texture2D archertex = LoadTextureFromImage(LoadImage("resources/archer.png"));

Texture2D pikemantex = LoadTextureFromImage(LoadImage("resources/pikeman.png"));

Texture2D swordsmantex = LoadTextureFromImage(LoadImage("resources/swordsman.png"));

// YellowTint
Texture2D YellowTintTexture = LoadTexture("resources/YellowTint.png");

// HighlightTile
Texture2D HighlightTileTexture = LoadTexture("resources/HighlightTile.png");

// BIOMES

// Blank
Texture2D BlankTileTexture = LoadTexture("resources/tilenew.png");

// Water
Texture2D WaterTileTexture = LoadTexture("resources/Water.png");

// Grass
Texture2D GrassTileTexture = LoadTexture("resources/Grass.png");

// Forest
Texture2D ForestTileTexture = LoadTexture("resources/Forest.png");

// Mountains
Texture2D MountTileTexture = LoadTexture("resources/Mountains.png");

// Desert
Texture2D DesertTileTexture = LoadTexture("resources/Desert.png");

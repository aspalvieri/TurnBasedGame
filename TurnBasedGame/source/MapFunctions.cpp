#include "../header/Game.h"

void Game::buildTileset() {
	int tcx = 0, tcy = 0; //TileClip X, TileClip Y
	int maxTilesetX = (dynamicMap["tileset"].width / TILE_SIZE);
	int maxTilesetY = (dynamicMap["tileset"].height / TILE_SIZE);
	int maxTilesetSize = maxTilesetX * maxTilesetY;
	for (int i = 0; i < maxTilesetSize; i++) {
		tileClips[i] = { { tcx, tcy, TILE_SIZE, TILE_SIZE }, { false, true, false } };
		tcx += TILE_SIZE;
		if ((i + 1) % maxTilesetX == 0) {
			tcx = 0;
			tcy += TILE_SIZE;
		}
	}

	shaderClips = {
		//Outer shadows
		//0 - 5
		{0, 0, TILE_SIZE, TILE_SIZE},
		{32, 0, TILE_SIZE, TILE_SIZE},
		{64, 0, TILE_SIZE, TILE_SIZE},
		{0, 32, TILE_SIZE, TILE_SIZE},
		{32, 32, TILE_SIZE, TILE_SIZE},
		{64, 32, TILE_SIZE, TILE_SIZE},

		//Inner shadows (1x1)
		//6 - 21
		{96, 0, TILE_SIZE, TILE_SIZE},
		{128, 0, TILE_SIZE, TILE_SIZE},
		{160, 0, TILE_SIZE, TILE_SIZE},
		{96, 32, TILE_SIZE, TILE_SIZE},
		{128, 32, TILE_SIZE, TILE_SIZE},
		{160, 32, TILE_SIZE, TILE_SIZE},
		{96, 64, TILE_SIZE, TILE_SIZE},
		{128, 64, TILE_SIZE, TILE_SIZE},
		{160, 64, TILE_SIZE, TILE_SIZE},
		{96, 96, TILE_SIZE, TILE_SIZE},
		{128, 96, TILE_SIZE, TILE_SIZE},
		{160, 96, TILE_SIZE, TILE_SIZE},
		{96, 128, TILE_SIZE, TILE_SIZE},
		{128, 128, TILE_SIZE, TILE_SIZE},
		{96, 160, TILE_SIZE, TILE_SIZE},
		{128, 160, TILE_SIZE, TILE_SIZE},

		//Inner shadows (2x2)
		//22 - 33
		{0, 64, TILE_SIZE, TILE_SIZE},
		{32, 64, TILE_SIZE, TILE_SIZE},
		{64, 64, TILE_SIZE, TILE_SIZE},
		{0, 96, TILE_SIZE, TILE_SIZE},
		{32, 96, TILE_SIZE, TILE_SIZE},
		{64, 96, TILE_SIZE, TILE_SIZE},
		{0, 128, TILE_SIZE, TILE_SIZE},
		{32, 128, TILE_SIZE, TILE_SIZE},
		{64, 128, TILE_SIZE, TILE_SIZE},
		{0, 160, TILE_SIZE, TILE_SIZE},
		{32, 160, TILE_SIZE, TILE_SIZE},
		{64, 160, TILE_SIZE, TILE_SIZE}
	};
}

void Game::buildTiles(string path) {
	clearTiles();
	fstream RAF;
	RAF.open(path.c_str(), ios::in, ios::binary);
	if (!RAF.is_open()) {
		cout << "Error: Unable to open file: " << path << "\n";
		return;
	}
	RAF.seekg(0); //Start from beginning
	
	//Read non-comma
	int y = 0, x = 0;
	for (int i; RAF >> i;) {
		tiles.push_back(Tile(x, y, &tileClips[i].first, get<0>(tileClips[i].second), get<1>(tileClips[i].second), get<2>(tileClips[i].second), &dynamicMap["tileset"]));
		x += TILE_SIZE;
		if (RAF.peek() == '\n') {
			y += TILE_SIZE;
			mapMaxX += x;
			x = 0;
		}
		if (RAF.peek() == ',')
			RAF.ignore();
	}
	RAF.close();
	mapMaxX = (mapMaxX / y) * TILE_SIZE;
	mapMaxY = y;
	indexMaxX = mapMaxX / TILE_SIZE;
	indexMaxY = mapMaxY / TILE_SIZE;

	/* //1500x1500 map with walls every 3x3 tiles
	clearTiles();
	for (y = 0; y < 1500; y++) {
		for (x = 0; x < 1500; x++) {
			bool flipper = false;
			int iswall = 0;
			if (x != 0 && y != 0 && x % 3 == 0 && y % 3 == 0) {
				flipper = true;
				iswall = 5;
			}
			tiles.push_back(Tile(x * TILE_SIZE, y * TILE_SIZE, &tileClips[iswall].first, flipper, !flipper, flipper, &dynamicMap["tileset"]));
		}
	}
	mapMaxX = 1500 * TILE_SIZE;
	mapMaxY = 1500 * TILE_SIZE;
	indexMaxX = mapMaxX / TILE_SIZE;
	indexMaxY = mapMaxY / TILE_SIZE;
	//*/
#if DISPLAY_DEBUG
	cout << "Built tiles. Size: " << tiles.size() << " tiles.\n";
	cout << "Map max X: " << mapMaxX << ". Map max Y: " << mapMaxY << ".\n";
	cout << "Index max X: " << indexMaxX << ". Index max Y: " << indexMaxY << ".\n";
#endif
	//Add shaders to tiles
	for (int y = 0; y < indexMaxY; y++) {
		int yIndex = y * indexMaxX;
		int ym1 = yIndex - (1 * indexMaxX); //y minus 1
		int yp1 = yIndex + (1 * indexMaxX); //y plus 1
		for (int x = 0; x < indexMaxX; x++) {
			//Casting shadows onto tiles
			if (tiles[x + yIndex].getCastsShadow()) {
				//No tile above the tile, and no tile to the left of it
				if (tiles[x + ym1].getTakesShadow() && !tiles[(x-1) + yIndex].getCastsShadow())
					tiles[x + ym1].shader = Shader(x * TILE_SIZE, (y - 1) * TILE_SIZE, &shaderClips[1], &dynamicMap["shaders"]);
				//No tile above, and yes tile to the left
				if (tiles[x + ym1].getTakesShadow() && tiles[(x - 1) + yIndex].getCastsShadow())
					tiles[x + ym1].shader = Shader(x * TILE_SIZE, (y - 1) * TILE_SIZE, &shaderClips[0], &dynamicMap["shaders"]);
				//No tile above, no tile to right
				if (tiles[x + ym1].getTakesShadow() && tiles[(x + 1) + yIndex].getTakesShadow() && tiles[(x + 1) + ym1].getTakesShadow())
					tiles[(x + 1) + ym1].shader = Shader((x + 1) * TILE_SIZE, (y - 1) * TILE_SIZE, &shaderClips[2], &dynamicMap["shaders"]);
				//No tile the right of the tile, and no tile below it
				if (tiles[(x + 1) + yIndex].getTakesShadow() && !tiles[x + yp1].getCastsShadow())
					tiles[(x + 1) + yIndex].shader = Shader((x + 1) * TILE_SIZE, y * TILE_SIZE, &shaderClips[4], &dynamicMap["shaders"]);
				//To the right of the tile, and yes tile below it
				if (tiles[(x + 1) + yIndex].getTakesShadow() && tiles[x + yp1].getCastsShadow())
					tiles[(x + 1) + yIndex].shader = Shader((x + 1) * TILE_SIZE, y * TILE_SIZE, &shaderClips[3], &dynamicMap["shaders"]);
				//No tile above, Tile top-left
				if (tiles[x + ym1].getTakesShadow() && tiles[(x - 1) + ym1].getCastsShadow())
					tiles[x + ym1].shader = Shader(x * TILE_SIZE, (y - 1) * TILE_SIZE, &shaderClips[5], &dynamicMap["shaders"]);
			}
			//Inner shadow if collidable tile
			if (tiles[x + yIndex].getCollide()) {
				////1x1 Wall
				//No tile in any direction (lone tile)
				if (!tiles[x+ym1].getCollide() && !tiles[(x-1)+yIndex].getCollide() && !tiles[(x+1)+yIndex].getCollide() && !tiles[x+yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[8], &dynamicMap["shaders"]);
				//Tile below this one
				if (!tiles[x + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[6], &dynamicMap["shaders"]);
				//Tile above this one
				if (tiles[x + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[10], &dynamicMap["shaders"]);
				//Tile to the right of this one
				if (!tiles[x + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[9], &dynamicMap["shaders"]);
				//Tile to the left of this one
				if (!tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[7], &dynamicMap["shaders"]);
				//Tile to the up,down,left,right of this one (middle tile)
				if (!tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && !tiles[(x + 1) + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide() && !tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[17], &dynamicMap["shaders"]);
				//Tile above and below this one
				if (tiles[x + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[11], &dynamicMap["shaders"]);
				//Tile to the right and left of this one
				if (!tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[14], &dynamicMap["shaders"]);
				//Tile above and to the right
				if (tiles[x + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[15], &dynamicMap["shaders"]);
				//Tile above and to the left
				if (tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[16], &dynamicMap["shaders"]);
				//Tile below and to the right
				if (!tiles[x + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[12], &dynamicMap["shaders"]);
				//Tile below and to the left
				if (!tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[13], &dynamicMap["shaders"]);
				//Tile left, up, and right
				if (!tiles[(x-1) + ym1].getCollide() && tiles[x + ym1].getCollide() && !tiles[(x+1) + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[18], &dynamicMap["shaders"]);
				//Tile left, right, and down
				if (!tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide() && !tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[21], &dynamicMap["shaders"]);
				//Tile up, right, and down
				if (tiles[x + ym1].getCollide() && !tiles[(x + 1) + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[x + yp1].getCollide() && !tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[19], &dynamicMap["shaders"]);
				//Tile up, left, and down
				if (!tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && !tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[20], &dynamicMap["shaders"]);

				////2x2 Wall
				//Tile to the right, bottom, bottom-right
				if (!tiles[x + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[x + yp1].getCollide() && tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[22], &dynamicMap["shaders"]);
				//Tile to the top, right, top-right
				if (tiles[x + ym1].getCollide() && tiles[(x + 1) + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[25], &dynamicMap["shaders"]);
				//Tile up, right, bottom
				if (tiles[x + ym1].getCollide() && tiles[(x + 1) + ym1].getCollide() && !tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[x + yp1].getCollide() && tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[30], &dynamicMap["shaders"]);
				//Tile bottom, right, bottom-left
				if (!tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[23], &dynamicMap["shaders"]);
				//Tile up, left, bottom
				if (tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[33], &dynamicMap["shaders"]);
				//Tile up, left, right
				if (!tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide() && tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[24], &dynamicMap["shaders"]);
				//Tile bottom, left, right
				if (tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && tiles[(x + 1) + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[27], &dynamicMap["shaders"]);
				//Tile left, top, top-left
				if (tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide() && !tiles[x + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[26], &dynamicMap["shaders"]);
				//Tile all directions except top-right
				if (tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && !tiles[(x + 1) + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide() && tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[31], &dynamicMap["shaders"]);
				//Tile all directions except top-left
				if (!tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && tiles[(x + 1) + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide() && tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[32], &dynamicMap["shaders"]);
				//Tile all directions except bottom-right
				if (tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && tiles[(x + 1) + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide() && !tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[28], &dynamicMap["shaders"]);
				//Tile all directions except bottom-left
				if (tiles[(x - 1) + ym1].getCollide() && tiles[x + ym1].getCollide() && tiles[(x + 1) + ym1].getCollide() && tiles[(x - 1) + yIndex].getCollide() && tiles[(x + 1) + yIndex].getCollide() && !tiles[(x - 1) + yp1].getCollide() && tiles[x + yp1].getCollide() && tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[29], &dynamicMap["shaders"]);

				/*
				//Template
				if (!tiles[(x - 1) + ym1].getCollide() && !tiles[x + ym1].getCollide() && !tiles[(x + 1) + ym1].getCollide()
					&& !tiles[(x - 1) + yIndex].getCollide() && !tiles[(x + 1) + yIndex].getCollide()
					&& !tiles[(x - 1) + yp1].getCollide() && !tiles[x + yp1].getCollide() && !tiles[(x + 1) + yp1].getCollide())
					tiles[x + yIndex].shader = Shader(x * TILE_SIZE, y * TILE_SIZE, &shaderClips[8], &dynamicMap["shaders"]);
				*/
			}
		}
	}
#if DISPLAY_DEBUG
	cout << "Added shaders to tiles.\n";
#endif
}

void Game::clearTiles() {
	tiles.clear();
	tiles.shrink_to_fit();
#if DISPLAY_DEBUG
	cout << "Cleared all tiles.\n";
#endif
}

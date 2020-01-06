#ifndef GAME_H
#define GAME_H

#include "Sprite.h"
#include "Timer.h"
#include "Tile.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

class Game {
public:
	Game();
	~Game();

	////Engine functions
	void initialize();
	bool running();
	void handleEvents();
	void update();
	void render();
	void newText(string key, std::string text, TTF_Font* gFont, int x = 0, int y = 0, SDL_Color textColor = { 0, 0, 0 }, int wrapLength = SCREEN_WIDTH);
	void newImage(string key, std::string path, int x = 0, int y = 0);
	void clearDynamicMap();

	////Build-time functions
	void buildFontManager();

	////Game functions
	//Loads the given map.csv file into the tiles vector
	void buildTiles(string path);
	//Loads the dynamicMap["tileset"] texture and sets initial clips
	void buildTileset();
	void clearTiles();
	void clearClipsets();
	void updateEntity(Entity *ent);
	void chaseTarget(Enemy *ent);
	bool checkAllCollision(Entity*);
	void setTileProps(vector<int>, tuple<bool, bool, bool, bool, bool>);
	//For shaders on maps
	bool edgeTile(int, int);

	// 0 = Render,,, 1 = Update,,, 2 = Events,,, 3 = Build,,, 4 = Destory
	void routeManager(int route); //Really ugly way to do it, but maps weren't working....

	//Screens
	void mainGameRender();
	void mainGameUpdate();
	void mainGameEvents();
	void mainGameBuild();
	void mainGameDestroy();

	void limitFPS();

private:
	//Player variables
	SDL_Rect *camera; //Not entirely sure if I need to define the camera, since SDLR::camera can access it globally
	Player player;

	//Game variables
	string currentScreen = "mainGame";
	vector<Enemy> enemies; //All enemies stored inside this
	double deltaX, deltaY, magnitude;
	vector<Projectile> projectiles; //All bullets,arrows,etc...

	//Enemies
	Enemy testEnemy;

	//Tile & camera variables
	vector<Tile> tiles;
	vector<SDL_Rect> shaderClips;
	//The bools are: collide, takesShadow, castsShadow, hasInner(shadow), requiresSame(tile)
	unordered_map<int, pair<SDL_Rect, tuple<bool, bool, bool, bool, bool>>> tileClips;
	//mapMaxX/Y are the real size (ie 1280x720), while indexMaxX/Y are the literals
	//'literals' meaning the X/Y divided by TILE_SIZE
	int mapMaxX, mapMaxY, indexMaxX, indexMaxY;
	//camBounds is the x,y,w,h literals of the camera, used for indexing in tiles vector
	//'literals' meaning the x,y,w,h divided by TILE_SIZE
	SDL_Rect camBounds;

	//Engine variables
	double averageFPS = 0;
	Timer FPS, capFPS;
	int countedFrames = 0;
	Texture fpsText;
	//Dynamic Textures
	unordered_map<string, StaticTexture> dynamicMap;

	//Static variables
	SDL_Rect *mPos, *mPosCam;
	bool *leftDown, *leftReleased, *rightDown, *rightReleased;
	map<int, TTF_Font*> fontManager, fontManagerBold;
	bool gameRunning;

	//SDL variables
	SDL_Event e;
	SDL_Renderer *gRenderer = NULL;
	SDL_Window *gWindow = NULL;
};

#endif//GAME_H
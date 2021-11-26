#ifndef GAME_H
#define GAME_H

#include "Sprite.h"
#include "Timer.h"
#include "Tile.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "FloatingText.h"

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
	void newText(string key, string text, TTF_Font* gFont, int x = 0, int y = 0, SDL_Color textColor = { 0, 0, 0 }, int wrapLength = SCREEN_WIDTH);
	void updateText(string key, string text);
	void updateText(string key, int x, int y);
	void updateText(string key, string text, int x, int y);
	void newImage(string key, string path, int x = 0, int y = 0); //Also doubles as an updateImage
	string roundTo(double var, int dec);
	void clearDynamicMap();
	void clearMapKey(string key);

	////Build-time functions
	void buildFontManager();

	////Game functions
	//Loads the given map.csv file into the tiles vector
	void buildMap(string path);
	void buildTiles(string path);
	void buildShaders();
	//Loads the dynamicMap["tileset"] texture and sets initial clips
	void buildTileset();
	void clearTiles();
	void clearClipsets();
	void updateEntity(Entity *ent);
	void chaseTarget(Enemy *ent);
	bool checkAllCollision(CameraObj*);
	void updateProjectile(Projectile *proj);
	Entity* findEntityByID(int ID);
	//For shaders on maps
	bool edgeTile(int, int);

	// 0 = Render,,, 1 = Update,,, 2 = Events
	void routeManager(int route); //Really ugly way to do it, but maps weren't working....

	//Screens
	void mainGameRender();
	void mainGameUpdate();
	void mainGameEvents();
	void mainGameBuild();
	void mainGameDestroy();

	/* Tile Properties List:
	First bool is collision
	Second bool is if the tile can have shadows cast on it
	Third bool is if the tile casts a shadow
	Fourth bool is if it has an inner shadow
	Fifth bool is if the tile requires the same tile to share inner shadows with */
	void setTileProps(vector<int>, tuple<bool, bool, bool, bool, bool>);
	
	void limitFPS();

private:
	//Player variables
	SDL_Rect *camera; //Not entirely sure if I need to define the camera, since SDLR::camera can access it globally
	Player player;

	//Game variables
	string currentScreen = "mainGame";
	vector<Enemy> enemies; //All enemies stored inside this
	vector<Projectile> projectiles; //All bullets,arrows,etc...
	vector<FloatingText> fTexts; //Effect texts that appear on entities
	vector<Light> lights; //Lighting maps
	double deltaX, deltaY, magnitude;

	//Variables to check for if an enemy can spawn in
	int collisionBlock = 0, collisionMod = 5;
	bool spawnCheck = true, forceMoved = false;
	vector<pair<int, int>> collisionCases = { {0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1} };

	//Enemies
	Enemy testEnemy;

	//Projectiles
	unordered_map<string, Projectile> projectileMap;

	//Tile & camera variables
	vector<Tile> tiles;
	vector<SDL_Rect> shaderClips;
	//The bools are: collide, takesShadow, castsShadow, hasInner(shadow), requiresSame(tile)
	unordered_map<int, pair<SDL_Rect, tuple<bool, bool, bool, bool, bool>>> tileClips;
	//mapMaxX/Y are the real size (ie 1280x720), while indexMaxX/Y are the literals
	//'literals' meaning the X/Y divided by TILE_SIZE (ie 40x22)
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
	//Mouse position relative to the window
	SDL_Rect *mPos;
	//Mouse position relative to the game world
	SDL_Rect *mPosCam;
	bool *leftDown, *leftReleased, *rightDown, *rightReleased;
	map<int, TTF_Font*> fontManager, fontManagerBold;
	bool gameRunning;
	RDevice rdevice;

	//SDL variables
	SDL_Event e;
	SDL_Renderer *gRenderer = NULL;
	SDL_Window *gWindow = NULL;
};

#endif//GAME_H
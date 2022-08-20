#ifndef GLOBALS_H
#define GLOBALS_H

#define DISPLAY_DEBUG 1

constexpr auto SCREEN_WIDTH = 1280;
constexpr auto HALF_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 800;
constexpr auto HALF_HEIGHT = 400;
constexpr auto SCREEN_FPS = 60;
constexpr auto SCREEN_TICK_PER_FRAME = (1000 / SCREEN_FPS);

constexpr auto TILE_SIZE = 32;
constexpr auto HALF_TILE_SIZE = 16;
constexpr auto QUARTER_TILE_SIZE = 8;
constexpr auto PLAYER_SIZE = 40;

constexpr auto RECENTLY_HIT_TIMEOUT = SCREEN_FPS * 5;
constexpr auto RECENTLY_HIT_TARGET_TIMEOUT = RECENTLY_HIT_TIMEOUT / 2;

constexpr auto SENDER_TYPE_PLAYER = 1;
constexpr auto SENDER_TYPE_ENEMY = 2;

#endif//GLOBALS_H
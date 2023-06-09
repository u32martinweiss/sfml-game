#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

// Game Info
extern const std::string GAME_TITLE;
extern const std::string GAME_VERSION;

const float TILE_SIZE                   = 32.f;
const float ITEM_SIZE                   = TILE_SIZE / 2;
const float GUI_ITEM_SIZE               = 22.f;
const float INVENTORY_BOX_SIZE          = 30.f;
const float HEART_SIZE                  = 12.f;
const float BASE_FONT_SIZE              = 14.f;
const float ITEM_FONT_SIZE              = 12.f;
const float BASE_FONT_OUTLINE_THICKNESS = 2.f;
const float TEXT_OFFSET                 = 12.f;

// Player
const float        PLAYER_SPEED          = 128.f;
const unsigned int PLAYER_INVENTORY_SIZE = 9;

// Bullets
const float BULLET_SIZE         = 8.f;
const float BULLET_SPEED        = 512.f;
const float BULLET_RELOAD_TIME  = 0.05f;
const float BULLET_DESPAWN_TIME = 0.05f;

#endif // CONSTANTS_HPP

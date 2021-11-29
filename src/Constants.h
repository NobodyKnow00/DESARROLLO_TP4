#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics/Color.hpp>

const int LANE_WIDTH = 120;
const int OBJECT_SIZE = LANE_WIDTH / 2;
const int PLAYER_HEIGHT = LANE_WIDTH;
const int WINDOW_HEIGHT = 750;
const int SPAWN_DIST = 250;
const int INITIAL_VELOCITY = 220;
const int ACCELERATION = 5;
const int OBJS_ON_SCREEN = 2 * (1 + WINDOW_HEIGHT / (SPAWN_DIST + OBJECT_SIZE));
const int PLAYER_TRANSITION_SPEED = 300;
const int FIRST_LANE_CENTER_POSITION = 60;
const int SECOND_LANE_CENTER_POSITION = 180;
const int THIRD_LANE_CENTER_POSITION = 300;
const int MENU_ARRAY_AMOUNT = 3;
const int CREDITS_ARRAY_AMOUNT = 3;


const sf::Color BASE_COLOR = sf::Color(0xFF4758FF);
const sf::Color BACKGROUND_COLOR = sf::Color(0x211357FF);
#endif //CONSTANTS_H
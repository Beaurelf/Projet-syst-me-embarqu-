#ifndef CONSTS_H
#define CONSTS_H
#include <stdint.h>

//======================================================== Robot
static const double DELAY_CORRECTION_MS = 0.5;
static const uint8_t DELAY_MOST_CORRECTION_MS = 10;
static const uint8_t DELAY_TO_GO_AHEAD_MS = 1;
static const double DELAY_FIND_LINE_MS = 0.875;
static const uint16_t DELAY_BEFORE_TURN_MS = 875;
static const uint8_t MILLI_SECOND = 1;
static const double SPEED = 0.45;
static const double SPEED_TO_ADJUST_MS = 0.4;
static const double SPEED_TO_MUST_ADJUST_MS = 0.3;
static const double SPEED_TO_FIND_LINE = 0.35;
static const uint16_t DELAY_TO_PLAY_SONG_MS = 1000;
static const uint16_t MIDDLE_DELAY_SPOT_DETECTED_MS = 1000;
static const uint8_t N_CYCLES_TO_BLINK_LED = 5;
static const uint16_t DELAY_AFTER_FIND_LINE_MS = 350;
static const uint16_t DELAY_STOP_BEFORE_TURN_MS = 350;
static const uint8_t MIN_SIZE_SCHEMA = 3;
static const double DELAY_TO_TAKE_HALF_SEGMENT_MS = 1.25;
static const double DELAY_TO_TAKE_SEGMENT_ROAD_MS = 1.7;
static const double DELAY_BEFORE_TAKE_DECISION_S = 1.65;
static const double DELAY_BEFORE_TAKE_CROSS_DECISION_S = 1.25;
static const double DELAY_BEFORE_TAKE_LOST_DECISION_S = 1.1;
static const double DELAY_TO_TAKE_SEGMENT_MS = 2.25;
static const uint16_t DELAY_TO_STOP_ENGINE_FOR_BACK_MS = 350;
static const uint8_t DELAY_TO_SKIP_CROSS_NOT_NECESSARY_MS = 200;
static const uint8_t NOTE_IF_CORNER_FOUND = 81;
static const uint8_t MAX_COlS_VALUE = 7;
static const uint8_t MAX_ROW_VALUE = 4;
static const uint8_t N_TIME_TO_PLAY_SONG = 5;
static const uint8_t DELAY_200_MS = 200;
static const uint8_t DELAY_100_MS = 100;
static const uint8_t NOTE_IF_OBSTACLE_DETECTED = 56;
static const uint16_t DELAY_TO_AJUST_IF_OBSTACLE_DETECTED = 550;
static const uint8_t SPEED_IMPULSION = 1;
static const uint8_t DELAY_FOR_IMPULSION = 10;
const uint8_t DELAY_AJUST_WHILE_RUNNING = 50;
//======================================================== Dijkstra
static const uint8_t SIZE = 28; // Taille de la matrice d'adjacence.
static const uint8_t INF = 200; // Valeur infinie utilisée pour l'initialisation de la matrice.
//======================================================== RobotManager
const uint16_t DELAY_BEFORE_START_IDENTIFY_CORNER_MS = 2000;
const uint8_t N_ROAD = 3;
//======================================================== SearchEngine

#endif
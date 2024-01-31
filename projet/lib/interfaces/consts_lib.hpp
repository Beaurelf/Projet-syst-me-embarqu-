#ifndef CONSTS_LIB_H
#define CONSTS_LIB_H
#include <stdint.h>
#include <avr/io.h>
//=========================================================== Navigation
static const uint16_t DELAY_TURN_180_DEGRE = 1800;
static const uint16_t DELAY_TURN_90_DEGRE = 900;
static const uint16_t DELAY_STOP_AFTER_TURN = 500;
// metttre deux vitesses differentes roue gauche superieure a droite
// ajuster la roue de droite tourne moins vite que celle de gauche
static const double PERCENT_TO_ADJUST = 0.056;
static const double PERCENT_TO_ADJUST_TURN = 0.1;
static const double SPEED_TO_TURN_FORWARD = 0.4;
static const double SPEED_TO_TURN_BACKWARD = 0.4;
static const double MAX_SPEED = 1;
static const uint8_t DELAY_IMPULSION = 20;
//=========================================================== Led
static const uint8_t DELAY_GREEN_MS = 15;       // Durée d'allumage de la LED verte en millisecondes.
static const uint8_t DELAY_RED_MS = 10;         // Durée d'allumage de la LED rouge en millisecondes.
static const uint16_t DELAY_MS_PER_BLINK = 500; // Durée standard pour un clignotement en millisecondes.

//========================================================== LineSensor
// Définition des constantes pour les broches des sorties numériques des capteurs de ligne.
static const uint8_t DIGITAL_OUTPUT_D1 = PA3;
static const uint8_t DIGITAL_OUTPUT_D2 = PA4;
static const uint8_t DIGITAL_OUTPUT_D3 = PA5;
static const uint8_t DIGITAL_OUTPUT_D4 = PA6;
static const uint8_t DIGITAL_OUTPUT_D5 = PA7;
//========================================================== ObstacleDetector
const uint8_t PRECISION_BIT_SHIFT = 2;
const uint8_t DETECTOR_OUTPUT = PA0;
const uint8_t N_READ = 5;
const uint8_t DELAY_BETWEEN_READ = 5;
const uint8_t MIN_DISTANCE_TO_DETECT = 35;
const uint8_t MAX_DISTANCE_TO_DETECT = 195;
//========================================================== Sound
static const uint8_t NOIR = 120;
static const uint8_t CROCHE = 60;
static const uint8_t DO = 46;
static const uint8_t RE = 48;
static const uint8_t MI = 50;
static const uint8_t FA = 51;
static const uint8_t SOL = 53;
static const uint8_t HIGH_LA = 56;
static const uint8_t SI_BEMOL = 57;

#endif
/**
 * @file Config.h
 * @brief Définition des configurations pour le système de navigation.
 *
 * Ce fichier contient des constantes, des structures et des configurations utilisées pour
 * définir le plan de navigation, les points d'intérêt, et les directions dans un environnement de navigation.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "res/struct/CornerNode.hpp"
#include "res/enum/Cardinal.hpp"
#include "interfaces/struct/NoteMusic.hpp"

// Constantes définissant la taille des différents tableaux utilisés pour la navigation
const uint8_t CORNER_LIST_SIZE = 8;	   // Nombre de coins dans la liste.
const uint8_t CORNER_SIZE = 4;		   // Nombre de coins directionnels pour les changements de directions.
const uint8_t MAX_POINT_AFFILATED = 5; // Nombre maximal de points affiliés.
const uint8_t MAX_NBR_POINTS = 28;	   // Nombre maximal de points dans l'espace de navigation.
/**
 * @brief Tableau des coins de la carte avec leurs schémas associés.
 *
 * Ce tableau définit les coins et les directions associées pour chaque coin dans l'environnement de navigation.De plus,
 * il definit aussi les schema associer a chaque coin selon une orientation donnée. Cela sert a l'identification des
 * coins de depart.
 *
 * @var Coordonnee du coin
 * @var Cardinal associe pour une orientation precise
 * @var schema associé au coin
 * @var 1ere Direction ou tourner lors du parcour
 * @var 2eme Direction ou tourner lors du parcour
 */
const CornerNode MapCorner[CORNER_LIST_SIZE] = {
	{{{1, 1}, Cardinal::EAST}, {'A', 'A', 'D'}, 3, Direction::LEFT, Direction::RIGHT},
	{{{1, 1}, Cardinal::SOUTH}, {'A', 'G', 'X'}, 3, Direction::RIGHT, Direction::LEFT},
	{{{4, 1}, Cardinal::EAST}, {'A', 'A', 'G', 'X'}, 4, Direction::RIGHT, Direction::LEFT},
	{{{4, 1}, Cardinal::NORTH}, {'A', 'D', 'X'}, 3, Direction::LEFT, Direction::RIGHT},
	{{{1, 7}, Cardinal::WEST}, {'A', 'G', 'A'}, 3, Direction::RIGHT, Direction::LEFT},
	{{{1, 7}, Cardinal::SOUTH}, {'A', 'D', 'A', 'A'}, 4, Direction::LEFT, Direction::RIGHT},
	{{{4, 7}, Cardinal::WEST}, {'A', 'D', 'A', 'D'}, 4, Direction::LEFT, Direction::RIGHT},
	{{{4, 7}, Cardinal::NORTH}, {'A', 'A', 'G', 'A'}, 4, Direction::RIGHT, Direction::LEFT}};

/**
 * @brief Tableau des points de navigation dans l'espace.
 *
 * Ce tableau contient les coordonnées des points de navigation utilisés pour définir le chemin du robot.
 */
const Coordinate points[MAX_NBR_POINTS] = {
	{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}};

// Définition des coins directionnels
const Corner North = {{-1, 0}, Cardinal::NORTH}; // Coin Nord avec orientation et déplacement.
const Corner South = {{1, 0}, Cardinal::SOUTH};	 // Coin Sud avec orientation et déplacement.
const Corner East = {{0, 1}, Cardinal::EAST};	 // Coin Est avec orientation et déplacement.
const Corner West = {{0, -1}, Cardinal::WEST};	 // Coin Ouest avec orientation et déplacement.

/**
 * @brief Tableau des coins directionnels pour la navigation.
 *
 * Ce tableau contient les coins directionnels utilisés pour naviguer dans l'environnement.
 */
const Corner listCornersNav[CORNER_SIZE] = {North, South, East, West};

/**
 * @brief Tableau des points affiliés pour chaque point de navigation.
 *
 * Chaque point de navigation peut être affilié à plusieurs autres points. Ce tableau définit ces affiliations.
 */
const uint8_t affiliatedPoints[MAX_NBR_POINTS][MAX_POINT_AFFILATED] = {
	{0, 1, 7, 100, 100},
	{1, 0, 2, 100, 100},
	{2, 1, 3, 9, 100},
	{3, 2, 10, 100, 100},
	{4, 5, 100, 100, 100},
	{5, 4, 6, 12, 100},
	{6, 5, 13, 100, 100},
	{7, 0, 8, 100, 100},
	{8, 7, 9, 15, 100},
	{9, 8, 2, 16, 100},
	{10, 3, 11, 100, 100},
	{11, 10, 12, 18, 100},
	{12, 11, 5, 13, 19},
	{13, 12, 6, 20, 100},
	{14, 15, 21, 100, 100},
	{15, 8, 14, 16, 100},
	{16, 9, 15, 17, 23},
	{17, 16, 18, 24, 100},
	{18, 11, 17, 25, 100},
	{19, 12, 26, 100, 100},
	{20, 13, 27, 100, 100},
	{21, 14, 22, 100, 100},
	{22, 21, 23, 100, 100},
	{23, 16, 22, 100, 100},
	{24, 17, 25, 100, 100},
	{25, 24, 18, 26, 100},
	{26, 25, 19, 27, 100},
	{27, 26, 20, 100, 100}};

#endif

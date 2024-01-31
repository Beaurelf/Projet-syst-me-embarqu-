/**
 * @file Corner.h
 * @brief Définition de la structure Corner pour représenter un coin dans un espace de navigation.
 *
 * Ce fichier contient la définition de la structure Corner, utilisée pour stocker des informations
 * sur un coin spécifique, notamment ses coordonnées spatiales et son orientation cardinale.
 * Cette structure est particulièrement utile dans les contextes de navigation et de cartographie.
 */

#ifndef CORNER_H
#define CORNER_H

#include <stdint.h>
#include "res/enum/Cardinal.hpp"
#include "res/struct/Coordinates.hpp"

/**
 * @struct Corner
 * @brief Structure représentant un coin dans un espace de navigation.
 *
 * La structure Corner est utilisée pour décrire un coin dans un environnement de navigation,
 * comme un point de changement de direction sur un parcours. Elle associe une position spatiale
 * à une orientation cardinale, permettant une représentation claire du coin dans l'espace.
 */
struct Corner
{
    Coordinate coordinate; // Les coordonnées du coin dans l'espace (la carte).
    Cardinal orientation;  // L'orientation cardinale du coin (Nord, Est, Sud, Ouest).
};

#endif // CORNER_H

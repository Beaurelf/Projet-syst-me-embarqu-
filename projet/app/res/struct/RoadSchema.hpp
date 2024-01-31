/**
 * @file RoadSchema.h
 * @brief Définition de la structure RoadSchema pour représenter le schéma d'un parcours.
 *
 * Ce fichier contient la définition de la structure RoadSchema, utilisée pour stocker une séquence
 * de directions représentant le parcours d'un robot ou d'un véhicule dans un environnement donné.
 * Elle permet de modéliser un itinéraire en termes de directions cardinales et de séquences de mouvements.
 */

#ifndef ROAD_SCHEMA_H
#define ROAD_SCHEMA_H

#include "res/enum/Cardinal.hpp"
#include "stdint.h"

const uint8_t MAX_ROAD_SIZE = 28; // Taille maximale du parcours en nombre de directions.

/**
 * @struct RoadSchema
 * @brief Structure représentant le schéma d'un parcours.
 *
 * La structure RoadSchema est utilisée pour modéliser le parcours d'un robot
 * à l'aide d'une série de directions cardinales. Elle stocke un tableau de directions ainsi que
 * la taille actuelle du parcours.
 */
struct RoadSchema
{
    CardinalDirection road[MAX_ROAD_SIZE]; // Tableau stockant la séquence des directions du parcours.
    uint8_t size;                          // Nombre actuel de directions dans le parcours.
};

#endif // ROAD_SCHEMA_H

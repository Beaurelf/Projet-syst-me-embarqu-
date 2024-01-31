/**
 * @file Coordinates.h
 * @brief Définition de la structure Coordinate pour représenter des coordonnées dans un espace bidimensionnel.
 *
 * Ce fichier contient la définition de la structure Coordinate, utilisée pour stocker et manipuler
 * des coordonnées dans un espace bidimensionnel, tel qu'une grille ou une carte, souvent utilisée
 * dans les systèmes de navigation robotique.
 */

#ifndef COORDINATES_H
#define COORDINATES_H

#include <stdint.h>

/**
 * @struct Coordinate
 * @brief Structure représentant une paire de coordonnées dans un espace bidimensionnel (la carte).
 *
 * Cette structure est utilisée pour décrire une position dans un espace à deux dimensions,
 * avec des composantes 'row' (ligne) et 'column' (colonne) pour indiquer des positions spécifiques,
 * comme des emplacements sur une grille ou une carte.
 */
struct Coordinate
{
    int8_t row;    // L'indice de ligne dans l'espace bidimensionnel (la carte).
    int8_t column; // L'indice de colonne dans l'espace bidimensionnel (la carte).
};

#endif // COORDINATES_H

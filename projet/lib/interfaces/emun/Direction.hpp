/**
 * @file Direction.h
 * @brief Fichier d'en-tête définissant les directions possibles.
 *
 * Ce fichier définit une énumération représentant les directions
 * de base que quelque chose (par exemple un robot, un véhicule)
 * peut prendre.
 */

#ifndef DIRECTION_H
#define DIRECTION_H

// Énumération représentant les différentes directions possibles.
enum class Direction
{
    FORWARD,  // Direction vers l'avant.
    BACKWARD, // Direction vers l'arrière.
    RIGHT,    // Direction vers la droite.
    LEFT      // Direction vers la gauche.
};

#endif

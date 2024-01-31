/**
 * @file Cardinal.h
 * @brief Définition des énumérations pour les directions cardinales et les directions de navigation.
 *
 * Ce fichier contient les énumérations pour représenter les directions cardinales (Nord, Est, Ouest, Sud)
 * et les directions spécifiques de navigation utilisées dans le système de navigation du robot.
 */

#ifndef CARDINAL_H
#define CARDINAL_H

/**
 * @enum Cardinal
 * @brief Énumération des directions cardinales.
 *
 * Représente les quatre directions cardinales principales : Nord, Est, Ouest et Sud.
 */
enum class Cardinal
{
    NORTH, // Nord
    EAST,  // Est
    WEST,  // Ouest
    SOUTH  // Sud
};

/**
 * @enum CardinalDirection
 * @brief Énumération des directions de navigation, y compris les points de départ et de fin.
 *
 * Étend l'énumération des directions cardinales pour inclure des points spéciaux de navigation comme
 * le point de départ et le point de fin pour les parcours et les itinéraires.
 */
enum class CardinalDirection
{
    START, // Point de départ
    NORTH, // Nord
    EAST,  // Est
    WEST,  // Ouest
    SOUTH, // Sud
    END    // Point de fin
};

#endif // CARDINAL_H

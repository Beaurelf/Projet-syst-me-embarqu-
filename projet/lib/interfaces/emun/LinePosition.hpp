/**
 * @file LinePosition.h
 * @brief Définition de l'énumération LinePosition pour les positions relatives d'une ligne.
 *
 * Ce fichier contient l'énumération LinePosition, utilisée pour représenter les différentes positions
 * relatives qu'une ligne peut occuper par rapport à un capteur ou un point de référence.
 * Cela est particulièrement utile dans les systèmes de navigation et de suivi de ligne pour les robots.
 */

#ifndef LINE_POSITION_H
#define LINE_POSITION_H

/**
 * @enum LinePosition
 * @brief Énumération des différentes positions d'une ligne.
 *
 * LinePosition définit les différentes positions qu'une ligne peut occuper par rapport à un capteur ou
 * un robot. Elle inclut des positions telles que gauche, droite, centre, ainsi que des états spéciaux
 * comme perdu ou détecté à un croisement.
 */
enum class LinePosition
{
    MOST_LEFT,            // La ligne est la plus à gauche possible.
    LEFT,                 // La ligne est à gauche.
    MOST_RIGHT,           // La ligne est la plus à droite possible.
    RIGHT,                // La ligne est à droite.
    CENTER,               // La ligne est au centre.
    LOST,                 // La ligne est perdue ou non détectée.
    CROSS_DETECTED,       // Un croisement est détecté.
    CROSS_RIGHT_DETECTED, // Un croisement est détecté à droite.
    CROSS_LEFT_DETECTED,  // Un croisement est détecté à gauche.
    UNDEFINED             // La position de la ligne est indéfinie.
};

#endif // LINE_POSITION_H

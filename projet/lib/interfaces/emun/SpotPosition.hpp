/**
 * @file SpotPosition.h
 * @brief Définition de l'énumération SpotPosition pour représenter la position relative d'un point d'intérêt.
 *
 * Ce fichier contient l'énumération SpotPosition, utilisée pour catégoriser la position relative
 * d'un point d'intérêt (comme un obstacle) par rapport à un capteur ou à un robot. Elle est utile
 * dans les contextes où la distance ou la proximité d'un objet est un critère important pour la navigation
 * ou la prise de décision.
 */

#ifndef SPOT_POSITION_H
#define SPOT_POSITION_H

/**
 * @enum SpotPosition
 * @brief Énumération des différentes positions relatives d'un point d'intérêt.
 *
 * SpotPosition fournit une manière simple de représenter la proximité ou l'éloignement d'un point d'intérêt,
 * tel qu'un obstacle, par rapport à un capteur ou à un robot. Elle est utilisée pour faciliter les décisions
 * de navigation et d'évitement d'obstacles.
 */
enum class SpotPosition
{
    NOTHING, // Aucun point d'intérêt n'est détecté.
    CLOSE,   // Le point d'intérêt est proche.
    FAR      // Le point d'intérêt est éloigné.
};

#endif // SPOT_POSITION_H

/**
 * @file ObstacleDetector.hpp
 * @brief Définition de la classe ObstacleDetector pour la détection d'obstacles.
 *
 * La classe ObstacleDetector fournit des fonctionnalités pour détecter la présence et la position
 * d'obstacles (un poteau) dans l'environnement du robot. Elle utilise un capteur de distance pour évaluer
 * la proximité des objets et déterminer si un obstacle est détecté.
 */
#ifndef OBSTACLE_DECTECTOR_H
#define OBSTACLE_DECTECTOR_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include "Can.hpp"
#include <util/delay.h>
#include "interfaces/emun/SpotPosition.hpp"
#include "interfaces/consts_lib.hpp"

/**
 * @class ObstacleDetector
 * @brief Classe pour détecter les obstacles à l'aide d'un capteur de distance.
 *
 * ObstacleDetector utilise un capteur de distance pour identifier la présence d'obstacles
 * devant le robot. Elle fournit des méthodes pour obtenir la distance de l'obstacle le plus proche
 * et pour déterminer s'il y a un obstacle dans une plage de distance spécifique.
 */
class ObstacleDetector
{
public:
    /**
     * @brief Constructeur d'ObstacleDetector.
     *
     * Initialise le capteur de distance et configure les paramètres nécessaires pour la détection.
     */
    ObstacleDetector();

    /**
     * @brief Obtient la distance du capteur à l'obstacle le plus proche.
     * @return uint8_t Distance en centimètres à l'obstacle détecté.
     */
    uint8_t getDistance();

    /**
     * @brief Détermine la position de l'obstacle détecté.
     * @return SpotPosition Position de l'obstacle (gauche, droite, centre, etc.).
     */
    SpotPosition getSpotPosition();

    /**
     * @brief Vérifie si un obstacle est détecté dans la plage spécifiée.
     * @return bool Vrai si un obstacle est détecté, faux sinon.
     */
    bool isSpotDetected();

private:
    Can can_; // Interface CAN pour la communication avec le capteur.
};

#endif
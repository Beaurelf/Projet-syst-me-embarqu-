/**
 * @file ObstacleDetector.cpp
 * @brief Implémentation de la classe ObstacleDetector pour la détection d'obstacles.
 *
 * Ce fichier implémente les méthodes de la classe ObstacleDetector. Il gère la logique de
 * détection des obstacles en utilisant un capteur de distance, permettant au robot de réagir
 * à la présence d'obstacles dans son environnement.
 */

#include "ObstacleDetector.hpp"

ObstacleDetector::ObstacleDetector() {}

uint8_t ObstacleDetector::getDistance()
{
    uint16_t distanceSum = 0;
    // on effectue plusieurs lecture
    for (uint8_t i = 0; i < N_READ; ++i)
        distanceSum += can_.read(DETECTOR_OUTPUT) >> PRECISION_BIT_SHIFT;
    return distanceSum / N_READ;
}

SpotPosition ObstacleDetector::getSpotPosition()
{
    return SpotPosition::NOTHING;
}

bool ObstacleDetector::isSpotDetected()
{
    uint8_t distance = getDistance();
    return distance >= MIN_DISTANCE_TO_DETECT && distance <= MAX_DISTANCE_TO_DETECT;
}

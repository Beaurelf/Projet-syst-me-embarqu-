/**
 * @file LineSensor.cpp
 * @brief Implémentation de la classe LineSensor pour la détection de lignes.
 *
 * Ce fichier implémente les méthodes de la classe LineSensor. Il gère la logique de
 * fonctionnement des capteurs de ligne du robot, permettant de détecter la position de la ligne
 * et d'ajuster le mouvement du robot en conséquence.
 */
#include "LineSensor.hpp"
#include "Communication.hpp"

LineSensor::LineSensor()
{
    initIO();
}

LinePosition LineSensor::determineLinePosition()
{

    bool leftMost = readLineSensorsState(DIGITAL_OUTPUT_D1);  // Capteur le plus à gauche (S1)
    bool left = readLineSensorsState(DIGITAL_OUTPUT_D2);      // Capteur gauche (S2)
    bool center = readLineSensorsState(DIGITAL_OUTPUT_D3);    // Capteur central (S3)
    bool right = readLineSensorsState(DIGITAL_OUTPUT_D4);     // Capteur droit (S4)
    bool rightMost = readLineSensorsState(DIGITAL_OUTPUT_D5); // Capteur le plus à droite (S5)

    bool cross = leftMost && left && center && right && rightMost; // permet de savoir si un cross
    bool crossLeft = left && center && leftMost && !rightMost;     // permet de savoir si un cross a gauche est detecté
    bool crossRight = right && center && rightMost && !leftMost;   // permet de savoir si un cross a droite est detecté

    // Si seulement le capteur central détecte la ligne, on est au centre
    if (!leftMost && !left && center && !right && !rightMost)
        return LinePosition::CENTER;
    // Si le capteur le plus gauche détecte la ligne, la ligne est  trop à gauche
    else if (leftMost && !left && !center && !right && !rightMost)
        return LinePosition::MOST_LEFT;
    // Si le capteur le plus a droite détecte la ligne, la ligne est trop à droite
    else if (!leftMost && !left && !center && !right && rightMost)
        return LinePosition::MOST_RIGHT;
    // Si les capteur de gauche détectent la ligne, la ligne est à gauche
    else if (left && !crossLeft && !right && !rightMost)
        return LinePosition::LEFT;
    // Si les capteur de gauche détectent la ligne, la ligne est à gauche
    else if (right && !crossRight && !left && !leftMost)
        return LinePosition::RIGHT;
    // Si aucun capteur ne détecte la ligne, elle est perdue
    else if (!leftMost && !left && !center && !right && !rightMost)
        return LinePosition::LOST;
    // si les capteur de gauche et du centre détectent la ligne il y a un croissement a gauche
    else if (crossLeft)
        return LinePosition::CROSS_LEFT_DETECTED;
    // si les capteur de droite et du centre détectent la ligne il y a un croissement a droite
    else if (crossRight)
        return LinePosition::CROSS_RIGHT_DETECTED;
    // Si tous les capteurs détectent la ligne, c'est un croisement
    else if (cross)
        return LinePosition::CROSS_DETECTED;
    return LinePosition::UNDEFINED;
}

bool LineSensor::readLineSensorsState(const uint8_t sensorPin)
{
    return (PINA & (1 << sensorPin)) == (1 << sensorPin);
}

void LineSensor::initIO()
{
    clearRegisterBits(&DDRA, DIGITAL_OUTPUT_D1);
    clearRegisterBits(&DDRA, DIGITAL_OUTPUT_D2);
    clearRegisterBits(&DDRA, DIGITAL_OUTPUT_D3);
    clearRegisterBits(&DDRA, DIGITAL_OUTPUT_D4);
    clearRegisterBits(&DDRA, DIGITAL_OUTPUT_D5);
}
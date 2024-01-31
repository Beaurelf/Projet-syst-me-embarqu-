/**
 * @file LineSensor.h
 * @brief Définition de la classe LineSensor pour la détection de ligne.
 *
 * La classe LineSensor fournit des fonctionnalités pour détecter la position d'une ligne
 * sur laquelle le robot est positionné. Elle utilise un capteur de suiveur de ligne pour déterminer
 * la position précise de la ligne par rapport au robot.
 */
#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <avr/io.h>
#include "interfaces/emun/LinePosition.hpp"
#include "interfaces/utils.hpp"
#include "interfaces/consts_lib.hpp"

/**
 * @class LineSensor
 * @brief Classe pour la détection de ligne à l'aide de capteurs.
 *
 * Cette classe gère l'ensemble des capteurs de ligne et fournit des méthodes pour déterminer
 * la position de la ligne par rapport au robot. Elle est essentielle pour le suivi de ligne
 * et les manœuvres de navigation basées sur les capteurs.
 */
class LineSensor
{
public:
    friend class Robot;

private:
    // Constructeur et destructeur
    LineSensor();
    ~LineSensor() = default;

    /**
     * @brief Détermine la position de la ligne par rapport au robot.
     * @return LinePosition Position de la ligne (perdue, gauche, droite, etc.).
     */
    LinePosition determineLinePosition();

    /**
     * @brief Lit l'état du capteur de ligne spécifié.
     * @param sensorPin Le numéro de la broche du capteur à lire.
     * @return bool Vrai si la ligne est détectée sur la broche spécifiée, faux sinon.
     */
    bool readLineSensorsState(const uint8_t sensorPin);

    /**
     * @brief Initialise les entrées/sorties pour les capteurs de ligne.
     *
     * Configure les broches des capteurs de ligne en tant qu'entrées numériques.
     */
    void initIO();
};

#endif
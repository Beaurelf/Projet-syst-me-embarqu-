/**
 * @file Navigation.hpp
 * @brief Définition de la classe Navigation pour gérer les mouvements du robot.
 *
 * Cette classe fournit des méthodes pour contrôler les mouvements du robot, comme avancer,
 * reculer, tourner à gauche ou à droite. Elle repose sur la gestion des deux roues du robot
 * en utilisant la classe `Roue` pour chaque roue.
 *
 * Description Materielle:
 * - les broches PB4 et PB6 sont respectivement connectés aux enable et direction de la roue gauche.
 * - les broches PB3 et PB5 sont respectivement connectés aux enable et direction de la roue droite.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 2.0
 * @date [Date]
 */

#ifndef NAVIGATION_H
#define NAVIGATION_H
#include "Wheel.hpp"
#include "Timer.hpp"
#include "interfaces/emun/Direction.hpp"
#include "util/delay.h"
#include "Can.hpp"
#include "interfaces/consts_lib.hpp"

/**
 * @class Navigation
 * @brief Classe pour gérer les mouvements du robot.
 *
 * Cette classe intègre deux objets de type `Roue` représentant les roues gauche et droite du robot.
 * Elle offre des méthodes pour le déplacement et le contrôle directionnel du robot.
 */
class Navigation
{
public:
    /**
     * @brief Constructeur de la classe Navigation.
     * @param timer Pointeur vers l'objet Timer de type Timer 1 utilisé pour contrôler les roues.
     */
    Navigation();

    // destructeur de la classe
    ~Navigation();

    /**
     * @brief Initialise les ports d'entrée/sortie nécessaires.
     */
    void initIO();

    /**
     * @brief Contrôle le mouvement des roues dans une direction spécifique.
     * @param direction Direction du mouvement.
     * @param speedLeft La vitesse à laquelle le roue gauche doit se déplacer.
     * @param speedRight La vitesse à laquelle le roue droite doit se déplacer.
     */
    void moveWheelToDirection(const Direction &direction, const double speedLeft, const double speedRight);

    /**
     * @brief Arrête le robot.
     */
    void stop();

    /**
     * @brief Effectue un virage de 90 degrés.
     * @param direction Direction du virage (gauche ou droite).
     *        Permet de spécifier la direction du virage à effectuer.
     */
    void turn90Degre(const Direction &direction);

    /**
     * @brief Effectue un demi-tour de 180 degrés.
     * @param direction Direction initiale du demi-tour (gauche ou droite).
     *        Indique la direction initiale du virage pour le demi-tour.
     */
    void turn180Degre(const Direction &direction);

    /**
     * @brief Effectue un tour complet de 360 degrés.
     * Le robot effectue un tour complet sur lui-même.
     */
    void turn360Degre();

private:
    // -- -Constantes pour la configuration des ports-- -
    // Ports pour la direction des roues
    static const uint8_t LEFT_WHEEL_DIRECTION = PB6;
    static const uint8_t RIGHT_WHEEL_DIRECTION = PB5;

    // Ports pour l'activation des roues (PWM)
    static const uint8_t LEFT_WHEEL_ENABLE = PB4;  // ocr0B
    static const uint8_t RIGHT_WHEEL_ENABLE = PB3; // ocr0A
    Wheel leftWheel_;                              // Objet Roue pour la roue gauche.
    Wheel rightWheel_;                             // Objet Roue pour la roue droite.
    Timer<0> timer_;                               // Timer pour le PWM des roues

    /**
     * @brief Fait tourner le robot vers la gauche.
     * @param speedLeft La vitesse à laquelle le roue gauche doit se déplacer.
     * @param speedRight La vitesse à laquelle le roue droite doit se déplacer.
     */
    void turnLeft(const double speedLeft, const double speedRight);

    /**
     * @brief Fait tourner le robot vers la droite.
     * @param speedLeft La vitesse à laquelle le roue gauche doit se déplacer.
     * @param speedRight La vitesse à laquelle le roue droite doit se déplacer.
     */
    void turnRight(const double speedLeft, const double speedRight);

    /**
     * @brief Déplace le robot vers l'avant.
     * @param speedLeft La vitesse à laquelle le roue gauche doit se déplacer.
     * @param speedRight La vitesse à laquelle le roue droite doit se déplacer.
     */
    void moveForward(const double speedLeft, const double speedRight);

    /**
     * @brief Déplace le robot vers l'arrière.
     * @param speedLeft La vitesse à laquelle le roue gauche doit se déplacer.
     * @param speedRight La vitesse à laquelle le roue droite doit se déplacer.
     */
    void moveBackward(const double speedLeft, const double speedRight);
};
#endif
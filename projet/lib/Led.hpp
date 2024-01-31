/**
 * @file Led.h
 * @brief Définition et interface de la classe Led.
 *
 * La classe Led permet de gérer et de contrôler une LED RGB. Elle offre des fonctionnalités
 * pour allumer, éteindre et faire clignoter la LED avec différentes couleurs. Elle est conçue
 * pour être utilisée avec des LEDs Bicolore ayant des pins séparés pour les composantes Rouge et Verte.
 *
 * La combinaison des LEDs Rouge et Verte permet d'obtenir différentes couleurs telles que l'Ambre.
 * La gestion du clignotement de l'Ambre nécessite un traitement spécial
 * en raison de la combinaison des couleurs Rouge et Verte.
 *
 * Descritpion Materielle:
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#ifndef LED_H
#define LED_H
#include "interfaces/utils.hpp"
#include "util/delay.h"
#include "interfaces/emun/LedColor.hpp"
#include "Timer.hpp"
#include "interfaces/consts_lib.hpp"

/**
 * @class Led
 * @brief Classe permettant de contrôler une LED Bicolore.
 *
 * La classe Led permet de manipuler une LED Bicolore, en permettant de
 * la piloter à travers ses pins associés pour l'allumer, l'éteindre,
 * ou la faire clignoter avec différentes couleurs.
 * Pour faire clignoter la led utiliser le port D
 */
class Led
{
public:
    /**
     * @brief Constructeur de la classe Led.
     *
     * @param port Le registre du port où la LED est connectée.
     * @param mode Le registre de mode du port.
     * @param pinGreen Le numéro de la broche de la LED verte.
     * @param pinRed Le numéro de la broche de la LED rouge.
     */
    Led(Register port, Register mode, uint8_t pinGreen, uint8_t pinRed);

    /**
     * @brief Destructeur de la classe Led.
     */
    ~Led();

    /**
     * @brief Éteint la LED.
     */
    void turnOffLed();

    /**
     * @brief Allume la LED avec une couleur spécifiée.
     *
     * @param color La couleur avec laquelle la LED doit être allumée.
     */
    void turnOnLed(const LedColor &color);

    /**
     * @brief Fait clignoter la LED avec une couleur et une durée spécifiées.
     *
     * @param color La couleur de clignotement de la LED.
     * @param blinkDurationMs La durée de clignotement en millisecondes.
     */
    void blinkLed(const LedColor &color, const uint32_t blinkDurationMs);

    /**
     * @brief Fait clignoter la LED en Ambre.
     *
     * @param blinkDurationMs La durée de clignotement en millisecondes.
     */
    void blinkInAmber(uint16_t blinkDurationMs);

private:
    Register port_;    // Le registre du port de la LED.
    Register mode_;    // Le registre de mode du port de la LED.
    uint8_t pinGreen_; // Numéro de broche de la LED verte.
    uint8_t pinRed_;   // Numéro de broche de la LED rouge.
};

#endif // LED_H

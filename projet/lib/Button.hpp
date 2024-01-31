/**
 * @file Button.hpp
 * @brief Définition de la classe Button pour la gestion d'un bouton poussoir avec le microcontrôleur ATmega324PA.
 *
 * Ce fichier fournit une interface pour gérer facilement les boutons poussoirs connectés au microcontrôleur ATmega324PA.
 * La classe encapsule des fonctionnalités telles que la détection d'appui sur un bouton et utilise un mécanisme de
 * "debouncing" pour éviter les lectures erronées dues aux rebonds électriques du bouton.
 *
 * @details faire l'identificationn materielle !!!
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date 2023-10-26
 */
#ifndef BUTTON_H
#define BUTTON_H

#include "util/delay.h"
#include "interfaces/utils.hpp"
#include "interfaces/emun/ButtonMode.hpp"

/**
 * @class Button
 * @brief Classe pour gérer un bouton poussoir sur le microcontrôleur ATmega324PA.
 *
 * Cette classe fournit les méthodes nécessaires pour initialiser, lire et déterminer l'état d'un bouton poussoir.
 * Elle utilise également une technique de "debouncing" pour s'assurer que l'état lu est stable et exempt d'interférences
 * dues aux rebonds électriques du bouton.
 *
 */
class Button
{
public:
    /**
     * @brief Constructeur de la classe Button.
     *
     * @param mode Mode du port (Entrée/Sortie).
     * @param pin Pin du port pour lire l'état du bouton.
     * @param pinNumber Numéro du pin sur lequel le bouton est connecté.
     * @param buttonMode Mode du bouton (Actif haut/Actif bas).
     */
    Button(Register mode, Register pin, uint8_t pinNumber, const ButtonMode &buttonMode);

    /**
     * @brief Destructeur de la classe Button.
     */
    ~Button();

    /**
     * @brief Vérifie si le bouton est pressé.
     *
     * @return true si le bouton est pressé, false sinon.
     */
    bool isPressed();

private:
    Register pin_;                              // PIN permet de lire la valeur du bouton (0 ou 1).
    ButtonMode buttonMode_;                     // Mode du bouton (Actif haut/Actif bas).
    uint8_t pinButton_;                         // Numéro du pin sur lequel le bouton est connecté.
    static const uint8_t DELAY_DEBOUNE_MS = 25; // Délai de debounce en millisecondes.
};

#endif
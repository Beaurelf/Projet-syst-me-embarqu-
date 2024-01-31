/**
 * @file Button.cpp
 * @brief Implémentation de la classe Button pour la gestion d'un bouton poussoir avec le microcontrôleur ATmega324PA.
 *
 * Ce fichier contient l'implémentation des méthodes de la classe Button définies dans Button.hpp.
 * La classe permet la gestion des boutons poussoirs en encapsulant les fonctionnalités nécessaires pour
 * initialiser, lire et déterminer l'état d'un bouton poussoir.
 *
 * @author [Nom de l'auteur]
 * @date [Date]
 *
 */
#include "Button.hpp"

Button::Button(Register mode, Register pin, uint8_t pinButton, const ButtonMode &buttonMode) : pin_(pin), buttonMode_(buttonMode), pinButton_(pinButton)
{
    clearRegisterBits(mode, pinButton_);
}

bool Button::isPressed()
{
    uint8_t reading1 = *pin_ & (1 << pinButton_);
    _delay_ms(DELAY_DEBOUNE_MS);
    uint8_t reading2 = *pin_ & (1 << pinButton_);
    bool signalIsHigh = (buttonMode_ == ButtonMode::PULL_DOWN) ? reading1 == (1 << pinButton_) : reading1 != (1 << pinButton_);
    bool signalIsStable = reading1 == reading2;
    return signalIsHigh && signalIsStable;
}

Button::~Button() = default;
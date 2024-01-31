/**
 * @file Led.cpp
 * @brief Implémentation de la classe Led pour contrôler une LED Bicolore.
 *
 * Ce fichier fournit l'implémentation des méthodes définies dans Led.hpp pour manipuler
 * une LED Bicolore. La classe Led permet de contrôler une LED Bicolre à travers ses pins
 * correspondants, en offrant des fonctionnalités pour l'allumer, l'éteindre,
 * et la faire clignoter dans différentes couleurs.
 *
 * @details rajouter la description materiel pour la led !!!!!!!!!!!
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#include "Led.hpp"

Led::Led(Register port, Register mode, uint8_t pinGreen, uint8_t pinRed) : port_(port), mode_(mode), pinGreen_(pinGreen), pinRed_(pinRed)
{
    setRegisterBits(mode, pinGreen_);
    setRegisterBits(mode, pinRed_);
}

void Led::turnOffLed()
{
    clearRegisterBits(port_, pinGreen_);
    clearRegisterBits(port_, pinRed_);
    // isLedBlinked_ = false;
}

void Led::turnOnLed(const LedColor &color)
{
    turnOffLed();
    switch (color)
    {
    case LedColor::RED:
        setRegisterBits(port_, pinRed_);
        break;
    case LedColor::GREEN:
        setRegisterBits(port_, pinGreen_);
        break;
    default:
        break;
    }
}

void Led::blinkLed(const LedColor &color, const uint32_t blinkDurationMs)
{
    for (uint8_t i = 0; i < blinkDurationMs / (2 * DELAY_MS_PER_BLINK); i++)
    {
        turnOnLed(color);
        _delay_ms(DELAY_MS_PER_BLINK);
        turnOffLed();
        _delay_ms(DELAY_MS_PER_BLINK);
    }
}

void Led::blinkInAmber(uint16_t blinkDurationMs)
{
    for (uint8_t i = 0; i < blinkDurationMs / (DELAY_GREEN_MS + DELAY_RED_MS); i++)
    {
        turnOnLed(LedColor::GREEN);
        _delay_ms(DELAY_GREEN_MS);
        turnOnLed(LedColor::RED);
        _delay_ms(DELAY_RED_MS);
    }
    turnOffLed();
}

Led::~Led() {}
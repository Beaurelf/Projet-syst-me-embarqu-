/**
 * @file Wheel.cpp
 * @brief Implémentation de la classe Wheel pour la gestion des mouvements d'une Wheel motorisée.
 *
 * Ce fichier contient les détails d'implémentation des méthodes déclarées dans Wheel.h.
 * Il fournit la logique nécessaire pour démarrer, arrêter, et changer la direction
 * de la Wheel en utilisant un Timer pour la modulation de largeur d'impulsion (PWM).
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#include "Wheel.hpp"

Wheel::Wheel(Timer<0> *timer, uint8_t directionPort, volatile uint8_t *ocrRegister) : wheelDirectionPort_(directionPort)
{
    timer_ = timer;
    ocrRegister_ = ocrRegister;
};

void Wheel::move(const double speed)
{
    timer_->setOCRnXRegister(speed, ocrRegister_);
}

void Wheel::stop()
{
    move(0.0);
}

void Wheel::turnWheelBackward(const double speed)
{
    setRegisterBits(&PORTB, wheelDirectionPort_);
    move(speed);
}

void Wheel::turnWheelForward(const double speed)
{
    clearRegisterBits(&PORTB, wheelDirectionPort_);
    move(speed);
}
/**
 * @file Chrono.cpp
 *
 * @brief Implémentation de la classe Chrono définie dans "Chrono.hpp".
 *
 * La classe Chrono fournit un chronomètre basé sur une instance de Timer.
 * Ce fichier contient le code pour les méthodes qui contrôlent ce chronomètre,
 * notamment les fonctions pour le démarrer et l'arrêter.
 *
 * @author [Votre Nom ou celui de l'équipe]
 * @version 1.0
 * @date [Date de création ou de modification]
 *
 * @note il faut implementer la routine d'interruption dans le main elle incrementera nCyclePassed et
 * verifier si le chrono a expiré et execute les instructions a faire
 */
#include "Chrono.hpp"

Chrono::Chrono() : timer_(TimerMode::CTC, Prescaler::PRESCALER_1024), nCyclesPassed(0) {}

void Chrono::start(double durationS)
{
    nCyclesNeeded = static_cast<uint16_t>(durationS / DELAY_INTERRUPT_S);
    timer_.setOCRnXRegister(DELAY_INTERRUPT_S, &OCR1A);
    timer_.enable();
}

void Chrono::incrementCycles()
{
    nCyclesPassed++;
}

bool Chrono::isTimerExpired()
{
    if (nCyclesNeeded > 0)
    {
        incrementCycles();
        if (nCyclesPassed >= nCyclesNeeded)
        {
            reset(); // Réinitialiser le compteur après l'expiration
            return true;
        }
        else
            return false;
    }
    return false;
}

void Chrono::reset()
{
    nCyclesNeeded = 0;
    nCyclesPassed = 0;
}

void Chrono::stop()
{
    nCyclesNeeded = 0;
    nCyclesPassed = 0;
    timer_.disable();
}
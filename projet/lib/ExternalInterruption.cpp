/**
 * @file ExternalInterruption.cpp
 * @brief Implémentation pour la classe ExternalInterruption.
 *
 * Ce fichier fournit les définitions des méthodes pour gérer les interruptions externes sur un microcontrôleur AVR.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date 2023-10-26
 */

#include "ExternalInterruption.hpp"

void ExternalInterruption::enable(const ExternalInterrupt &externalInterrupt, const InterruptTrigger &interrupTigger)
{
    ExternalInterruptionConfig::enableExternalInterrupt(externalInterrupt);
    ExternalInterruptionConfig::configureInterruptTrigger(externalInterrupt, interrupTigger);
}

void ExternalInterruption::disable(const ExternalInterrupt &externalInterrupt)
{
    ExternalInterruptionConfig::clearExternalInterrupt(externalInterrupt);
}

void ExternalInterruption::disableAllExternalInterruption()
{
    ExternalInterruptionConfig::clearAllExternalInterrupt();
}

void ExternalInterruption::changeTigger(const ExternalInterrupt &externalInterrupt, const InterruptTrigger &interrupTigger)
{
    ExternalInterruptionConfig::configureInterruptTrigger(externalInterrupt, interrupTigger);
}
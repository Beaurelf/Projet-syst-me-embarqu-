/**
 * @file ExternalInterruptEnum.h
 * @brief Fichier d'en-tête définissant les énumérations pour les interruptions externes.
 *
 * Ce fichier définit les types d'interruptions externes disponibles et
 * les différents déclencheurs d'interruption qui peuvent être utilisés.
 */

#ifndef EXTERNAL_INTERRUPT_ENUM_H
#define EXTERNAL_INTERRUPT_ENUM_H

// Énumération représentant les différents types d'interruptions externes disponibles.
enum class ExternalInterrupt
{
    INT_0, // Interruption externe de type 0.
    INT_1, // Interruption externe de type 1.
    INT_2  // Interruption externe de type 2.
};

// Énumération décrivant les différents déclencheurs d'interruption.
enum class InterruptTrigger
{
    LOW_LEVEL,    // Déclenché lorsque le niveau est bas.
    ANY_EDGE,     // Déclenché sur n'importe quel bord (montant ou descendant).
    FALLING_EDGE, // Déclenché sur le bord descendant.
    RISING_EDGE   // Déclenché sur le bord montant.
};

#endif

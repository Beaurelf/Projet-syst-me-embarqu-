#ifndef INTERRUPTION_CONFIG_H
#define INTERRUPTION_CONFIG_H

#include <stdint.h>

/**
 * @struct InterruptConfig
 * @brief Représente les configurations pour une seule interruption externe.
 */
struct InterruptConfig
{
    uint8_t interruptionType; // Type pour l'interruption spécifique.
    uint8_t ISCn0;            // Bit de configuration pour le contrôle de sens de l'interruption.
    uint8_t ISCn1;            // Bit de configuration pour le contrôle de sens de l'interruption.
};

#endif
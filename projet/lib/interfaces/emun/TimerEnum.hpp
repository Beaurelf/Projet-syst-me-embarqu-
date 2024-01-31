/**
 * @file TimerEnum.hpp
 * @brief Fichier d'en-tête contenant les énumérations pour la configuration des timers sur un ATmega324PA.
 *
 * Ce fichier définit les modes de fonctionnement possibles des timers ainsi que les valeurs de prédiviseurs
 * disponibles pour la configuration des timers.
 */

#ifndef TIMER_ENUM_H
#define TIMER_ENUM_H

// Énumération décrivant les modes de fonctionnement possibles d'un timer.
enum class TimerMode
{
    NORMAL, // Mode de fonctionnement normal.
    PWM,    // Mode Pulse Width Modulation (Modulation de Largeur d'Impulsion).
    CTC     // Mode Clear Timer on Compare Match (Réinitialise le timer lors d'une concordance de comparaison).
};

// Énumération décrivant les différentes valeurs de prédiviseurs pour la configuration des timers.
enum class Prescaler
{
    NO_PRESCALER = 0,     // Pas de prédiviseur.
    PRESCALER_8 = 8,      // Prédiviseur de 8.
    PRESCALER_64 = 64,    // Prédiviseur de 64.
    PRESCALER_256 = 256,  // Prédiviseur de 256.
    PRESCALER_1024 = 1024 // Prédiviseur de 1024.
};

#endif

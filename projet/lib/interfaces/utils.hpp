/**
 * @file Utils.hpp
 * @brief Utilitaires pour la manipulation des registres AVR.
 *
 * Ce fichier fournit des fonctions inline pour manipuler efficacement les bits individuels
 * dans les registres AVR, tels que la définition et la suppression des bits.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */

#ifndef UTILS_H
#define UTILS_H
#define F_CPU 8000000UL
#include <avr/io.h>

/// Type défini pour représenter un registre AVR.
typedef volatile uint8_t *Register;

/**
 * @brief Définit un bit spécifique dans un registre AVR donné.
 *
 * @param avrRegister Pointeur vers le registre AVR à modifier.
 * @param bit Index du bit à définir (0-7).
 */
inline void setRegisterBits(Register avrRegister, const uint8_t bit)
{
    *avrRegister |= _BV(bit);
}

/**
 * @brief Efface un bit spécifique dans un registre AVR donné.
 *
 * @param avrRegister Pointeur vers le registre AVR à modifier.
 * @param bit Index du bit à effacer (0-7).
 */
inline void clearRegisterBits(Register avrRegister, const uint8_t bit)
{
    *avrRegister &= ~_BV(bit);
}

#endif
/**
 * @file TabSchema.h
 * @brief Définition de la structure TabSchema pour représenter un tableau de schémas.
 *
 * Ce fichier contient la définition de la structure TabSchema, utilisée pour stocker un tableau
 * de caractères représentant un schéma ou une séquence de commandes. Cette structure est utile
 * pour modéliser des séquences de trajet dans un format compact.
 */

#ifndef TAB_SCHEMA_H
#define TAB_SCHEMA_H

#include "stdint.h"

const uint8_t MAX_ARRAY_LENGTH = 5; // Longueur maximale du tableau de schémas.

/**
 * @struct TabSchema
 * @brief Structure représentant un tableau de schémas ou de séquences.
 *
 * La structure TabSchema est utilisée pour stocker un tableau de caractères représentant un schéma
 * spécifique, une séquence de mouvement comme des caractères dans un format compact.
 * Elle inclut également une variable pour indiquer la taille actuelle du tableau.
 */
struct TabSchema
{
    char tabSchema[MAX_ARRAY_LENGTH]; // Tableau de caractères représentant le schéma.
    uint8_t size;                     // Taille actuelle du tableau, indiquant le nombre d'éléments stockés.
};

#endif // TAB_SCHEMA_H

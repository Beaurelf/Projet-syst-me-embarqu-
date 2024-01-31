/**
 * @file ButtonMode.h
 * @brief Fichier d'en-tête définissant les modes possibles pour un bouton.
 *
 * Ce fichier définit une énumération pour les différents modes
 * de configuration d'un bouton, spécifiquement en termes de
 * résistances pull-up et pull-down.
 */

#ifndef BUTTON_MODE_H
#define BUTTON_MODE_H

// Énumération représentant les modes de configuration d'un bouton.
enum class ButtonMode
{
    PULL_UP,  // Mode avec résistance pull-up activée.
    PULL_DOWN // Mode avec résistance pull-down activée.
};

#endif

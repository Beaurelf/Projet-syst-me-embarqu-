/**
 * @file Sound.hpp
 * @brief Classe Sound pour la gestion de la sortie audio.
 *
 * La classe Sound encapsule la fonctionnalité pour jouer des sons via un buzzer ou un
 * haut-parleur connecté à un pin du microcontrôleur. Elle utilise un objet Timer pour
 * générer des fréquences de notes correspondantes.
 *
 * Descritpion Materielle: le pin de signal est PD7 et l'autre borne du buzzer est branche sur PD6 (toujours a 0 Volt)
 *
 * @version 1.0
 * @date [Date]
 */

#ifndef SOUND_H
#define SOUND_H
#include "Timer.hpp"
#include "util/delay.h"
#include "interfaces/emun/NoteFrequency.hpp"
#include "interfaces/consts_lib.hpp"

// le pin de signal est PD7

/**
 * @class Sound
 * @brief Classe pour la gestion du son.
 *
 * La classe Sound permet de jouer des notes musicales en contrôlant la fréquence
 * de la sortie d'un timer connecté à un buzzer ou à un haut-parleur. Elle offre
 * une interface simple pour démarrer et arrêter la lecture d'une note.
 */
class Sound
{
private:
    Timer<2> timer_;  // Instance de Timer pour contrôler les fréquences des notes
    bool isSongPlay_; // Flag pour indiquer si une note est en train d'être jouée

public:
    Sound();            // Constructeur
    ~Sound() = default; // Destructeur par défaut

    /**
     * @brief Joue une note musicale.
     * @param noteNumber Le numéro de la note à jouer basé sur l'énumération NoteFrequency.
     */
    void play(uint8_t noteNumber);

    /**
     * @brief Joue le song du film pirates des caraibes
     */
    void playPiratesDesCaraibesSong();

    /**
     * @brief Arrête de jouer la note musicale.
     */
    void stop();
};

#endif
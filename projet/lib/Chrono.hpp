/**
 *  @file Chrono.hpp
 *  @brief Ce fichier contient la déclaration de la classe Chrono
 *
 * La classe Chrono est une abstraction représentant un chronomètre qui utilise une instance du
 * Timer (comme défini dans "Timer.hpp") pour suivre le temps. Elle offre des fonctions pour démarrer et
 * arrêter le chronomètre. Le chronomètre est conçu pour être simple à utiliser, tout en offrant la précision et la fiabilité
 * requises pour les tâches de mesure du temps dans divers contextes.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#ifndef CHRONO_H
#define CHRONO_H
#include "Timer.hpp"
#include "avr/interrupt.h"

/**
 * @class Chrono
 *
 * Cette classe représente un chronomètre simple. Elle offre la possibilité de démarrer et
 * d'arrêter un chronomètre basé sur un timer. L'utilisation précise du timer n'est pas immédiatement
 * évidente sans accéder à l'implémentation ou à la documentation du Timer.
 */

class Chrono
{
public:
    /**
     * @brief Constructeur par défaut.
     * Initialise les membres internes de la classe, probablement en mettant le timer en état d'initialisation.
     */
    Chrono();
    /**
     * @brief Démarre le chronomètre.
     *
     * @param durationS Durée en secondes après laquelle le timer doit se terminer ou déclencher une action.
     */
    void start(double durationS);

    /**
     * @brief incremente nCyclesPassed.
     *
     */
    void incrementCycles();

    /**
     * @brief renvoie true lorsque le temps inmarti est arrivé.
     *
     */
    bool isTimerExpired();

    void reset();

    /**
     * @brief Arrête le chronomètre.
     * Cela pourrait interrompre le timer en cours ou simplement marquer la fin du décompte.
     */
    void stop();

private:
    // Un membre privé de type Timer. La valeur template '1' pourrait représenter une spécification particulière pour le Timer 2
    Timer<1> timer_;
    const double DELAY_INTERRUPT_S = 0.025;
    uint16_t nCyclesPassed; // nombre de cycle deja ecouler depuis le debut de compte du timer
    uint16_t nCyclesNeeded; // nombre de cycle dont on a besoin
};

#endif // CHRONO_H

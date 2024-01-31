/**
 * @file ExternalInterruption.hpp
 * @brief Définition de la classe ExternalInterruption.
 *
 * Cette classe offre une interface pour gérer les interruptions externes sur un microcontrôleur AVR.
 * Elle fournit des méthodes pour activer, désactiver, et modifier le type de déclencheur d'une interruption externe.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date 2023-10-26
 */

#ifndef INTERRUPTION_H
#define INTERRUPTION_H
#include "ExternalInterruptConfig.hpp" //demander a tristan comment remmetrre ca dans interface

/**
 * @class ExternalInterruption
 * @brief Classe pour gérer les interruptions externes sur un microcontrôleur AVR.
 *
 * Cette classe fournit une abstraction pour les opérations courantes associées aux interruptions externes.
 * Elle permet d'activer, de désactiver et de modifier le type de déclencheur pour les interruptions externes.
 */
class ExternalInterruption
{
public:
    ExternalInterruption() = delete;
    ExternalInterruption(const ExternalInterruption &externalInterruption) = delete;
    /**
     * @brief Active une interruption externe spécifiée avec un type de déclencheur donné.
     *
     * @param externalInterrupt L'interruption externe à activer.
     * @param interrupTigger Le type de déclencheur pour cette interruption.
     */
    static void enable(const ExternalInterrupt &externalInterrupt, const InterruptTrigger &interrupTigger);

    /**
     * @brief Désactive une interruption externe spécifiée.
     *
     * @param externalInterrupt L'interruption externe à désactiver.
     */
    static void disable(const ExternalInterrupt &externalInterrupt);

    /**
     * @brief Désactive toutes les interruptions externes.
     */
    static void disableAllExternalInterruption();

    /**
     * @brief Modifie le type de déclencheur pour une interruption externe spécifiée.
     *
     * @param externalInterrupt L'interruption externe dont le type de déclencheur doit être modifié.
     * @param interrupTigger Le nouveau type de déclencheur pour cette interruption.
     */
    static void changeTigger(const ExternalInterrupt &externalInterrupt, const InterruptTrigger &interrupTigger);
};

#endif

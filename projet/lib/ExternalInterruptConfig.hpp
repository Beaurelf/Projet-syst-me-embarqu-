/**
 * @file ExternalInterruptionConfig.h
 * @brief Fichier d'en-tête pour la configuration des interruptions externes sur un ATmega324PA.
 *
 * Ce fichier contient la définition de la classe ExternalInterruptionConfig, qui fournit
 * des méthodes pour configurer et gérer les interruptions externes de l'ATmega324PA.
 * La classe offre des outils pour définir le type de déclenchement de l'interruption,
 * activer/désactiver les interruptions, et réinitialiser les configurations.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#include "interfaces/utils.hpp"
#ifndef EXTERNAL_INTERRUPTION_CONFIG_H
#define EXTERNAL_INTERRUPTION_CONFIG_H
#include "interfaces/utils.hpp"
#include "interfaces/emun/ExternalInterruptEnum.hpp"
#include "interfaces/struct/InterruptionConfig.hpp"
/**
 * @class ExternalInterruptionConfig
 * @brief Classe de configuration pour la gestion des interruptions externes sur un ATmega324PA.
 *
 * Cette classe fournit une série de méthodes statiques pour configurer et gérer les
 * interruptions externes disponibles sur un ATmega324PA. Elle offre des fonctions pour
 * configurer le type de déclenchement de l'interruption, activer/désactiver les
 * interruptions et effacer les configurations d'interruption.
 */
class ExternalInterruptionConfig
{
    // Donner à la classe ExternalInterruption un accès aux méthodes privées de cette classe.
    friend class ExternalInterruption;
public:
    ExternalInterruptionConfig() = delete;
    ExternalInterruptionConfig(const ExternalInterruptionConfig &externalInterruptionConfig) = delete;
private:
    /**
     * @brief Configurations pour les interruptions externes.
     *
     * Chaque configuration contient le type d'interruption, et les bits associés
     * à la configuration de déclenchement pour cette interruption.
     */
    static constexpr InterruptConfig InterruptConfigs[] = {
        {INT0, ISC00, ISC01},
        {INT1, ISC10, ISC11},
        {INT2, ISC20, ISC21}};
    /**
     * @brief Configure le type de déclenchement pour une interruption donnée.
     *
     * @param config La configuration de l'interruption.
     * @param trigger Le type de déclenchement.
     */
    static void setTriggerType(const InterruptConfig &config, const InterruptTrigger &trigger);
    /**
     * @brief Désactive et efface tous les réglages pour toutes les interruptions externes.
     */
    static void clearAllExternalInterrupt();
    /**
     * @brief Active une interruption externe spécifiée.
     *
     * @param interrupt L'interruption à activer.
     */
    static void enableExternalInterrupt(const ExternalInterrupt &interrupt);
    /**
     * @brief Configure le type de déclenchement pour une interruption externe spécifiée.
     *
     * @param interrupt L'interruption à configurer.
     * @param trigger Le type de déclenchement.
     */
    static void configureInterruptTrigger(const ExternalInterrupt &interrupt, const InterruptTrigger &trigger);
    /**
     * @brief Désactive et efface les réglages pour une interruption externe spécifiée.
     *
     * @param interrupt L'interruption à effacer.
     */
    static void clearExternalInterrupt(const ExternalInterrupt &interrupt);
};
#endif
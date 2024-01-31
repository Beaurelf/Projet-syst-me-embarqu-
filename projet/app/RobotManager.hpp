/**
 * @file RobotManager.hpp
 * @brief Définition de la classe RobotManager pour la gestion du robot.
 *
 * La classe RobotManager est responsable de la gestion des routines de navigation et de décision
 * du robot, en fonction de différents états de parcours et modes de fonctionnement. Elle agit
 * comme un coordinateur entre les différentes tâches du robot et son algorithme de navigation.
 */
#ifndef ROBOT_MANAGER_H
#define ROBOT_MANAGER_H
#include "Robot.hpp"
#include "Dijkstra.hpp"
#include "res/consts.hpp"

/**
 * @class RobotManager
 * @brief Classe pour la gestion des routines et modes de fonctionnement du robot.
 *
 * RobotManager gère les interactions et les routines du robot, en fonction des sélections,
 * validations, et modes choisis. Elle contrôle le déroulement des différentes tâches
 * et routines de navigation.
 */
class RobotManager
{
private:
    bool isSelected;  // Indique si une option de navigation est sélectionnée.
    bool isValidated; // Indique si une option de navigation est validée.
    bool isYes;       // Utilisé pour confirmer les sélections ou les décisions.

public:
    /**
     * @brief Constructeur de RobotManager.
     */
    RobotManager();

    /**
     * @brief Destructeur par défaut de RobotManager.
     */
    ~RobotManager() = default;

    /**
     * @brief Met à jour la routine de sélection de parcours.
     * @param pathConfigState État actuel du parcours du robot.
     */
    void updateSelectionJourneyRoutine(volatile PathConfigState &pathConfigState);

    /**
     * @brief Exécute la routine de sélection en fonction de l'état du parcours.
     * @param pathConfigState État actuel du parcours.
     * @param robot Pointeur vers l'instance du robot.
     */
    void executeSelectionRoutineMode(const volatile PathConfigState &pathConfigState, Robot *robot);

    /**
     * @brief Définit l'état de sélection.
     * @param value Nouvel état de sélection.
     */
    void setIsSelected(bool value);

    /**
     * @brief Définit l'état de validation.
     * @param value Nouvel état de validation.
     */
    void setIsValidated(bool value);

    /**
     * @brief Définit l'état de confirmation.
     * @param value Nouvel état de confirmation.
     */
    void setIsYes(bool value);

    /**
     * @brief Exécute la routine principale du robot en fonction du mode.
     * @param mode Mode de fonctionnement actuel du robot.
     * @param robot Pointeur vers l'instance du robot.
     * @param pathConfigState État actuel dde la configuration du parcours.
     */
    void runRobotRoutine(Robot *robot, volatile PathConfigState &pathConfigState);

    /**
     * @brief Exécute la routine d'identification des coins.
     * @param robot Pointeur vers l'instance du robot.
     */
    void executeIdentifyCornerRoutine(Robot *robot);

    /**
     * @brief Exécute la routine de réalisation de parcours.
     * @param robot Pointeur vers l'instance du robot.
     * @param pathConfigState État actuel dde la configuration du parcours.
     */
    void executeMakeJourneyRoutine(Robot *robot, volatile PathConfigState &pathConfigState);

    /**
     * @brief Réinitialise la routine de réalisation de parcours.
     * @param pathConfigState État actuel du parcours.
     * @param robot Pointeur vers l'instance du robot.
     * @param dijkstra Instance de l'algorithme de Dijkstra utilisé pour le calcul de parcours.
     */
    void resetMakeJourneyRoutine(volatile PathConfigState &pathConfigState, Robot *robot, Dijkstra &dijkstra);
};

#endif
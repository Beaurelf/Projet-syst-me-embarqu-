/**
 * @file RobotMode.h
 * @brief Définition de l'énumération RobotMode pour les modes de fonctionnement du robot.
 *
 * Ce fichier contient l'énumération RobotMode, qui est utilisée pour spécifier les différents modes
 * de fonctionnement dans lesquels le robot peut opérer. Chaque mode détermine un comportement ou une
 * routine spécifique que le robot va suivre.
 */

#ifndef ROBOT_MODE_H
#define ROBOT_MODE_H

/**
 * @enum RobotMode
 * @brief Énumération des modes de fonctionnement du robot.
 *
 * Cette énumération définit les différents modes opérationnels que le robot peut adopter. Chaque mode
 * correspond à une série de comportements ou de tâches spécifiques que le robot doit exécuter, allant
 * de l'identification des coins à la réalisation d'un parcours.
 */
enum class RobotMode
{
	UNDEFINED,		 // Mode non défini ou état initial.
	IDENTIFY_CORNER, // Mode pour identifier les coins dans l'environnement.
	MAKE_JOURNEY	 // Mode pour réaliser un parcours spécifié.
};

#endif // ROBOT_MODE_H

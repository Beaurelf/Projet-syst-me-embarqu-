/**
 * @file JourneyState.h
 * @brief Définition de l'énumération JourneyState pour les états de configuration.
 *
 * Ce fichier contient l'énumération JourneyState, qui est utilisée pour décrire les différents états
 * ou phases de choix dans le point  de destination dans le parcours du robot.
 */

#ifndef PATH_CONFIG_STATE_H
#define PATH_CONFIG_STATE_H

/**
 * @enum PathConfigState
 * @brief Énumération des différents états de configuration dans le processus de choix du point de destination
 * du robot.
 *
 * Cette énumération représente les différentes étapes ou états que le robot peut traverser lors de
 * la préparation et de l'exécution de son parcours au niveau de la configuration sur le LCD pour le choix
 * du point de destination, allant de l'initialisation à la finalisation du point de destination.
 */
enum class PathConfigState
{
	INIT_ROW,		   // Initialisation de la ligne de départ.
	INIT_COL,		   // Initialisation de la colonne de départ.
	SELECT_ROW,		   // Sélection de la ligne de destination.
	SELECT_COLUMN,	   // Sélection de la colonne de destination.
	CONFIRMATION,	   // Confirmation des choix de ligne et de colonne.
	INIT_CONFIRMATION, // Debut de l'etape de confirmation.
	RESET,			   // Réinitialisation du choix du point de destination.
	FINALIZED		   // Finalisation du choix du points de destination (choix validé).
};

#endif // PATH_CONFIG_STATE_H

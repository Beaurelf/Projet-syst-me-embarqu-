/**
 * @file CornerNode.h
 * @brief Définition de la structure CornerNode pour représenter un nœud dans un parcours de navigation.
 *
 * Ce fichier contient la définition de la structure CornerNode, utilisée pour stocker des informations
 * détaillées sur un nœud spécifique dans le cadre d'un parcours de navigation. Cela inclut les coordonnées
 * du nœud, les directions à prendre, et un schéma associé à ce nœud.
 */

#ifndef CORNER_NODE_H
#define CORNER_NODE_H

#include "res/struct/Coordinates.hpp"
#include "res/enum/Cardinal.hpp"
#include "interfaces/emun/Direction.hpp"
#include "res/struct/Corner.hpp"

static const int TAILLE_TAB = 5; // Taille maximale du tableau pour stocker le schéma.

/**
 * @struct CornerNode
 * @brief Structure représentant un nœud de coin dans un parcours de navigation.
 *
 * Cette structure contient les informations nécessaires pour naviguer à partir d'un coin spécifique,
 * y compris les coordonnées du coin, le schéma associé à ce coin, la longueur de ce schéma, et
 * les directions à prendre pour naviguer à partir de ce coin.
 */
struct CornerNode
{
	Corner corner;					 // Coin représentant la position du nœud.
	char schema[TAILLE_TAB];		 // Schéma associé à ce coin.
	int schemaLength;				 // Longueur du schéma associé.
	Direction directionToTurnFirst;	 // Première direction à tourner à ce coin.
	Direction directionToTurnSecond; // Seconde direction à tourner à ce coin.
};

#endif // CORNER_NODE_H

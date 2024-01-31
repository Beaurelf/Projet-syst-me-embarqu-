/**
 * @file SearchEngine.h
 * @brief Définition de la classe SearchEngine pour la gestion de recherche des coins initiaux.
 *
 * La classe SearchEngine offre des fonctionnalités pour la recherche et l'identification de schémas
 * de navigation et de points de repère spécifiques (tels que des coins) lors de la navigation du robot.
 * Elle joue un rôle crucial dans l'élaboration de schémas de navigation basés sur les données de capteurs
 * et d'autres entrées.
 */

#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "res/struct/CornerNode.hpp"
#include "res/struct/TabSchema.hpp"
#include "res/struct/Corner.hpp"
#include "res/config.hpp"
#include "res/utils.hpp"
#include "Communication.hpp"
#include "res/consts.hpp"

/**
 * @class SearchEngine
 * @brief Classe dédiée à la recherche de coin et à l'analyse de schémas de navigation.
 *
 * SearchEngine fournit des méthodes pour vérifier l'existence de schémas de navigation,
 * identifier des nœuds de coin spécifiques, et construire des schémas de navigation
 * basés sur les données de capteurs et d'autres critères. Elle joue un rôle crucial dans
 * l'élaboration des stratégies de pour identifier le coin initial.
 */
class SearchEngine
{

public:
	/**
	 * @brief Constructeur par défaut de SearchEngine.
	 */
	SearchEngine();

	/**
	 * @brief Vérifie si un schéma donné existe déjà.
	 * @param currentSchema Le schéma actuel à vérifier.
	 * @param length La longueur du schéma.
	 * @param cornerList La liste des nœuds de coin à comparer.
	 * @return int8_t L'indice du schéma s'il existe, -1 sinon.
	 */
	int8_t isSchemaExist(const char *currentSchema, uint8_t length, const CornerNode cornerList[]);

	/**
	 * @brief Identifie un nœud dans la liste des nœuds de coin.
	 * @param cornerList La liste des nœuds de coin.
	 * @param indice L'indice du nœud à identifier.
	 * @return CornerNode Le nœud de coin identifié.
	 */
	CornerNode identifyNode(const CornerNode *cornerList, uint8_t indice);

	/**
	 * @brief Construit un schéma de navigation basé sur l'étape actuelle.
	 * @param step L'étape actuelle de navigation.
	 * @param currentSchema Référence à un TabSchema pour stocker le schéma construit.
	 */
	void buildSchema(char step, TabSchema &currentSchema);
};

#endif
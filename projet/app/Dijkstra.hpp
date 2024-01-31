/**
 * @file Dijkstra.h
 * @brief Définition de la classe Dijkstra pour le calcul de chemin le plus court.
 *
 * La classe Dijkstra implémente l'algorithme de Dijkstra pour le calcul de chemins les plus courts.
 * Elle est utilisée pour déterminer le chemin optimal que le robot doit suivre, en tenant compte
 * des obstacles et des configurations de l'environnement.
 */

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "res/struct/Coordinates.hpp"
#include "res/config.hpp"
#include "res/struct/RoadSchema.hpp"
#include "res/consts.hpp"

/**
 * @class Dijkstra
 * @brief Classe implémentant l'algorithme de Dijkstra pour le calcul de chemins.
 *
 * Dijkstra fournit des méthodes pour générer des chemins optimaux entre deux points, détruire des chemins
 * en cas d'obstacles détectés, et initialiser la matrice d'adjacence utilisée pour le calcul des chemins.
 */
class Dijkstra
{
public:
    /**
     * @brief Constructeur de Dijkstra.
     *
     * Initialise l'algorithme de Dijkstra et prépare la matrice d'adjacence.
     */
    Dijkstra();

    /**
     * @brief Destructeur par défaut de Dijkstra.
     */
    ~Dijkstra() = default;

    /**
     * @brief Génère le chemin le plus court entre deux points.
     * @param startPoint Le point de départ.
     * @param endPoint Le point d'arrivée.
     * @return RoadSchema Le schéma du chemin le plus court calculé.
     */
    RoadSchema generateRoad(const Coordinate &startPoint, const Coordinate &endPoint); // Calcule et affiche le chemin le plus court

    /**
     * @brief Détruit un chemin en cas de détection d'obstacle.
     * @param destroyPoint Le point où un obstacle a été détecté.
     */
    void destroyPath(const Coordinate &destroyPoint);

    /**
     * @brief Initialise la matrice d'adjacence avec des valeurs infinies.
     */
    void initMatrix();

private:
    /**
     * @brief Définit les coûts des chemins dans la matrice d'adjacence.
     */
    void setCosts();

    /**
     * @brief Définit le coût d'un chemin entre deux nœuds.
     * @param node1 Le premier nœud.
     * @param node2 Le second nœud.
     * @param cost Le coût du chemin entre les deux nœuds.
     */
    void setCost(uint8_t node1, uint8_t node2, const uint8_t cost);

    /**
     * @brief Associe des coordonnées à une position dans la matrice.
     * @param point Les coordonnées à associer.
     * @return uint8_t La position dans la matrice correspondant aux coordonnées.
     */
    uint8_t matchPoint(const Coordinate &point);

    /**
     * @brief Associe une position dans la matrice à des coordonnées.
     * @param position La position dans la matrice.
     * @return Coordinate Les coordonnées correspondant à la position dans la matrice.
     */
    Coordinate matchCoordinates(uint8_t position);

    uint8_t matrix[SIZE][SIZE]; // Matrice d'adjacence pour les coûts des chemins.
};

#endif
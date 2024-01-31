/**
 * @file Dijkstra.cpp
 * @brief Implémentation de la classe Dijkstra pour le calcul de chemin le plus court.
 *
 * Ce fichier implémente les méthodes de la classe Dijkstra. Elle utilise l'algorithme de Dijkstra pour
 * calculer le chemin le plus court entre deux points dans un environnement qui peut inclure des obstacles.
 */
#include "Dijkstra.hpp"
#include "Communication.hpp"

// Constructeur de la classe Dijkstra
Dijkstra::Dijkstra()
{
    initMatrix(); // Initialisation de la matrice d'adjacence
}

// Fonction pour initialiser la matrice d'adjacence avec des valeurs infinies
void Dijkstra::initMatrix()
{
    for (uint8_t i = 0; i < SIZE; ++i)
    {
        for (uint8_t j = 0; j < SIZE; ++j)
            matrix[i][j] = INF; // Chaque élément est initialisé à l'infini (infini n est qu'une grande valeur)
    }
    setCosts();
}

// Définit le coût (poids) entre deux nœuds dans la matrice d'adjacence
void Dijkstra::setCost(uint8_t node1, uint8_t node2, const uint8_t cost)
{
    matrix[node1][node2] = cost; // Coût du noeud1 au noeud2
    matrix[node2][node1] = cost; // Coût du noeud2 au noeud1 (car le graphe est non orienté)
}

void Dijkstra::setCosts()
{
    setCost(0, 1, 1);
    setCost(0, 7, 1);
    setCost(1, 2, 1);
    setCost(2, 3, 1);
    setCost(2, 9, 1);
    setCost(3, 10, 1);
    setCost(4, 5, 1);
    setCost(5, 6, 2);
    setCost(5, 12, 2);
    setCost(6, 13, 1);
    setCost(7, 8, 5);
    setCost(8, 9, 1);
    setCost(10, 11, 2);
    setCost(11, 12, 1);
    setCost(12, 13, 1);
    setCost(8, 15, 1);
    setCost(9, 16, 5);
    setCost(14, 15, 2);
    setCost(15, 16, 1);
    setCost(16, 17, 1);
    setCost(17, 18, 5);
    setCost(11, 18, 5);
    setCost(12, 19, 1);
    setCost(13, 20, 1);
    setCost(14, 21, 5);
    setCost(21, 22, 1);
    setCost(22, 23, 1);
    setCost(16, 23, 1);
    setCost(17, 24, 1);
    setCost(24, 25, 2);
    setCost(18, 25, 5);
    setCost(25, 26, 5);
    setCost(19, 26, 1);
    setCost(26, 27, 1);
    setCost(20, 27, 1);
}

// Trouve l'indice dans la matrice correspondant aux coordonnées (x, y)
uint8_t Dijkstra::matchPoint(const Coordinate &point)
{
    for (uint8_t index = 0; index < SIZE; ++index)
    {
        if (points[index].row == point.row && points[index].column == point.column)
        {
            return index; // Retourne l'indice correspondant
        }
    }
    return 100; // Retourne 100 si aucune correspondance n'est trouvée
}

// Retourne les coordonnées du point correspondant à l'indice donné
Coordinate Dijkstra::matchCoordinates(uint8_t position)
{
    return points[position]; // Retourne le point à la position donnée
}

// Calcule le chemin le plus court entre deux points en utilisant l'algorithme de Dijkstra
RoadSchema Dijkstra::generateRoad(const Coordinate &startPoint, const Coordinate &endPoint)
{
    // Convertit les coordonnées en indices de la matrice
    int8_t start = matchPoint(startPoint);
    int8_t end = matchPoint(endPoint);

    // Initialisation pour l'algorithme de Dijkstra
    bool visitedNodes[SIZE] = {false}; // Tableau des nœuds visités
    uint8_t minDistance[SIZE];         // Tableau des distances minimales
    int8_t predecessors[SIZE];         // Tableau des prédécesseurs pour chaque nœud

    for (uint8_t i = 0; i < SIZE; ++i)
    {
        minDistance[i] = INF; // Initialisation des distances à l'infini
        predecessors[i] = -1; // Aucun prédécesseur au début
    }
    minDistance[start] = 0; // La distance du point de départ à lui-même est toujours 0

    // Boucle principale de l'algorithme de Dijkstra
    for (uint8_t count = 0; count < SIZE - 1; ++count)
    {
        int8_t u = -1;
        uint8_t minDist = INF;

        // Trouver le nœud avec la distance minimale non visité
        for (int8_t v = 0; v < SIZE; ++v)
        {
            if (!visitedNodes[v] && (minDistance[v] <= minDist))
            {
                u = v;
                minDist = minDistance[v];
            }
        }

        if (u == -1)
            break; // Si aucun nœud n'est accessible, aucun chemin n'est possible

        visitedNodes[u] = true; // Marquer le nœud sélectionné comme visité

        // Mise à jour des distances et des prédécesseurs pour les voisins du nœud sélectionné
        for (uint8_t v = 0; v < SIZE; ++v)
        {
            if (!visitedNodes[v] && (matrix[u][v] != INF) && ((minDistance[u] + matrix[u][v]) < minDistance[v]))
            {
                predecessors[v] = u;
                minDistance[v] = minDistance[u] + matrix[u][v];
            }
        }
    }

    int8_t road[SIZE]; // Utilisation d'un tableau statique pour stocker le chemin
    int8_t roadIndex = 0;

    // Construction du chemin en remontant à partir du point d'arrivée
    for (int8_t v = end; v != -1; v = predecessors[v])
    {
        road[roadIndex++] = v;
    }
    // Parcours du chemin pour calculer la direction entre chaque point consécutif
    // generer le roadSchema
    RoadSchema roadSchema;
    roadSchema.size = 0;
    for (int8_t i = (roadIndex - 1); i > 0; --i)
    {
        Coordinate startPt = matchCoordinates(road[i]);
        Coordinate endPt = matchCoordinates(road[i - 1]);

        int8_t dx = endPt.row - startPt.row;
        int8_t dy = endPt.column - startPt.column;

        for (uint8_t i = 0; i < 4; i++)
        {
            if (listCornersNav[i].coordinate.row == dx && listCornersNav[i].coordinate.column == dy)
            {
                switch (listCornersNav[i].orientation)
                {
                case Cardinal::EAST:
                    roadSchema.road[roadSchema.size++] = CardinalDirection::EAST;
                    break;
                case Cardinal::SOUTH:
                    roadSchema.road[roadSchema.size++] = CardinalDirection::SOUTH;
                    break;
                case Cardinal::WEST:
                    roadSchema.road[roadSchema.size++] = CardinalDirection::WEST;
                    break;
                case Cardinal::NORTH:
                    roadSchema.road[roadSchema.size++] = CardinalDirection::NORTH;
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }
    return roadSchema;
}

void Dijkstra::destroyPath(const Coordinate &coordinate)
{
    uint8_t point = matchPoint(coordinate);
    for (uint8_t j = 0; j < SIZE; ++j)
        matrix[point][j] = INF; // Chaque élément est initialisé à l'infini
}

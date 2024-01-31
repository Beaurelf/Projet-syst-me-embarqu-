/**
 * @file SearchEngine.cpp
 * @brief Implémentation de la classe SearchEngine.
 *
 * Ce fichier implémente les méthodes de la classe SearchEngine. Il comprend la logique
 * pour la gestion des schémas de navigation et la reconnaissance de points ou nœuds spécifiques
 * lors de la navigation du robot.
 */
#include "SearchEngine.hpp"

SearchEngine::SearchEngine()
{
}

int8_t SearchEngine::isSchemaExist(const char *currentSchema, uint8_t length, const CornerNode cornerList[CORNER_LIST_SIZE])
{

    for (int i = 0; i < CORNER_LIST_SIZE; i++)
    {
        if (length == cornerList[i].schemaLength)
        {
            if (compareCharArrays(currentSchema, cornerList[i].schema))
                return i;
        }
    }
    return -1;
}
CornerNode SearchEngine::identifyNode(const CornerNode cornerList[CORNER_LIST_SIZE], uint8_t indice)
{
    return cornerList[indice];
}

void SearchEngine::buildSchema(char step, TabSchema &currentSchema)
{
    if (currentSchema.size != 0)
    {
        if (currentSchema.tabSchema[currentSchema.size - 1] != step || step == 'A')
        {
            currentSchema.tabSchema[currentSchema.size++] = step;
        }
    }
    else
        currentSchema.tabSchema[currentSchema.size++] = step;
}
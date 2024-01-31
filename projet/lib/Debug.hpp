/**
 * @file Debug.hpp
 * @brief Définit des macros et utilitaires pour le débogage.
 * 
 * Ce fichier d'en-tête définit des macros qui facilitent le débogage conditionnel.
 * Lorsque le drapeau DEBUG est activé, les macros afficheront des informations 
 * de débogage ; sinon, elles seront ignorées.
 * 
 * Note : Les commentaires `code mort` signifient que ce code ne sera pas exécuté.
 * 
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */

#include "Communication.hpp"
#ifdef DEBUG // Le mode de débogage est activé.
  /**
     * @brief Affiche un message de débogage.
     * 
     * Utilise la fonction debug::printf pour afficher les données fournies.
     * 
     * @param data Les données/messages à afficher.
     */
#define DEBUG_PRINT(data) Debug::printf(data)
/**
     * @brief Affichage formaté pour les messages de débogage.
     * 
     * Utilise la fonction Communication::printf pour afficher les données formatées 
     * et ajoute une nouvelle ligne à la fin.
     * 
     * @param data Chaîne de format (similaire à printf).
     * @param ...  Arguments variadiques pour la chaîne de format.
     */
#define DEBUG_PRINTF(data, ...)  {\
    Communication::printf((char*)data, sizeof(data), ##__VA_ARGS__);\
    Communication::sendSerialChar('\n');\
}

#else // Le mode de débogage n'est pas activé : Définir les macros "code mort".
# define DEBUG_PRINT(data) do {} while (0) // code mort
# define DEBUG_PRINTF(data, ...) do {} while (0) // code mort

#endif

/**
 * @namespace Debug
 * @brief Utilitaires de débogage pour afficher des messages et des nombres.
 */
namespace Debug
{
    /**
     * @brief Affiche un message sur la sortie de débogage.
     * 
     * @param msg Le message à afficher.
     */
   void printf(const char *msg);

   /**
     * @brief Affiche un nombre de 16 bits sur la sortie de débogage.
     * 
     * @param number Le nombre à afficher.
     */
   void printf(uint16_t number);
}
/**
 * @file Communication.h
 * @brief Définition de la classe Communication pour la communication série via UART.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "interfaces/utils.hpp"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/**
 * @class Communication
 * @brief Gestionnaire de communication série via UART.
 *
 * La classe Communication est conçue pour faciliter la communication série
 * entre le microcontrôleur et d'autres périphériques ou ordinateurs. Elle fournit
 * des méthodes pour envoyer des chaînes de caractères, des caractères individuels,
 * des nombres entiers et permet également de lire des caractères depuis l'UART.
 *
 * Les fonctionnalités comprennent également une implémentation personnalisée de
 * la fonction printf pour permettre des messages formatés.
 *
 * Toutes les fonctions de cette classe sont statiques pour permettre une
 * utilisation facile sans nécessité de créer une instance de la classe.
 *
 * @note L'utilisation de cette classe nécessite une configuration préalable
 *       et correcte de l'UART en fonction des spécifications matérielles.
 */
class Communication
{
public:
    Communication() = delete;
    Communication(const Communication &communication) = delete;
    /**
     * @brief Initialise le module UART pour la communication.
     */
    static void initializeUART();

    /**
     * @brief Envoie une chaîne de caractères via UART.
     *
     * @param data Pointeur vers le tableau contenant les caractères à envoyer.
     * @param length Longueur du tableau de caractères à envoyer.
     */
    static void sendSerialString(const uint8_t data[], uint8_t length);

    /**
     * @brief Envoie un caractère individuel via UART.
     *
     * @param data Caractère à envoyer.
     */
    static void sendSerialChar(uint8_t data);

    /**
     * @brief Envoie un nombre entier via UART sous forme de chaîne de caractères.
     *
     * @param number Nombre entier à envoyer.
     */
    static void sendSerialInteger(int16_t number);

    /**
     * @brief Lit un caractère depuis UART.
     *
     * @return Le caractère lu depuis UART.
     */
    static char readSerialChar();

    /**
     * @brief Envoie un message formaté via UART, similaire à la fonction printf standard.
     *
     * @param format Chaîne de formatage, similaire à celle utilisée avec printf.
     * @param ... Arguments variables correspondant aux spécificateurs de format dans la chaîne de formatage.
     */
    static void printf(const char format[], ...);

private:
    // Délai après chaque envoi pour garantir une transmission sans encombre.
    static const uint8_t DELAY_SEND = 100;
};

#endif

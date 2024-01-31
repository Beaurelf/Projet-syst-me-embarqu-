/**
 * @file Communication.cpp
 * @brief Implémentation des fonctions pour la communication UART avec le microcontrôleur ATmega324PA.
 *
 * Ce fichier contient la définition des fonctions de la classe Communication qui permettent
 * la communication série (UART) entre le microcontrôleur ATmega324PA et d'autres dispositifs.
 * Les fonctions incluent l'initialisation de la communication UART, l'envoi et la réception
 * de données sur le port série, ainsi qu'une fonction printf pour faciliter la communication
 * formatée.
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

void Communication::initializeUART()
{
    // Configuration du débit de communication
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // Activation de la transmission et réception
    setRegisterBits(&UCSR0B, RXEN0);
    setRegisterBits(&UCSR0B, TXEN0);
    // Configuration des bits de données et de la parité (8 bits de données, pas de parité)
    setRegisterBits(&UCSR0C, UCSZ00);
    setRegisterBits(&UCSR0C, UCSZ01);
}

void Communication::sendSerialChar(uint8_t data)
{
    // Attend que la file de transmission soit vide avant d'envoyer les données
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

void Communication::sendSerialString(const uint8_t data[], uint8_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        sendSerialChar(data[i]);
    }
}

void Communication::sendSerialInteger(int16_t number)
{
    uint8_t buffer[255]; // Un tampon pour stocker la chaîne formatée
    sprintf((char *)buffer, "%d", number);
    sendSerialString(buffer, strlen((char *)buffer));
}

char Communication::readSerialChar()
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    // retouner la donnée lue
    return UDR0;
}

void Communication::printf(const char format[], ...)
{
    va_list args;
    va_start(args, format);
    uint8_t buffer[255]; // Un tampon pour stocker la chaîne formatée

    vsnprintf((char *)buffer, sizeof(buffer), format, args);
    va_end(args);

    sendSerialString(buffer, strlen((char *)buffer));
}

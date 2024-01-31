/**
 * @file NoteFrequency.h
 * @brief Définition de l'énumération Note et du tableau des fréquences associées.
 *
 * Ce fichier contient l'énumération Note pour représenter des notes musicales spécifiques avec
 * leurs valeurs numériques correspondantes. Il inclut également un tableau de fréquences pour
 * chaque note, permettant une représentation précise des fréquences sonores des notes musicales.
 */

#ifndef NOTE_FREQUENCY_H
#define NOTE_FREQUENCY_H

/**
 * @enum Note
 * @brief Énumération des notes musicales avec leurs valeurs numériques correspondantes.
 *
 * Cette énumération associe des valeurs numériques à des notes musicales spécifiques, facilitant
 * leur utilisation dans des contextes nécessitant une représentation numérique des notes, comme
 * la synthèse sonore ou le traitement de signaux musicaux.
 */
enum class Note
{
    SILENCE = 0,
    A2 = 45,
    A2b = 46,
    B2 = 47,
    C3 = 48,
    C3b = 49,
    D3 = 50,
    D3b = 51,
    E3 = 52,
    F3 = 53,
    F3b = 54,
    G3 = 55,
    G3b = 56,
    A3 = 57,
    A3b = 58,
    B3 = 59,
    C4 = 60,
    C4b = 61,
    D4 = 62,
    D4b = 63,
    E4 = 64,
    F4 = 65,
    F4b = 66,
    G4 = 67,
    G4b = 68,
    A4 = 69,
    A4b = 70,
    B4 = 71,
    C5 = 72,
    C5b = 73,
    D5 = 74,
    D5b = 75,
    E5 = 76,
    F5 = 77,
    F5b = 78,
    G5 = 79,
    G5b = 80,
    A5 = 81
};

/**
 * @brief Tableau de fréquences correspondant à chaque note.
 *
 * Ce tableau contient les fréquences en Hertz pour chaque note musicale définie dans l'énumération
 * Note. Il est utilisé pour obtenir la fréquence exacte d'une note musicale pour la synthèse sonore
 * ou d'autres applications musicales.
 */
constexpr double noteFrequencies[] = {
    110.0,  // Do
    116.54, // Do#
    123.47, // Ré
    130.81, // Ré#
    138.59, // Mi
    146.83, // Fa
    155.56, // Fa#
    164.81, // Sol
    174.61, // Sol#
    185.0,  // La
    196.0,  // La#
    207.65, // Si
    220.0,  // Do
    233.08, // Do#
    246.94, // Ré
    261.63, // Ré#
    277.18, // Mi
    293.66, // Fa
    311.13, // Fa#
    329.63, // Sol
    349.23, // Sol#
    369.99, // La
    392.0,  // La#
    415.3,  // Si
    440.0,  // Do
    466.16, // Do#
    493.88, // Ré
    523.25, // Ré#
    554.37, // Mi
    587.33, // Fa
    622.25, // Fa#
    659.26, // Sol
    698.46, // Sol#
    739.99, // La
    783.99, // La#
    830.61, // Si
    880.0   // Do
};

#endif
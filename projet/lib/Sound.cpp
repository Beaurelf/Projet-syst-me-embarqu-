/**
 * @file Sound.cpp
 * @brief Implémentation de la classe Sound pour la génération de sons.
 *
 * Ce fichier contient les définitions des méthodes de la classe Sound. La classe utilise
 * un objet Timer pour générer des fréquences correspondant à différentes notes musicales.
 * La sortie est réalisée sur le pin PD7 du microcontrôleur.
 */

#include "Sound.hpp"

Sound::Sound() : timer_(TimerMode::CTC, Prescaler::PRESCALER_256), isSongPlay_(false)
{
    setRegisterBits(&DDRD, PD6);
    clearRegisterBits(&PORTD, PD6);
    setRegisterBits(&DDRD, PD7);
}

void Sound::play(uint8_t noteNumber)
{
    if ((noteNumber >= 45) && (noteNumber <= 81))
    {
        if (!isSongPlay_)
        {
            // generer le PWM sur le port OC2A (PD7)
            setRegisterBits(&TCCR2A, COM2A0);
            // setRegisterBits(&PORTD, PD7);
            isSongPlay_ = true;
        }
        timer_.setOCRnXCtcToGenerateSignal(noteFrequencies[noteNumber - 45], &OCR2A);
    }
}

void Sound::stop()
{
    isSongPlay_ = false;
    clearRegisterBits(&TCCR2A, COM2A0);
    clearRegisterBits(&PORTD, PD7);
}

void Sound::playPiratesDesCaraibesSong()
{
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // // Mi croche
    play(MI);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // // Fa noire
    play(FA);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // // Fa noire
    play(FA);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // // Fa croche
    play(FA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // // Sol croche
    play(SOL);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // // MI noire
    play(MI);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // // MI noire
    play(MI);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // // Do croche
    play(DO);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // // Do croche
    play(DO);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // // Silence croche
    stop();
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // La bas croche
    stop();
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Do croche
    play(DO);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Mi croche
    play(MI);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Fa noire
    play(FA);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Fa  noire
    play(FA);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Fa croche
    play(FA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Sol croche
    play(SOL);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Mi noire
    play(MI);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Mi noire
    play(MI);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Do croche
    play(DO);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Silence noire
    stop();
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // La bas croche
    stop();
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Do croche
    play(DO);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Fa croche
    play(FA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Sol noire
    play(SOL);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Sol noire
    play(SOL);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Sol croche
    play(SOL);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // La haut croche
    play(HIGH_LA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Si haut noire
    play(SI_BEMOL);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Si haut noire
    play(SI_BEMOL);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // La haut croche
    play(HIGH_LA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Sol croche
    play(SOL);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // La haut croche
    play(HIGH_LA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Silence croche
    stop();
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Mi croche
    play(MI);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Fa noire
    play(FA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Fa noire
    play(FA);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Sol noire
    play(SOL);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // La haut croche
    play(HIGH_LA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re noire
    play(RE);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Silence croche
    stop();
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Fa croche
    play(FA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Mi noire
    play(MI);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Mi noire
    play(MI);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Fa croche
    play(FA);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Re croche
    play(RE);
    _delay_ms(CROCHE);
    stop();
    _delay_ms(CROCHE);
    // Mi noire
    play(MI);
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    // Silence noire
    stop();
    _delay_ms(NOIR);
    stop();
    _delay_ms(NOIR);
    stop();
}
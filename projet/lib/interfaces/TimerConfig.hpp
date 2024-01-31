/**
 * @file TimerConfig.hpp
 * @brief Configuration de la classe TimerConfig pour les minuteries TIMER de l'ATmega324PA.
 *
 * Ce fichier fournit une classe de configuration de template pour les minuteries disponibles
 * sur l'ATmega324PA. Il permet une manipulation générique des registres et des configurations
 * pour différentes minuteries (TIMER0, TIMER1, TIMER2, etc.).
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#ifndef TIMERMODE_H
#define TIMERMODE_H

#include "interfaces/utils.hpp"
#include "interfaces/emun/TimerEnum.hpp"

/**
 * @class TimerConfig
 * @brief Classe de configuration de template pour les minuteries TIMER de l'ATmega324PA.
 *
 * Cette classe fournit une série de méthodes statiques pour la configuration de minuteries
 * sur l'ATmega324PA. Elle utilise un mécanisme de template pour la configuration dynamique
 * en fonction du numéro de la minuterie.
 */
template <uint8_t TIMER_NUM>
class TimerConfig
{
    template <uint8_t TIMER_NUMBER>
    friend class Timer;

public:
    TimerConfig() = delete;
    TimerConfig(const TimerConfig &timerConfig) = delete;

private:
    /**
     * @brief Efface le mode de la minuterie sélectionnée.
     */
    static void clearMode()
    {
        if (TIMER_NUM == 1)
        {
            clearRegisterBits(&TCCR1A, WGM10);
            clearRegisterBits(&TCCR1A, WGM11);
            clearRegisterBits(&TCCR1B, WGM12);
            clearRegisterBits(&TCCR1B, WGM13);
            clearRegisterBits(&TCCR1A, COM1A1);
            clearRegisterBits(&TCCR1A, COM1B1);
        }
        else if (TIMER_NUM == 0)
        {
            clearRegisterBits(&TCCR0A, WGM00);
            clearRegisterBits(&TCCR0A, WGM01);
            clearRegisterBits(&TCCR0B, WGM02);
            clearRegisterBits(&TCCR0A, COM0A1);
            clearRegisterBits(&TCCR0A, COM0B1);
        }
        else if (TIMER_NUM == 2)
        {
            clearRegisterBits(&TCCR2A, WGM20);
            clearRegisterBits(&TCCR2A, WGM21);
            clearRegisterBits(&TCCR2B, WGM22);
            clearRegisterBits(&TCCR2A, COM2A1);
            clearRegisterBits(&TCCR2A, COM2B1);
        }
    }

    /**
     * @brief Efface le prescaler de la minuterie sélectionnée.
     */
    static void clearPrescaler()
    {
        if (TIMER_NUM == 1)
        {
            clearRegisterBits(&TCCR1B, CS10);
            clearRegisterBits(&TCCR1B, CS11);
            clearRegisterBits(&TCCR1B, CS12);
        }
        else if (TIMER_NUM == 0)
        {
            clearRegisterBits(&TCCR0B, CS00);
            clearRegisterBits(&TCCR0B, CS01);
            clearRegisterBits(&TCCR0B, CS02);
        }
        else if (TIMER_NUM == 2)
        {
            clearRegisterBits(&TCCR2B, CS20);
            clearRegisterBits(&TCCR2B, CS21);
            clearRegisterBits(&TCCR2B, CS22);
        }
    }

    /**
     * @brief Configure le mode de la minuterie sélectionnée.
     *
     * @param timerMode Le mode de minuterie à définir.
     */
    static void configureMode(const TimerMode &timerMode)
    {
        clearMode();
        switch (timerMode)
        {
        case TimerMode::CTC:
            if (TIMER_NUM == 1)
                setRegisterBits(&TCCR1B, WGM12);
            else if (TIMER_NUM == 0)
                setRegisterBits(&TCCR0A, WGM01);
            else if (TIMER_NUM == 2)
                setRegisterBits(&TCCR2A, WGM21);
            break;
        case TimerMode::PWM:
            if (TIMER_NUM == 1)
            {
                TCCR1C |= 0;
                setRegisterBits(&TCCR1A, WGM10);
                setRegisterBits(&TCCR1A, COM1A1);
                setRegisterBits(&TCCR1A, COM1B1);
            }
            else if (TIMER_NUM == 0)
            {
                setRegisterBits(&TCCR0A, WGM00);
                setRegisterBits(&TCCR0A, COM0A1);
                setRegisterBits(&TCCR0A, COM0B1);
            }
            else if (TIMER_NUM == 2)
            {
                setRegisterBits(&TCCR2A, WGM20);
                setRegisterBits(&TCCR2A, COM2A1);
                setRegisterBits(&TCCR2A, COM2B1);
            }
            break;
        default:
            break;
        }
    }

    /**
     * @brief Configure le prescaler de la minuterie sélectionnée.
     *
     * @param prescaler Le prescaler à définir.
     */
    static void configurePrescaler(const Prescaler &prescaler)
    {
        clearPrescaler();
        switch (prescaler)
        {
        case Prescaler::PRESCALER_8:
            if (TIMER_NUM == 1)
                setRegisterBits(&TCCR1B, CS10);
            else if (TIMER_NUM == 0)
                setRegisterBits(&TCCR0B, CS01);
            else if (TIMER_NUM == 2)
                setRegisterBits(&TCCR2B, CS21);
            break;
        case Prescaler::PRESCALER_64:
            if (TIMER_NUM == 1)
            {
                setRegisterBits(&TCCR1B, CS11);
                setRegisterBits(&TCCR1B, CS10);
            }
            else if (TIMER_NUM == 0)
            {
                setRegisterBits(&TCCR0B, CS01);
                setRegisterBits(&TCCR0B, CS00);
            }
            else if (TIMER_NUM == 2)
            {
                setRegisterBits(&TCCR2B, CS22);
            }
            break;
        case Prescaler::PRESCALER_256:
            if (TIMER_NUM == 1)
                setRegisterBits(&TCCR1B, CS12);
            else if (TIMER_NUM == 0)
                setRegisterBits(&TCCR0B, CS02);
            else if (TIMER_NUM == 2)
            {
                setRegisterBits(&TCCR2B, CS22);
                setRegisterBits(&TCCR2B, CS21);
            }
            break;
        case Prescaler::PRESCALER_1024:
            if (TIMER_NUM == 1)
            {
                setRegisterBits(&TCCR1B, CS12);
                setRegisterBits(&TCCR1B, CS10);
            }
            else if (TIMER_NUM == 0)
            {
                setRegisterBits(&TCCR0B, CS02);
                setRegisterBits(&TCCR0B, CS00);
            }
            else if (TIMER_NUM == 2)
            {
                setRegisterBits(&TCCR2B, CS22);
                setRegisterBits(&TCCR2B, CS21);
                setRegisterBits(&TCCR2B, CS20);
            }
            break;
        default:
            break;
        }
    };
};

#endif

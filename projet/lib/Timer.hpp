/**
 * @file Timer.hpp
 * @brief Définit la classe Timer pour la gestion des timers matériels.
 *
 * Ce fichier fournit une classe modélisée pour contrôler les fonctionnalités des timers matériels.
 *
 * @details rajouter la description materiel pour le timer avec les broches pour le pwm !!!!!!!!!!!
 *
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#ifndef TIMER_H
#define TIMER_H
#include "interfaces/TimerConfig.hpp"

constexpr uint64_t FREQUENCY = 8000000UL;

/**
 * @brief Classe Timer templatisée pour fournir des fonctionnalités pour différents timers.
 *
 * Cette classe offre des méthodes pour configurer et contrôler les timers matériels.
 * Le comportement du timer (mode PWM ou CTC) peut être défini dynamiquement. De plus,
 * des méthodes sont fournies pour définir le registre OCR pour les timers 8 bits et 16 bits.
 *
 * @tparam TIMER_NUM Identifiant numérique du timer matériel.
 */
template <uint8_t TIMER_NUM>
class Timer
{

public:
    /**
     * @brief Constructeur pour initialiser le timer avec le mode et le prescaler donnés.
     *
     * @param timerMode Mode du timer (PWM, CTC, etc.).
     * @param prescaler Valeur du prescaler.
     */
    Timer(const TimerMode &timerMode = TimerMode::PWM, const Prescaler &prescaler = Prescaler::PRESCALER_256);

    /**
     * @brief Change le mode du timer.
     *
     * @param timerMode Nouveau mode du timer.
     */
    void changeMode(const TimerMode &timerMode);

    /**
     * @brief Change la valeur du prescaler du timer.
     *
     * @param prescaler Nouvelle valeur du prescaler.
     */
    void changePrescaler(const Prescaler &prescaler);

    /**
     * @brief Configure le registre OCR pour un timer 16 bits.
     *
     * @param value Valeur à mettre dans le registre.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer.
     */
    void setOCRnXRegister(double value, volatile uint16_t *OCRnXRegister);

    /**
     * @brief Configure le registre OCR pour un timer 8 bits.
     *
     * @param value Valeur à mettre dans le registre.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer.
     */
    void setOCRnXRegister(double value, volatile uint8_t *OCRnXRegister);

    /**
     * @brief Configure le registre OCR pour un timer 8 bits (principalement utilisées pour generer un signal PWM avec un dutyCycle de 50%
     * avec une certaine frequence).
     *
     * @param frequence frequence du signal à generer.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer.
     */
    void setOCRnXCtcToGenerateSignal(double frequency, volatile uint8_t *OCRnXRegister);

    /**
     * @brief Configure le registre OCR pour un timer 16 bits (principalement utilisées pour generer un signal PWM avec un dutyCycle de 50%
     * avec une certaine frequence).
     *
     * @param frequence frequence du signal à generer.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer
     */
    void setOCRnXCtcToGenerateSignal(double frequency, volatile uint16_t *OCRnXRegister);

    /**
     * @brief Active les interruptions du timer.
     */
    void enable();

    /**
     * @brief Désactive les interruptions du timer.
     */
    void disable();

private:
    static const uint8_t MAX_PWM_COUNT_VALUE = 255; // Valeur maximale de comptage pour le mode PWM.
    TimerMode mode_;                                // Mode actuel du timer.
    Prescaler prescaler_;                           // Valeur actuelle du prescaler.

    // Méthodes privées pour configurer le registre OCR en fonction du mode du timer.

    /**
     * @brief Configure le registre OCR pour un timer 16 bits en mode PWM.
     *
     * @param dutyCycle Valeur de rapport cyclique entre 0.0 et 1.0.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer.
     */
    void setOCRnXPwmModeRegister(double dutyCycle, volatile uint16_t *OCRnXRegister);

    /**
     * @brief Configure le registre OCR pour un timer 16 bits en mode CTC.
     *
     * @param duration_s Durée en secondes pour laquelle le timer doit déclencher une interruption.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer.
     */
    void setOCRnXCtcModeRegister(double duration_s, volatile uint16_t *OCRnXRegister);

    /**
     * @brief Configure le registre OCR pour un timer 8 bits en mode PWM.
     *
     * @param dutyCycle Valeur de rapport cyclique entre 0.0 et 1.0.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer.
     */
    void setOCRnXPwmModeRegister(double dutyCycle, volatile uint8_t *OCRnXRegister);

    /**
     * @brief Configure le registre OCR pour un timer 8 bits en mode CTC.
     *
     * @param durationS Durée en secondes pour laquelle le timer doit déclencher une interruption.
     * @param OCRnXRegister Pointeur vers le registre OCR à configurer.
     */
    void setOCRnXCtcModeRegister(double durationS, volatile uint8_t *OCRnXRegister);
};

template <uint8_t TIMER_NUM>
Timer<TIMER_NUM>::Timer(const TimerMode &timerMode, const Prescaler &prescaler) : mode_(timerMode), prescaler_(prescaler)
{
    TimerConfig<TIMER_NUM>::configureMode(timerMode);
    TimerConfig<TIMER_NUM>::configurePrescaler(prescaler);
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::changeMode(const TimerMode &timerMode)
{
    mode_ = timerMode;
    TimerConfig<TIMER_NUM>::configureMode(timerMode);
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::changePrescaler(const Prescaler &prescaler)
{
    prescaler_ = prescaler;
    TimerConfig<TIMER_NUM>::configurePrescaler(prescaler);
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXRegister(double value, volatile uint16_t *OCRnXRegister)
{
    if (mode_ == TimerMode::PWM)
    {
        setOCRnXPwmModeRegister(value, OCRnXRegister);
    }
    else if (mode_ == TimerMode::CTC)
    {
        setOCRnXCtcModeRegister(value, OCRnXRegister);
    }
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXRegister(double value, volatile uint8_t *OCRnXRegister)
{
    if (mode_ == TimerMode::PWM)
    {
        setOCRnXPwmModeRegister(value, OCRnXRegister);
    }
    else if (mode_ == TimerMode::CTC)
    {
        setOCRnXCtcModeRegister(value, OCRnXRegister);
    }
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXCtcToGenerateSignal(double frequency, volatile uint8_t *OCRnXRegister)
{
    uint8_t ocrValue = static_cast<uint8_t>((FREQUENCY / (2 * static_cast<uint16_t>(prescaler_) * frequency)) - 1);
    *OCRnXRegister = ocrValue;
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXCtcToGenerateSignal(double frequency, volatile uint16_t *OCRnXRegister)
{
    uint8_t ocrValue = static_cast<uint8_t>((FREQUENCY / (2 * static_cast<uint16_t>(prescaler_) * frequency)) - 1);
    *OCRnXRegister = ocrValue;
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::enable()
{
    if (mode_ == TimerMode::CTC)
    {
        if (TIMER_NUM == 0)
        {
            TCNT0 = 0;
            setRegisterBits(&TIMSK0, OCIE0A);
        }
        else if (TIMER_NUM == 1)
        {
            TCNT1 = 0;
            setRegisterBits(&TIMSK1, OCIE1A);
        }
        else if (TIMER_NUM == 2)
        {
            TCNT2 = 0;
            setRegisterBits(&TIMSK2, OCIE2A);
        }
    }
    else if (mode_ == TimerMode::NORMAL)
    {
        if (TIMER_NUM == 0)
        {
            TCNT0 = 0;
            setRegisterBits(&TIMSK0, TOIE0);
        }
        else if (TIMER_NUM == 1)
        {
            TCNT1 = 0;
            setRegisterBits(&TIMSK1, TOIE1);
        }
        else if (TIMER_NUM == 2)
        {
            TCNT2 = 0;
            setRegisterBits(&TIMSK2, TOIE2);
        }
    }
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::disable()
{
    if (mode_ == TimerMode::CTC)
    {
        if (TIMER_NUM == 0)
            clearRegisterBits(&TIMSK0, OCIE0A);
        else if (TIMER_NUM == 1)
            clearRegisterBits(&TIMSK1, OCIE1A);
        else if (TIMER_NUM == 2)
            clearRegisterBits(&TIMSK2, OCIE2A);
    }
    else if (mode_ == TimerMode::NORMAL)
    {
        if (TIMER_NUM == 0)
            clearRegisterBits(&TIMSK0, TOIE0);
        else if (TIMER_NUM == 1)
            clearRegisterBits(&TIMSK1, TOIE1);
        else if (TIMER_NUM == 2)
            clearRegisterBits(&TIMSK2, TOIE2);
    }
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXPwmModeRegister(double dutyCycle, volatile uint16_t *OCRnXRegister)
{
    *OCRnXRegister = static_cast<uint16_t>(dutyCycle * MAX_PWM_COUNT_VALUE);
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXCtcModeRegister(double duration_s, volatile uint16_t *OCRnXRegister)
{
    *OCRnXRegister = static_cast<uint16_t>(duration_s * FREQUENCY / static_cast<uint16_t>(prescaler_));
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXPwmModeRegister(double dutyCycle, volatile uint8_t *OCRnXRegister)
{
    *OCRnXRegister = static_cast<uint8_t>(dutyCycle * MAX_PWM_COUNT_VALUE);
}

template <uint8_t TIMER_NUM>
void Timer<TIMER_NUM>::setOCRnXCtcModeRegister(double duration_s, volatile uint8_t *OCRnXRegister)
{
    *OCRnXRegister = static_cast<uint8_t>(duration_s * FREQUENCY / static_cast<uint16_t>(prescaler_));
}

#endif
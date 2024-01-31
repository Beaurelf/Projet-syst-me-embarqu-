/**
 * @file Wheel.hpp
 * @brief Définition et interface de la classe Roue.
 *
 * La classe Roue représente une roue individuelle d'un robot. Elle fournit des fonctionnalités
 * pour contrôler une roue, y compris sa vitesse et sa direction. Cette classe utilise un objet Timer
 * pour moduler la vitesse de la roue à l'aide de la modulation de largeur d'impulsion (PWM).
 *
 * Les principales fonctionnalités comprennent la capacité de faire avancer ou reculer la roue à
 * une vitesse spécifiée, ainsi que de l'arrêter complètement.
 *
 * @details rajouter la description materiel pour les roues !!!!!!!!!!!
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#ifndef WHEEL_H
#define WHEEL_H
#include "Timer.hpp"

/**
 * @class Wheel
 * @brief Classe pour la gestion d'une roue motorisée sur un microcontrôleur AVR.
 *
 * Cette classe permet de démarrer, arrêter, et changer la direction de la roue
 * motorisée. Elle utilise un Timer pour la modulation de largeur d'impulsion (PWM)
 * afin de contrôler la vitesse de la roue.
 */
class Wheel
{
private:
    Timer<0> *timer_;               // Pointeur vers le Timer 1 utilisé pour le PWM.
    uint8_t wheelDirectionPort_;    // Port pour contrôler la direction de la roue.
    volatile uint8_t *ocrRegister_; // Registre OCR pour la configuration PWM.

public:
    /**
     * @brief Constructeur de la classe Roue.
     *
     * Initialise une nouvelle instance de la classe Roue avec le Timer, le port d'activation,
     * et le registre OCR fournis.
     *
     * @param timer Pointeur vers le Timer 1 à utiliser pour le PWM.
     * @param directionPort Port la direction daans laquelle la roue tourne (Avant ou arrière).
     * @param ocrRegister Pointeur vers le registre OCR pour la configuration PWM.
     */
    Wheel(Timer<0> *timer, uint8_t directionPort, volatile uint8_t *ocrRegister);

    ~Wheel() = default;

    /**
     * @brief Déplace la roue à une vitesse spécifiée.
     *
     * @param speed Vitesse à laquelle la roue doit se déplacer.
     */
    void move(const double speed);

    /**
     * @brief Fait tourner la roue vers l'avant à une vitesse spécifiée.
     *
     * @param speed Vitesse à laquelle la roue doit se déplacer vers l'avant.
     */
    void turnWheelForward(const double speed);

    /**
     * @brief Fait tourner la roue vers l'arrière à une vitesse spécifiée.
     *
     * @param speed Vitesse à laquelle la roue doit se déplacer vers l'arrière.
     */
    void turnWheelBackward(const double speed);

    /**
     * @brief Arrête la roue.
     */
    void stop();
};

#endif

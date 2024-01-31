/**
 * @file Navigation.cpp
 * @brief Implémentation de la classe Navigation.
 *
 * Cette classe fournit les méthodes nécessaires pour contrôler les mouvements du robot,
 * en se basant sur les commandes envoyées aux deux roues via les objets de type `Roue`.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 2.0
 * @date [Date]
 **/
#include "Navigation.hpp"
#include "Communication.hpp"

Navigation::Navigation() : leftWheel_(&timer_, LEFT_WHEEL_DIRECTION, &OCR0B), rightWheel_(&timer_, RIGHT_WHEEL_DIRECTION, &OCR0A)
{
    initIO();
};

void Navigation::initIO()
{
    setRegisterBits(&DDRB, LEFT_WHEEL_DIRECTION);
    setRegisterBits(&DDRB, RIGHT_WHEEL_DIRECTION);
    setRegisterBits(&DDRB, LEFT_WHEEL_ENABLE);
    setRegisterBits(&DDRB, RIGHT_WHEEL_ENABLE);
};

void Navigation::moveForward(const double speedLeft, const double speedRight)
{
    leftWheel_.turnWheelForward(speedLeft);
    rightWheel_.turnWheelForward(speedRight);
};

void Navigation::moveBackward(const double speedLeft, const double speedRight)
{
    leftWheel_.turnWheelBackward(speedLeft);
    rightWheel_.turnWheelBackward(speedRight);
};

void Navigation::turnLeft(const double speedLeft, const double speedRight)
{
    leftWheel_.turnWheelBackward(speedLeft);
    rightWheel_.turnWheelForward(speedRight);
};

void Navigation::turnRight(const double speedLeft, const double speedRight)
{
    leftWheel_.turnWheelForward(speedLeft);
    rightWheel_.turnWheelBackward(speedRight);
};

void Navigation::turn90Degre(const Direction &direction)
{

    if (direction == Direction::LEFT)
    {
        turnLeft(MAX_SPEED, MAX_SPEED);
        _delay_ms(DELAY_IMPULSION);
        turnLeft(SPEED_TO_TURN_BACKWARD + PERCENT_TO_ADJUST_TURN, SPEED_TO_TURN_FORWARD);
    }
    else if (direction == Direction::RIGHT)
    {
        // petite impulsion au roue pour bien demarrer
        turnRight(MAX_SPEED, MAX_SPEED);
        _delay_ms(DELAY_IMPULSION);
        turnRight(SPEED_TO_TURN_FORWARD + PERCENT_TO_ADJUST, SPEED_TO_TURN_BACKWARD + PERCENT_TO_ADJUST_TURN);
    }
    _delay_ms(DELAY_TURN_90_DEGRE);
    stop();
    //_delay_ms(DELAY_STOP_AFTER_TURN);
}
void Navigation::turn180Degre(const Direction &direction)
{
    if (direction == Direction::LEFT)
    {
        turnLeft(MAX_SPEED, MAX_SPEED);
        _delay_ms(DELAY_IMPULSION);
        turnLeft(SPEED_TO_TURN_BACKWARD + PERCENT_TO_ADJUST_TURN, SPEED_TO_TURN_FORWARD);
    }
    else if (direction == Direction::RIGHT)
    {
        turnRight(MAX_SPEED, MAX_SPEED);
        _delay_ms(DELAY_IMPULSION);
        turnRight(SPEED_TO_TURN_FORWARD + +PERCENT_TO_ADJUST, SPEED_TO_TURN_BACKWARD + PERCENT_TO_ADJUST_TURN);
    }
    _delay_ms(DELAY_TURN_180_DEGRE);
    stop();
}

void Navigation::turn360Degre()
{
    turn180Degre(Direction::LEFT);
    turn180Degre(Direction::LEFT);
}

void Navigation::moveWheelToDirection(const Direction &direction, const double speedLeft, const double speedRight)
{
    switch (direction)
    {
    case Direction::FORWARD:
        moveForward(speedLeft + PERCENT_TO_ADJUST, speedRight);
        break;
    case Direction::BACKWARD:
        moveBackward(speedLeft + PERCENT_TO_ADJUST, speedRight);
        break;
    case Direction::LEFT:
        turnLeft(speedLeft + PERCENT_TO_ADJUST, speedRight);
        break;
    case Direction::RIGHT:
        turnRight(speedLeft + PERCENT_TO_ADJUST, speedRight);
        break;
    }
};

void Navigation::stop()
{
    leftWheel_.stop();
    rightWheel_.stop();
};

Navigation::~Navigation() = default;
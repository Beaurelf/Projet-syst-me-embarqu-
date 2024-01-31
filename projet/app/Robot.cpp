/**
 * @file Robot.cpp
 * @brief Implémentation des fonctionnalités de la classe Robot pour la gestion des actions du robot.
 *
 * Ce fichier contient les définitions des méthodes de la classe Robot. La classe Robot agit
 * comme une façade pour les divers composants du robot, tels que les LED, les sons et la
 * navigation, en offrant une interface de haut niveau pour exécuter des actions telles que
 * attendre, jouer un son ou se déplacer dans différentes directions.
 *
 * @author Aymane Bourchirch
 * @author Beaurel Fohom
 * @author Christ Bouka
 * @author Nelson Lekem
 *
 * @version 1.0
 * @date [Date]
 */
#include "Robot.hpp"

Robot *gRobot;
volatile uint8_t gNCyclesToBlinkedLedPassed = 0;
volatile bool gIsLedGreenBlinked = false;

ISR(TIMER1_COMPA_vect)
{
    // logique clignotement des led
    if (gRobot->getMode() == RobotMode::IDENTIFY_CORNER)
    {
        gNCyclesToBlinkedLedPassed++;
        if (gNCyclesToBlinkedLedPassed == N_CYCLES_TO_BLINK_LED)
        {
            if (gIsLedGreenBlinked)
                gRobot->turnOffLed();
            else
                gRobot->setLedColorOn(LedColor::GREEN);
            gNCyclesToBlinkedLedPassed = 0;
            gIsLedGreenBlinked = !gIsLedGreenBlinked;
        }
    }

    if (gRobot->getChrono().isTimerExpired())
    {
        gRobot->setIsChronoRunning(false);
        if (gRobot->getMode() == RobotMode::IDENTIFY_CORNER)
            gRobot->buildSchema('A');
        if (gRobot->isGoForwardBeforeTakeDecision())
            gRobot->setIsGoForwardBeforeTakeDecision(false);
    }
}

Robot::Robot() : led_(&PORTB, &DDRB, PB1, PB0), lcm_(&DDRC, &PORTC), buttonMotherBoard_(&DDRD, &PIND, PD2, ButtonMode::PULL_DOWN),
                 buttonValidation_(&DDRD, &PIND, PD3, ButtonMode::PULL_UP), buttonSelection_(&DDRB, &PINB, PB2, ButtonMode::PULL_UP),
                 linePosition_(LinePosition::UNDEFINED), isChronoRunning_(false), isFirstChronoRunning_(true), isInitialCornerFound_(false),
                 isReturnToIntialaCorner_(false), isObstacleDetected_(false), isGoForwardBeforeTakeDecision_(false), mode_(RobotMode::UNDEFINED),
                 initialDirection_(CardinalDirection::SOUTH), isRoadEnd_(false)
{
    gRobot = this;
    currentSchema_ = {};
    initialPoint_ = {1, 1};
    currentPoint_ = {1, 1};
    finalPoint_ = {1, 1};
}

void Robot::wait(uint16_t delayMs)
{
    while (delayMs > 0)
    {
        _delay_ms(MILLI_SECOND);
        delayMs--;
    }
}

void Robot::setIsChronoRunning(bool value)
{
    isChronoRunning_ = value;
}

Chrono &Robot::getChrono()
{
    return chrono_;
}

bool Robot::isGoForwardBeforeTakeDecision()
{
    return isGoForwardBeforeTakeDecision_;
}

void Robot::setIsGoForwardBeforeTakeDecision(bool value)
{
    isGoForwardBeforeTakeDecision_ = value;
}

CornerNode &Robot::getCorner()
{
    return initialCorner_;
}

bool Robot::isButtonMotherBoardPressed()
{
    return buttonMotherBoard_.isPressed();
}

bool Robot::isButtonValidationPressed()
{
    return buttonValidation_.isPressed();
}

bool Robot::isButtonSelectionPressed()
{
    return buttonSelection_.isPressed();
}

void Robot::blinkLed(const LedColor &color, uint32_t duration)
{
    led_.blinkLed(color, duration);
}

void Robot::setLedColorOn(const LedColor &color)
{
    led_.turnOnLed(color);
}

void Robot::turnOffLed()
{
    led_.turnOffLed();
}

void Robot::blinkLed(const LedColor &ledColor, double frequency)
{
    led_.blinkLed(ledColor, frequency);
}

void Robot::playSong(uint8_t noteNumber)
{
    sound_.play(noteNumber);
}

void Robot::playPiratesDesCaraibesSong()
{
    sound_.playPiratesDesCaraibesSong();
}

void Robot::stopSong()
{
    sound_.stop();
}

void Robot::moveTo(const Direction &direction, const double speedLeft, const double speedRight)
{
    nav_.moveWheelToDirection(direction, speedLeft, speedRight);
}

void Robot::turn90Degre(const Direction &direction)
{
    stopEngine();
    _delay_ms(DELAY_STOP_BEFORE_TURN_MS);
    nav_.turn90Degre(direction);
    findLine(direction);
}

void Robot::turn180Degre(const Direction &direction)
{
    stopEngine();
    _delay_ms(DELAY_STOP_BEFORE_TURN_MS);
    nav_.turn180Degre(direction);
    findLine(direction);
}

void Robot::turn360Degre()
{
    stopEngine();
    _delay_ms(DELAY_STOP_BEFORE_TURN_MS);
    nav_.turn360Degre();
    findLine(Direction::LEFT);
}

void Robot::stopEngine()
{
    nav_.stop();
}

void Robot::stopRobot()
{
    chrono_.stop();
    stopEngine();
    stopSong();
    turnOffLed();
}

void Robot::followLine()
{
    linePosition_ = lineSensor_.determineLinePosition();
    switch (linePosition_)
    {
    case LinePosition::MOST_LEFT:
        moveTo(Direction::FORWARD, SPEED_TO_MUST_ADJUST_MS, SPEED);
        break;
    case LinePosition::LEFT:
        moveTo(Direction::FORWARD, SPEED_TO_ADJUST_MS, SPEED);
        break;
    case LinePosition::RIGHT:
        moveTo(Direction::FORWARD, SPEED, SPEED_TO_ADJUST_MS);
        break;
    case LinePosition::MOST_RIGHT:
        moveTo(Direction::FORWARD, SPEED, SPEED_TO_MUST_ADJUST_MS);
        break;
    case LinePosition::CROSS_DETECTED:
    case LinePosition::CROSS_LEFT_DETECTED:
    case LinePosition::CROSS_RIGHT_DETECTED:
    case LinePosition::LOST:
    case LinePosition::CENTER:
        moveTo(Direction::FORWARD, SPEED, SPEED);
        break;
    default:
        break;
    }
    _delay_ms(DELAY_CORRECTION_MS);
}

void Robot::findLine(const Direction &direction)
{
    linePosition_ = lineSensor_.determineLinePosition();
    while (linePosition_ != LinePosition::CENTER && linePosition_ != LinePosition::RIGHT && linePosition_ != LinePosition::LEFT)
    {
        moveTo(direction, SPEED_TO_FIND_LINE, SPEED_TO_FIND_LINE);
        _delay_ms(DELAY_FIND_LINE_MS);
        linePosition_ = lineSensor_.determineLinePosition();
        stopEngine();
    }
    _delay_ms(DELAY_AFTER_FIND_LINE_MS);
}

bool Robot::isInitialCornerFound() const
{
    return isInitialCornerFound_;
}

bool Robot::isReturnToInitialCorner() const
{
    return isReturnToIntialaCorner_;
}

void Robot::buildSchema(char step)
{
    searchEngine_.buildSchema(step, currentSchema_);
}

void Robot::displayNode(const Corner &node)
{
    lcm_.write("Corner: ");
    lcm_ << "(";
    lcm_ << (uint16_t)node.coordinate.row;
    lcm_ << ",";
    lcm_ << (uint16_t)node.coordinate.column;
    lcm_ << ")";
    switch (node.orientation)
    {
    case Cardinal::NORTH:
        lcm_.write("NORD", LCM_FW_HALF_CH);
        break;
    case Cardinal::EAST:
        lcm_.write("EST", LCM_FW_HALF_CH);
        break;
    case Cardinal::SOUTH:
        lcm_.write("SUD", LCM_FW_HALF_CH);
        break;
    case Cardinal::WEST:
        lcm_.write("OUEST", LCM_FW_HALF_CH);
        break;
    default:
        break;
    }
}

LinePosition Robot::getLinePosition()
{
    return lineSensor_.determineLinePosition();
}

void Robot::searchInitialCorner()
{
    if (!isChronoRunning_)
    {
        if (isFirstChronoRunning_)
        {
            chrono_.start(DELAY_TO_TAKE_HALF_SEGMENT_MS); // ajuster parfois
            isFirstChronoRunning_ = false;
        }
        else
            chrono_.start(DELAY_TO_TAKE_SEGMENT_MS); // ajuster parfois
        isChronoRunning_ = true;
    }

    if (currentSchema_.size >= MIN_SIZE_SCHEMA)
    {
        int8_t indiceSchema = searchEngine_.isSchemaExist(currentSchema_.tabSchema, currentSchema_.size, MapCorner);
        if (indiceSchema != -1)
        {
            initialCorner_ = searchEngine_.identifyNode(MapCorner, indiceSchema);
            isInitialCornerFound_ = true;
        }
    }
    if (!isInitialCornerFound_)
    {
        followLine();
        linePosition_ = lineSensor_.determineLinePosition();

        if (linePosition_ == LinePosition::CROSS_LEFT_DETECTED)
            buildSchema('G');
        else if (linePosition_ == LinePosition::CROSS_RIGHT_DETECTED)
            buildSchema('D');
        else if (linePosition_ == LinePosition::LOST)
        {
            buildSchema('X');
            int8_t indiceSchema = searchEngine_.isSchemaExist(currentSchema_.tabSchema, currentSchema_.size, MapCorner);
            if (indiceSchema != -1)
            {
                initialCorner_ = searchEngine_.identifyNode(MapCorner, indiceSchema);
                isInitialCornerFound_ = true;
            }
            else
            {
                // si jamais on arrive a lost et aucune sequence n'est detecté on fait demi tour
                // et on recommence
                // chrono_.stop();
                chrono_.reset();
                forwardBeforeTurn();
                isChronoRunning_ = false;
                isFirstChronoRunning_ = true;
                goBackToInitialCorner(Direction::LEFT, Direction::RIGHT);
                currentSchema_ = {};
                lcm_.clear();
            }
        }
    }
    // moveTo(Direction::FORWARD, SPEED, SPEED);
}

void Robot::forwardBeforeTurn()
{
    moveTo(Direction::FORWARD, SPEED, SPEED);
    _delay_ms(DELAY_BEFORE_TURN_MS);
}

void Robot::goBackToInitialCorner(const Direction &directionToTurnFirst, const Direction &directionToTurnSecond)
{
    stopEngine();
    _delay_ms(DELAY_TO_STOP_ENGINE_FOR_BACK_MS);
    turn180Degre(directionToTurnFirst);
    linePosition_ = lineSensor_.determineLinePosition();
    while (linePosition_ != LinePosition::LOST)
    {
        if (linePosition_ == LinePosition::CROSS_LEFT_DETECTED || linePosition_ == LinePosition::CROSS_RIGHT_DETECTED) // pour palier a certains cas
        {
            moveTo(Direction::FORWARD, SPEED, SPEED);
            _delay_ms(DELAY_TO_SKIP_CROSS_NOT_NECESSARY_MS);
        }
        followLine();
    }
    forwardBeforeTurn();
    turn180Degre(directionToTurnSecond);
}

void Robot::searchInitialCornerAndReturn()
{
    if (!isInitialCornerFound_)
        searchInitialCorner();
    else
    {
        chrono_.stop();
        stopEngine();
        playSong(NOTE_IF_CORNER_FOUND);
        _delay_ms(DELAY_TO_PLAY_SONG_MS);
        stopSong();
        setLedColorOn(LedColor::GREEN);
        goBackToInitialCorner(initialCorner_.directionToTurnFirst, initialCorner_.directionToTurnSecond);
        displayNode(initialCorner_.corner);
        stopRobot();
        isReturnToIntialaCorner_ = true;
    }
}

void Robot::setMode(const RobotMode &mode)
{
    mode_ = mode;
}

RobotMode Robot::getMode() const
{
    return mode_;
}

void Robot::displayJourneyMode(const volatile PathConfigState &pathConfigState, bool yes)
{
    lcm_.clear();
    if (pathConfigState == PathConfigState::SELECT_ROW || pathConfigState == PathConfigState::INIT_ROW || pathConfigState == PathConfigState::RESET)
    {
        lcm_.write("LIGNE");
        lcm_.write(" ", LCM_FW_HALF_CH);
        lcm_ << (uint16_t)finalPoint_.row;
    }
    else if (pathConfigState == PathConfigState::SELECT_COLUMN || pathConfigState == PathConfigState::INIT_COL)
    {
        lcm_.write("COLONNE");
        lcm_.write(" ", LCM_FW_HALF_CH);
        lcm_ << (uint16_t)finalPoint_.column;
    }
    else if (pathConfigState == PathConfigState::CONFIRMATION || pathConfigState == PathConfigState::INIT_CONFIRMATION)
    {
        lcm_ << "(";
        lcm_ << (uint16_t)finalPoint_.row;
        lcm_ << ",";
        lcm_ << (uint16_t)finalPoint_.column;
        lcm_ << ")";
        lcm_ << "  OK ?";

        if (yes)
            lcm_.write("OUI", LCM_FW_HALF_CH);
        else
            lcm_.write("NON", LCM_FW_HALF_CH);
    }
}

void Robot::incrementPointRow()
{
    finalPoint_.row++;
    if (finalPoint_.row > MAX_ROW_VALUE)
        finalPoint_.row = 1;
}

void Robot::incrementPointCol()
{
    finalPoint_.column++;
    if (finalPoint_.column > MAX_COlS_VALUE)
        finalPoint_.column = 1;
}

const Coordinate &Robot::getInitialPoint() const
{
    return initialPoint_;
}

const Coordinate &Robot::getCurrentPoint() const
{
    return currentPoint_;
}

const Coordinate &Robot::getFinalPoint() const
{
    return finalPoint_;
}

void Robot::resetFinalPoint()
{
    finalPoint_ = {1, 1};
}

void Robot::setRoad(const RoadSchema &roadSchema)
{
    roadSchema_.size = roadSchema.size + 2;
    roadSchema_.road[0] = CardinalDirection::START;
    for (uint8_t i = 0; i < roadSchema.size; i++)
        roadSchema_.road[i + 1] = roadSchema.road[i];
    roadSchema_.road[roadSchema_.size - 1] = CardinalDirection::END;
    currentIndexRoad_ = 0;
    isRoadEnd_ = false;
    isObstacleDetected_ = false;
}

void Robot::turnWithDecision(const CardinalDirection &dir1, const CardinalDirection &dir2)
{
    switch (dir1)
    {
    case CardinalDirection::EAST:
        if (dir2 == CardinalDirection::NORTH)
            turn90Degre(Direction::LEFT);
        else if (dir2 == CardinalDirection::WEST)
            turn180Degre(Direction::LEFT);
        else if (dir2 == CardinalDirection::SOUTH)
            turn90Degre(Direction::RIGHT);
        break;
    case CardinalDirection::NORTH:
        if (dir2 == CardinalDirection::EAST)
            turn90Degre(Direction::RIGHT);
        else if (dir2 == CardinalDirection::WEST)
            turn90Degre(Direction::LEFT);
        else if (dir2 == CardinalDirection::SOUTH)
            turn180Degre(Direction::LEFT);
        break;
    case CardinalDirection::WEST:
        if (dir2 == CardinalDirection::NORTH)
            turn90Degre(Direction::RIGHT);
        else if (dir2 == CardinalDirection::EAST)
            turn180Degre(Direction::LEFT);
        else if (dir2 == CardinalDirection::SOUTH)
            turn90Degre(Direction::LEFT);
        break;
    case CardinalDirection::SOUTH:
        if (dir2 == CardinalDirection::NORTH)
            turn180Degre(Direction::LEFT);
        else if (dir2 == CardinalDirection::WEST)
            turn90Degre(Direction::RIGHT);
        else if (dir2 == CardinalDirection::EAST)
            turn90Degre(Direction::LEFT);
        break;
    default:
        break;
    }
}

void Robot::updateCurrentPoint()
{
    switch (currentDirection_)
    {
    case CardinalDirection::EAST:
        currentPoint_.column++;
        break;
    case CardinalDirection::SOUTH:
        currentPoint_.row++;
        break;
    case CardinalDirection::NORTH:
        currentPoint_.row--;
        break;
    case CardinalDirection::WEST:
        currentPoint_.column--;
        break;
    default:
        break;
    }
}

Coordinate Robot::getNextPoint() const
{
    Coordinate nextPoint = currentPoint_;

    switch (currentDirection_)
    {
    case CardinalDirection::EAST:
        nextPoint.column++;
        break;
    case CardinalDirection::SOUTH:
        nextPoint.row++;
        break;
    case CardinalDirection::NORTH:
        nextPoint.row--;
        break;
    case CardinalDirection::WEST:
        nextPoint.column--;
        break;
    default:
        break;
    }
    return nextPoint;
}

void Robot::endRoadRoutine()
{
    lcm_.clear();
    initialPoint_ = finalPoint_;
    currentPoint_ = finalPoint_;
    resetFinalPoint();
    currentIndexRoad_ = 0;
    // a faire c'est que cela fausse l'algo
    if (roadSchema_.road[roadSchema_.size - 2] != CardinalDirection::START)
        initialDirection_ = roadSchema_.road[roadSchema_.size - 2];
    linePosition_ = lineSensor_.determineLinePosition();
    if (linePosition_ == LinePosition::LOST)
    {
        turn180Degre(Direction::RIGHT);
        switch (initialDirection_)
        {
        case CardinalDirection::NORTH:
            initialDirection_ = CardinalDirection::SOUTH;
            break;
        case CardinalDirection::WEST:
            initialDirection_ = CardinalDirection::EAST;
            break;
        case CardinalDirection::SOUTH:
            initialDirection_ = CardinalDirection::NORTH;
            break;
        case CardinalDirection::EAST:
            initialDirection_ = CardinalDirection::WEST;
            break;
        default:
            break;
        }
    }
    isRoadEnd_ = true;
    for (uint8_t i = 0; i < N_TIME_TO_PLAY_SONG; i++)
    {
        playSong(NOTE_IF_CORNER_FOUND);
        _delay_ms(DELAY_200_MS);
        stopSong();
        _delay_ms(DELAY_100_MS);
    }
    stopRobot();
}

void Robot::takeDecision()
{
    // desactiver le timer car cross detecté ou timer expirée
    chrono_.stop();
    isChronoRunning_ = false;
    stopEngine();
    _delay_ms(DELAY_AJUST_WHILE_RUNNING);
    // tourner si les directions sont pas les memes
    if (currentDirection_ != nextDirection_)
        turnWithDecision(currentDirection_, nextDirection_);
}
void Robot::routineWhenObstacleDetected()
{
    lcm_.clear();
    stopEngine();
    playSong(NOTE_IF_OBSTACLE_DETECTED);
    lcm_.write("Poteau detecte");
    _delay_ms(MIDDLE_DELAY_SPOT_DETECTED_MS);
    lcm_.clear();
    lcm_.write("Changement d'itineraire");
    _delay_ms(MIDDLE_DELAY_SPOT_DETECTED_MS);
    stopSong();
    initialDirection_ = currentDirection_;
    isObstacleDetected_ = true;
    lcm_.clear();
}
void Robot::followRoad()
{
    currentDirection_ = roadSchema_.road[currentIndexRoad_];
    if (currentDirection_ == CardinalDirection::END)
        endRoadRoutine();
    else
    {
        nextDirection_ = roadSchema_.road[currentIndexRoad_ + 1];
        if (currentDirection_ == CardinalDirection::START)
        {
            turnWithDecision(initialDirection_, nextDirection_);
            currentIndexRoad_++;
        }
        else
        {
            // il faut qu'il se positionne bien avant qu'on fasse la lecture ca peut nuire parfois !!!!!!
            if (obstacleDetector_.isSpotDetected())
                routineWhenObstacleDetected();
            else
            {
                if (!isChronoRunning_)
                {
                    chrono_.start(DELAY_TO_TAKE_SEGMENT_ROAD_MS); // il avance un peu d'ou il faut diminuer le temps TODO nbre magique
                    isChronoRunning_ = true;
                }
                // avance jusqu'a cross ou temps ecoulé
                linePosition_ = lineSensor_.determineLinePosition();
                while (linePosition_ != LinePosition::CROSS_DETECTED && linePosition_ != LinePosition::CROSS_RIGHT_DETECTED &&
                       linePosition_ != LinePosition::CROSS_LEFT_DETECTED && isChronoRunning_)
                {
                    followLine();
                    if (obstacleDetector_.isSpotDetected())
                    {
                        chrono_.stop();
                        isChronoRunning_ = false;
                        routineWhenObstacleDetected();
                        break;
                    }
                }
                if (isObstacleDetected_)
                {
                    // faire une marche arriere
                    moveTo(Direction::BACKWARD, SPEED, SPEED);
                    _delay_ms(DELAY_TO_AJUST_IF_OBSTACLE_DETECTED);
                    stopEngine();
                }
                else
                {
                    moveTo(Direction::FORWARD, SPEED, SPEED);
                    _delay_ms(DELAY_AJUST_WHILE_RUNNING);
                    stopEngine();
                    _delay_ms(DELAY_AJUST_WHILE_RUNNING);
                    // avancer avant de prendre decision avec le timer
                    linePosition_ = lineSensor_.determineLinePosition();
                    isGoForwardBeforeTakeDecision_ = true;
                    chrono_.reset();
                    if (!isChronoRunning_)
                        chrono_.start(DELAY_BEFORE_TAKE_DECISION_S);
                    else if (linePosition_ == LinePosition::LOST)
                    {
                        lcm_.clear();
                        lcm_.write("LOST");
                        chrono_.start(DELAY_BEFORE_TAKE_LOST_DECISION_S);
                    }
                    else
                        chrono_.start(DELAY_BEFORE_TAKE_CROSS_DECISION_S);

                    while (isGoForwardBeforeTakeDecision_)
                        followLine();
                    // prend decision
                    updateCurrentPoint();
                    takeDecision();
                    currentIndexRoad_++;
                }
            }
        }
    }
}
bool Robot::isRoadEnd() const
{
    return isRoadEnd_;
}

bool Robot::isObstacleDetected() const
{
    return isObstacleDetected_;
}

void Robot::setIsRoadEnd(bool value)
{
    isRoadEnd_ = value;
}

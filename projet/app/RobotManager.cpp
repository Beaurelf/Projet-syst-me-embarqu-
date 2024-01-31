/**
 * @file RobotManager.cpp
 * @brief Implémentation de la classe RobotManager.
 *
 * Ce fichier contient les implémentations des méthodes de la classe RobotManager,
 * qui gère les routines et les modes de fonctionnement du robot.
 */

#include "RobotManager.hpp"

RobotManager::RobotManager() : isSelected(false), isValidated(false), isYes(true)
{
}

void RobotManager::updateSelectionJourneyRoutine(volatile PathConfigState &pathConfigState)
{
    switch (pathConfigState)
    {
    case PathConfigState::INIT_ROW:
    case PathConfigState::SELECT_ROW:
        if (isSelected)
            pathConfigState = PathConfigState::SELECT_ROW;
        else if (isValidated)
            pathConfigState = PathConfigState::INIT_COL;
        break;
    case PathConfigState::INIT_COL:
    case PathConfigState::SELECT_COLUMN:
        if (isSelected)
            pathConfigState = PathConfigState::SELECT_COLUMN;
        else if (isValidated)
            pathConfigState = PathConfigState::INIT_CONFIRMATION;
        break;
    case PathConfigState::INIT_CONFIRMATION:
    case PathConfigState::CONFIRMATION:
        if (isSelected)
            pathConfigState = PathConfigState::CONFIRMATION;
        else if (isValidated)
        {
            if (isYes)
                pathConfigState = PathConfigState::FINALIZED;
            else
                pathConfigState = PathConfigState::RESET;
        }
        break;
    case PathConfigState::RESET:
        pathConfigState = PathConfigState::SELECT_ROW;
        break;
    case PathConfigState::FINALIZED:
        break;
    }
}

void RobotManager::executeSelectionRoutineMode(const volatile PathConfigState &pathConfigState, Robot *robot)
{
    switch (pathConfigState)
    {
    case PathConfigState::INIT_ROW:
        robot->displayJourneyMode(pathConfigState);
        break;
    case PathConfigState::SELECT_ROW:
        robot->incrementPointRow();
        robot->displayJourneyMode(pathConfigState);
        break;
    case PathConfigState::INIT_COL:
        robot->displayJourneyMode(pathConfigState);
        break;
    case PathConfigState::SELECT_COLUMN:
        robot->incrementPointCol();
        robot->displayJourneyMode(pathConfigState);
        break;
    case PathConfigState::INIT_CONFIRMATION:
        robot->displayJourneyMode(pathConfigState);
        break;
    case PathConfigState::RESET:
        if (isValidated)
        {
            if (!isYes)
            {
                robot->resetFinalPoint();
                robot->displayJourneyMode(pathConfigState);
                isYes = true;
            }
        }
        break;
    case PathConfigState::CONFIRMATION:
        if (isSelected)
        {
            isYes = !isYes;
            robot->displayJourneyMode(pathConfigState, isYes);
        }
        break;
    case PathConfigState::FINALIZED:
        break;
    }
}

void RobotManager::setIsSelected(bool value)
{
    isSelected = value;
}

void RobotManager::setIsValidated(bool value)
{
    isValidated = value;
}

void RobotManager::setIsYes(bool value)
{
    isYes = value;
}

void RobotManager::runRobotRoutine(Robot *robot, volatile PathConfigState &pathConfigState)
{
    switch (robot->getMode())
    {
    case RobotMode::IDENTIFY_CORNER:
        executeIdentifyCornerRoutine(robot);
        break;
    case RobotMode::MAKE_JOURNEY:
        executeMakeJourneyRoutine(robot, pathConfigState);
        break;
    default:
        break;
    }
}

void RobotManager::executeIdentifyCornerRoutine(Robot *robot)
{
    robot->turnOffLed();
    _delay_ms(DELAY_BEFORE_START_IDENTIFY_CORNER_MS);
    while (!robot->isReturnToInitialCorner())
    {
        robot->searchInitialCornerAndReturn();
    }
}

void RobotManager::executeMakeJourneyRoutine(Robot *robot, volatile PathConfigState &pathConfigState)
{
    robot->turnOffLed();
    Dijkstra dijkstra;
    for (uint8_t i = 0; i < N_ROAD; i++)
    {
        robot->displayJourneyMode(pathConfigState);
        while (pathConfigState != PathConfigState::FINALIZED)
            ;
        RoadSchema roadShema = dijkstra.generateRoad(robot->getInitialPoint(), robot->getFinalPoint());
        robot->setRoad(roadShema);
        while (!robot->isRoadEnd())
        {
            robot->followRoad();
            // verifier si obstacle detecté
            if (robot->isObstacleDetected())
            {
                // detruit le point recalculer le nouveau parcours et faire une setRoad
                dijkstra.destroyPath(robot->getNextPoint());
                roadShema = dijkstra.generateRoad(robot->getCurrentPoint(), robot->getFinalPoint());
                robot->setRoad(roadShema);
            }
        }

        resetMakeJourneyRoutine(pathConfigState, robot, dijkstra);
    }
}

void RobotManager::resetMakeJourneyRoutine(volatile PathConfigState &pathConfigState, Robot *robot, Dijkstra &dijkstra)
{
    pathConfigState = PathConfigState::INIT_ROW;
    setIsSelected(false);
    setIsValidated(false);
    setIsYes(true);
    robot->setIsRoadEnd(false);

    // reset le matrice adjacence
    dijkstra.initMatrix();
}

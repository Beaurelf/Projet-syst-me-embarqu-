#include "RobotManager.hpp"
#include "Communication.hpp"
#include "ExternalInterruption.hpp"
#include <avr/interrupt.h>

volatile PathConfigState gPathConfigState = PathConfigState::INIT_ROW;

volatile bool gIsButtonValidationPressed = false;
volatile bool gIsButtonSelectionPressed = false;
volatile bool gIsButtonMotherBordPressed = false;

Robot *gRobotMain;
RobotManager *gRobotManager;

// Button sur le breadbord
ISR(INT0_vect)
{
    gIsButtonMotherBordPressed = gRobotMain->isButtonMotherBoardPressed();
    if (gIsButtonMotherBordPressed)
    {
        if (gRobotMain->getMode() == RobotMode::UNDEFINED)
            gRobotMain->setMode(RobotMode::IDENTIFY_CORNER);
    }
    gIsButtonMotherBordPressed = false;
    setRegisterBits(&EIFR, INTF1);
}

// Button validation
ISR(INT1_vect)
{
    gIsButtonValidationPressed = gRobotMain->isButtonValidationPressed();
    if (gIsButtonValidationPressed)
    {
        if (gRobotMain->getMode() == RobotMode::MAKE_JOURNEY && gPathConfigState != PathConfigState::FINALIZED)
        {
            gRobotManager->setIsSelected(false);
            gRobotManager->setIsValidated(true);
            gRobotManager->updateSelectionJourneyRoutine(gPathConfigState);
            gRobotManager->executeSelectionRoutineMode(gPathConfigState, gRobotMain);
        }
    }
    gIsButtonValidationPressed = false;
    setRegisterBits(&EIFR, INTF0);
}

// Button selection
ISR(INT2_vect)
{
    gIsButtonSelectionPressed = gRobotMain->isButtonSelectionPressed();
    if (gIsButtonSelectionPressed)
    {
        if (gRobotMain->getMode() == RobotMode::MAKE_JOURNEY && gPathConfigState != PathConfigState::FINALIZED)
        {
            gRobotManager->setIsSelected(true);
            gRobotManager->setIsValidated(false);
            gRobotManager->updateSelectionJourneyRoutine(gPathConfigState);
            gRobotManager->executeSelectionRoutineMode(gPathConfigState, gRobotMain);
        }
        else if (gRobotMain->getMode() == RobotMode::UNDEFINED)
        {
            gRobotMain->setMode(RobotMode::MAKE_JOURNEY);
        }
    }

    gIsButtonSelectionPressed = false;
    setRegisterBits(&EIFR, INTF2);
}

int main()
{
    Communication::initializeUART();
    ExternalInterruption::enable(ExternalInterrupt::INT_0, InterruptTrigger::ANY_EDGE);
    ExternalInterruption::enable(ExternalInterrupt::INT_1, InterruptTrigger::ANY_EDGE);
    ExternalInterruption::enable(ExternalInterrupt::INT_2, InterruptTrigger::ANY_EDGE);
    sei();
    Robot robot;
    gRobotMain = &robot;
    RobotManager robotManager;
    gRobotManager = &robotManager;

    robot.setLedColorOn(LedColor::RED);

    while (robot.getMode() == RobotMode::UNDEFINED)
        ;

    robotManager.runRobotRoutine(&robot, gPathConfigState);
}

#include "ExternalInterruptConfig.hpp"

constexpr InterruptConfig ExternalInterruptionConfig::InterruptConfigs[];

void ExternalInterruptionConfig::setTriggerType(const InterruptConfig &config, const InterruptTrigger &trigger)
{
    clearRegisterBits(&EICRA, config.ISCn0);
    clearRegisterBits(&EICRA, config.ISCn1);
    switch (trigger)
    {
    case InterruptTrigger::ANY_EDGE:
        setRegisterBits(&EICRA, config.ISCn0);
        break;
    case InterruptTrigger::FALLING_EDGE:
        setRegisterBits(&EICRA, config.ISCn1);
        break;
    case InterruptTrigger::RISING_EDGE:
        setRegisterBits(&EICRA, config.ISCn0);
        setRegisterBits(&EICRA, config.ISCn1);
        break;
    default:
        break;
    }
}
void ExternalInterruptionConfig::clearAllExternalInterrupt()
{
    for (const auto &config : InterruptConfigs)
    {
        clearRegisterBits(&EIMSK, config.interruptionType);
        clearRegisterBits(&EICRA, config.ISCn0);
        clearRegisterBits(&EICRA, config.ISCn1);
    }
}
void ExternalInterruptionConfig::enableExternalInterrupt(const ExternalInterrupt &interrupt)
{
    setRegisterBits(&EIMSK, InterruptConfigs[static_cast<int>(interrupt)].interruptionType);
}
void ExternalInterruptionConfig::configureInterruptTrigger(const ExternalInterrupt &interrupt, const InterruptTrigger &trigger)
{
    setTriggerType(InterruptConfigs[static_cast<int>(interrupt)], trigger);
}
void ExternalInterruptionConfig::clearExternalInterrupt(const ExternalInterrupt &interrupt)
{
    const auto &config = InterruptConfigs[static_cast<int>(interrupt)];
    clearRegisterBits(&EIMSK, config.interruptionType);
    clearRegisterBits(&EICRA, config.ISCn0);
    clearRegisterBits(&EICRA, config.ISCn1);
}
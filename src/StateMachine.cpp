#include "StateFunctions.h"
#include "StateMachine.h"


void state_machine_run()
{

    switch (current_states)
    {
        case states::start_state: Start_State(); break;
        case states::menu_state: Menu_State(); break;
        case states::calculator_state: Calculator_State(); break;
        default: break;

    }
}
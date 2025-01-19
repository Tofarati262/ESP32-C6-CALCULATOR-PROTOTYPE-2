#ifndef STATEMACHINE_H
#define STATEMACHINE_H

// Define the state enum
enum class states {
    start_state,
    menu_state,
    calculator_state
};

// Declare the global state variable
extern states current_states;

// Declare the state machine runner function
void state_machine_run();

#endif // STATEMACHINE_H

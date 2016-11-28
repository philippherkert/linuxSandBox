
/**
 * Start State of the controller.
 * This state waites for the first message to arrive
 */

#pragma once

#include "state.hpp"

class Idle_State : public State
{
	public:
		Idle_State(Controller* controller);
		virtual ~Idle_State();
		virtual void act();
};

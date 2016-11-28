
/**
 * Stops the controller thread
 */

#pragma once

#include "../state.hpp"
#include "action.hpp"

class State;

class Load_Action : public Action
{
	public:
		Load_Action();
		virtual ~Load_Action();
		virtual void visit(State* state);
};

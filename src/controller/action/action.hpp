
/**
 * Action Interface allows main to talk to controller
 */

#pragma once

#include "../state.hpp"

class State;

class Action
{
	public:
		Action();
		virtual ~Action();
		virtual void visit(State* state) = 0;
};

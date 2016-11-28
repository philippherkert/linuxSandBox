
/**
 * Stops the controller thread
 */

#pragma once

#include "../state.hpp"

class State;

class Close_Action : public Action
{
	public:
		Close_Action();
		virtual ~Close_Action();
		virtual void visit(State* state);
};

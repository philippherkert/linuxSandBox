
/**
 * The state of the Controller
 */

#pragma once

#include "controller.hpp"

class Controller;

class State
{
	public:
		State(Controller* controller);
		virtual ~State();
		virtual void act() = 0;
		Controller* controller;

	protected:
};

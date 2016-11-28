
#include "action/action.hpp"
#include "idle_state.hpp"

Idle_State::Idle_State(Controller* controller)
	:State(controller)
{
}

Idle_State::~Idle_State()
{

}

void
Idle_State::act()
{
	Action* action = controller->message_pop();
	if(action == NULL)
	{
		return;
	}
	action->visit(this);
	delete action;
}

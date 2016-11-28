
#include "close_action.hpp"

Close_Action::Close_Action()
{

}

Close_Action::~Close_Action()
{

}

void
Close_Action::visit(State* state)
{
	state->controller->stop_thread();
}

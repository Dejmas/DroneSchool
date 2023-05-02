#include "command.h"
#include "user.h"

ICommand::ICommand(/* args */)
{
}

bool ICommand::isDone (CDrone & drone) const {
    return false;
}

void ICommand::letUserWorkOnIt (IUser * user) {
    user->workOnCommand(*this);
}

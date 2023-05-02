#pragma once

#include <memory>
class IUser;
class CDrone;
class CRemoteControl;

class ICommand
{
private:

public:
    ICommand(/* args */);
    virtual ~ICommand() = default;

    virtual bool isDone (CDrone & drone) const;

    void letUserWorkOnIt (IUser *);

    virtual void workOnIt (CRemoteControl * ) = 0;

};

using ACommand = std::shared_ptr<ICommand>;


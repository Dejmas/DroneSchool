#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "remotecontrol.h"
#include "command.h"
#include <string>
#include <vector>
#include <iostream>

class CSupervisor : public IUser {
public:
    CSupervisor(const std::string & name)
    : IUser (name) {
    }

    ~CSupervisor() {
    }

    void workOnCommand (ICommand & command) {
        command.workOnIt(m_remote);
    }

    void update () override {
    }

private:

};

#endif
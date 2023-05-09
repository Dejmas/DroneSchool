#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "remotecontrol.h"
#include "userinterface.h"

#include <string>
#include <vector>
#include <stdexcept>

class CStudent : public IUser {
public:
    CStudent(const std::string & name, IUserInterface & ui)
    : IUser(name)
    , m_ui (ui) {
    }
    ~CStudent() {
    }

    CRemoteControl * getRemote() {
        if (!m_remote) throw std::runtime_error("missing remote"); 
        return m_remote;
    }

    void workOnCommand (ICommand & command) override {
        TUserInputAction userActions = m_ui.getUserActions();
        if (userActions.m_backward ) m_remote->goBackward();
        if (userActions.m_forward  ) m_remote->goForward();
        if (userActions.m_turnLeft ) m_remote->turnLeft();
        if (userActions.m_turnRight) m_remote->turnRight();
        if (userActions.m_pick) {
            m_remote->pick();
        }
    }

    void update () override {
        
    }

private:

    IUserInterface & m_ui;

};

#endif
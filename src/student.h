#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
#include "remotecontrol.h"
#include <string>
#include <vector>
#include <stdexcept>

class CStudent : public IUser {
public:
    CStudent(const std::string & name)
    : IUser(name) {
    }
    ~CStudent() {
    }

    CRemoteControl * getRemote() {
        if (!m_remote) throw std::runtime_error("missing remote"); 
        return m_remote;
    } 

    void droneForward() {
        if (!m_remote) throw std::runtime_error("missing remote"); 
        m_remote->goForward();
    }

    void droneBackward() {
        if (!m_remote) throw std::runtime_error("missing remote");
        m_remote->goBackward();
    }

    void droneLeft() {
        if (!m_remote) throw std::runtime_error("missing remote");
        m_remote->goLeft();
    }

    void droneRight() {
        if (!m_remote) throw std::runtime_error("missing remote");
        m_remote->goRight();
    }

    void workOnCommand (ICommand & command) override {
        if (m_userActions.m_backward ) m_remote->goBackward();
        if (m_userActions.m_forward  ) m_remote->goForward();
        if (m_userActions.m_turnLeft ) m_remote->turnLeft();
        if (m_userActions.m_turnRight) m_remote->turnRight();
        if (m_userActions.m_pick) {
            m_remote->pick();
        }
    }

    void update () override {
        
    }

private:

};

#endif
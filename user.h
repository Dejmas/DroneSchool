#ifndef USER_H
#define USER_H
#include <string>
#include "remotecontrol.h"

class CUser {
    std::string m_nick;
    CRemoteControl * m_remote;

    public:
    CUser(const std::string & nick): m_nick(nick) {
        
    }

    void setRemote(CRemoteControl * remote) {
        m_remote = remote;
    }

};

#endif // USER_H
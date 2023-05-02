#ifndef USER_H
#define USER_H
#include <string>
#include "remotecontrol.h"
#include "utils.h"
#include "command.h"
#include <memory>

struct TUserInputAction {
    bool m_forward = false,
         m_backward = false, 
         m_turnLeft = false, 
         m_turnRight = false,
         m_pick = false;
};

class ICommand;

class IUser {

    public:
        IUser(const std::string & name): m_name(name) {
        }

        void setRemote(CRemoteControl * remote) {
            m_remote = remote;
        }

        void setUserActions(TUserInputAction actions) {
            m_userActions = actions;
        }

        virtual ~IUser() = default;

        virtual void update () = 0;

        virtual void workOnCommand(ICommand & command) = 0;

    protected:
        std::string      m_name;
        CRemoteControl * m_remote;
        TUserInputAction  m_userActions;

};

using AUser = std::shared_ptr<IUser>;

#endif // USER_H
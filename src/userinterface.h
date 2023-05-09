#ifndef USERINTERFACE_H
#define USERINTERFACE_H

struct TUserInputAction {
    bool m_forward = false,
         m_backward = false, 
         m_turnLeft = false, 
         m_turnRight = false,
         m_pick = false;
};

class IUserInterface {
    public:
        IUserInterface() = default;

        virtual ~IUserInterface() = default;

        TUserInputAction getUserActions() const { return m_userActions; }

    protected:
        TUserInputAction m_userActions;
};

#endif // USERINTERFACE_H
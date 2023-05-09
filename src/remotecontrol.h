#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

class CDrone; 
class CCoord; 

class CRemoteControl
{
private:
    CDrone & m_Drone;
    /* data */
public:
    CRemoteControl(CDrone & droneRef);
    ~CRemoteControl();

    void goForward();
    void goBackward();
    void turnRight();
    void turnLeft();
    void pick();

    CCoord getDronesLocation() const;

    double getDronesAngle() const;
};



#endif // REMOTECONTROL_H
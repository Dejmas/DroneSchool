#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include "drone.h"

class CRemoteControl
{
private:
    CDrone & m_Drone;
    /* data */
public:
    CRemoteControl(CDrone & droneRef)
    : m_Drone(droneRef) {
    }
    ~CRemoteControl() {};

    void goForward() {
        m_Drone.setForwardInpulse(120);
        //m_Drone.setMovingVector(CVector2D(0, -20));
    }
    void goBackward() {
        m_Drone.setForwardInpulse(-100);
        //m_Drone.setMovingVector(CVector2D(0, 20));
    }
    void goLeft() {
        m_Drone.setMovingVector(CVector2D(-20, 0));
    }
    void goRight() {
        m_Drone.setMovingVector(CVector2D(20, 0));
    }
    void stop() {
        m_Drone.setMovingVector(CVector2D(0, 0));
    }
    void turnRight() {
        m_Drone.setAngle(m_Drone.getAngle() + 30);
    }

    void turnLeft() {
        m_Drone.setAngle(m_Drone.getAngle() - 30);
    }

    CCoord getDronesLocation() const {
        return m_Drone.getPosition();
    }

    double getDronesAngle() const {
        return m_Drone.getAngle();
    }
};

#endif // REMOTECONTROL_H
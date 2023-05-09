#include "remotecontrol.h"
#include "drone.h"
#include "utils.h"
CRemoteControl::CRemoteControl(CDrone & droneRef)
: m_Drone(droneRef) {
}

CRemoteControl::~CRemoteControl() {};

void CRemoteControl::goForward() {
    m_Drone.setForwardInpulse(30);
}
void CRemoteControl::goBackward() {
    m_Drone.setForwardInpulse(-20);
}
void CRemoteControl::turnRight() {
    m_Drone.rotateAngle(m_Drone.getAngle() - 15);
}

void CRemoteControl::turnLeft() {
    m_Drone.rotateAngle(m_Drone.getAngle() + 15);
}

void CRemoteControl::pick() {
    if (m_Drone.getBindedItem()) {
        m_Drone.drop();
    } else {
        m_Drone.pick();
    } 
}

CCoord CRemoteControl::getDronesLocation() const {
    return m_Drone.getPosition();
}

double CRemoteControl::getDronesAngle() const {
    return m_Drone.getAngle();
}

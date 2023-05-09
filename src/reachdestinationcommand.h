#pragma once

#include "command.h"
#include "utils.h"

class CReachDestinationCommand : public ICommand {

    CCoord m_destination;

public: 

    CReachDestinationCommand(CCoord dest) : m_destination(dest) {};

    virtual ~CReachDestinationCommand() {}

    virtual bool isDone (CDrone & drone) const override {
        return (drone.getPosition() - m_destination).abs() < 10;
    }

    virtual void workOnIt (CRemoteControl * remote) override {
        CCoord droneLoc = remote->getDronesLocation();
        CVector2D vecToDestination = m_destination - droneLoc;
        CVector2D dir = vecToDestination.norm();
        double rad = atan2(dir.x, dir.y);
        double deg = rad * 180 / M_PI;
        double droneDeg = remote->getDronesAngle();
        double angleDiff = normalize_angle(deg - droneDeg);

        // Turn if it helps
        if (angleDiff > 7.5) remote->turnLeft();
        else if (angleDiff < -7.5) remote->turnRight();

        // When destination is in the viewport go forward.
        if (fabs(angleDiff) <= 45 ) {
            if (vecToDestination.abs() > 10) {
                remote->goForward();
            }
        }

        /* std::cout 
            << "drone " << droneLoc << "\n"
            << "dest " << m_destination << "\n"
            << "vecToDestination " << vecToDestination << "\n"
            << "dir " << dir << "\n"
            << "deg " << deg << "\n"
            << "droneDeg " << droneDeg << "\n"
            << "angleDiff " << angleDiff << "\n"
            << "abs " << vecToDestination.abs() << "\n----\n"; */
    }    

    virtual void undo () override {
        // TODO:
    }  

};


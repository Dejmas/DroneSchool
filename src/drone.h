#ifndef DRONE_H
#define DRONE_H
#include <string>
#include "utils.h"
#include "item.h"

#include <cmath>

class CRemoteControl;
class CDroneSchool;

class CDrone : public IItem {
    private:        
        AItem           m_bindedItem;
        CDroneSchool  & m_school;
        CRemoteControl* m_remote;

        CVector2D       m_movingVector, m_targetVector, m_startVector;
        double          m_maxSpeed, m_forwardForce, m_moveFraction, m_angleStart, m_angleTarget, m_angleFraction;


    public:
        CDrone(CDroneSchool & school, const std::string & name, const std::string & textureName, CCoord pos = CCoord());

        void setMovingVector(CVector2D vec);

        void rotateAngle(double angle);

        void setForwardInpulse(double force);

        void update();

        void pick();

        void drop();

        CVector2D getTarget() const;

        CRemoteControl * getRemoteControl();

        AItem getBindedItem() const;
};


#endif // DRONE_H


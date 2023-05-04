#include "drone.h"
#include "remotecontrol.h"
#include "droneschool.h"

namespace {
    const double PICK_DISTANCE = 25;
}


CDrone::CDrone(CDroneSchool & school, const std::string & name, const std::string & textureName, CCoord pos)
: IItem(name, textureName, pos, 4*50, 4*50, 0)
, m_school(school)
, m_maxSpeed(5.0)
, m_forwardForce(0)
, m_moveFraction(1)
, m_angleStart{}
, m_angleTarget{}
, m_angleFraction(1)
, m_remote(new CRemoteControl(*this)) {}

void CDrone::setMovingVector(CVector2D vec) {
    m_movingVector = vec;
}

void CDrone::rotateAngle(double angle) {
    m_angleStart = normalize_angle(m_angle);
    m_angleTarget = normalize_angle(angle);
    m_angleFraction = 0;
}

void CDrone::setForwardInpulse(double force) {
    m_moveFraction = 0;
    double angleCorrected = fmod(360-m_angle-270, 360.0);
    double ix = cos(angleCorrected*M_PI/180)*force + m_position.x;
    double iy = sin(angleCorrected*M_PI/180)*force + m_position.y;
    m_targetVector = {ix, iy};
    m_startVector = {(double)m_position.x, (double) m_position.y};
}

void CDrone::update() {
    if (m_moveFraction < 1) {
        m_moveFraction += 0.1;
        auto vec = lerp(m_startVector, m_targetVector, m_moveFraction);
        m_position.x = vec.x;
        m_position.y = vec.y;
    }
    
    if (m_angleFraction < 1) {
        m_angleFraction += 0.1;
        m_angle = lerp_angle(m_angleStart, m_angleTarget, m_angleFraction);
    }

    if (m_bindedItem) {
        m_bindedItem->setAngle(m_angle);
        m_bindedItem->setPosition(m_position);
    }
    //m_position.addVector(m_movingVector);
    /* double angleDiff = m_angleTarget-m_angle;
    if (fabs(angleDiff) > 3) {
        double spinNow = 4*(angleDiff)/fabs(angleDiff);
        m_angleTarget -= spinNow;
        m_angle = m_angle + spinNow;
    } */
}

void CDrone::pick() {
    
    std::vector<AItem> itemsNear = m_school.getItemsNear(m_position, PICK_DISTANCE);
    for (size_t i = 0; i < itemsNear.size(); i ++) {
        if (itemsNear[i]->getIsPickable()) {
            m_bindedItem = itemsNear[i];
            std::cout << "Pick succefull\n";
            return;
        }
    }
    std::cout << "Pick failed\n";
}

void CDrone::drop() {
    if (m_bindedItem) {
        double newAngle = (m_bindedItem->getAngle() + randInteger(-10, 10)) ;
        CCoord newPosition = CCoord(
            m_bindedItem->getPosition().x + randInteger(-10, 10),
            m_bindedItem->getPosition().y + randInteger(-10, 10)
        );
        m_bindedItem->setAngle(newAngle);
        m_bindedItem->setPosition(newPosition);
        m_bindedItem = nullptr;
        std::cout << "Drop\n";
    }
}

CVector2D CDrone::getTarget() const {
    return m_targetVector;
}

CRemoteControl * CDrone::getRemoteControl() {
    return m_remote;
}

AItem CDrone::getBindedItem() const {
    return m_bindedItem; 
}
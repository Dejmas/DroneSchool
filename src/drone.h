#ifndef DRONE_H
#define DRONE_H
#include <string>
#include "utils.h"
#include <cmath>

class CDrone {
    private:
        static unsigned lastId; // todo initialize
        unsigned        m_id;
        std::string     m_name;
        CCoord          m_position;
        CVector2D       m_movingVector, m_targetVector, m_startVector;
        double          m_angle, m_angleTarget, m_maxSpeed, m_forwardForce, m_angleStart, m_angleFraction, m_moveFraction;

    public:
        CDrone(const std::string & name, CCoord pos = CCoord())
        : m_id(++lastId)
        , m_name(name) 
        , m_position(pos)
        , m_angle(0)
        , m_maxSpeed(5.0)
        , m_forwardForce(0)
        , m_angleFraction(1)
        , m_moveFraction(1) {}

        void setMovingVector(CVector2D vec) {
            m_movingVector = vec;
        }

        void setAngle(double angle) {
            m_angleStart = m_angle;
            m_angleTarget = angle;
            m_angleFraction = 0;
        }

        void setForwardInpulse(double force) {
            m_moveFraction = 0;
            double angleCorrected = fmod(360-m_angle+270, 360.0);
            double ix = -cos(angleCorrected*M_PI/180)*force + m_position.x;
            double iy =  sin(angleCorrected*M_PI/180)*force + m_position.y;
            m_targetVector = {ix, iy};
            m_startVector = {(double)m_position.x, (double) m_position.y};
        }

        void update() {
            if (m_moveFraction < 1) {
                m_moveFraction += 0.1;
                auto vec = lerp(m_startVector, m_targetVector, m_moveFraction);
                m_position.x = vec.x;
                m_position.y = vec.y;
            }
            
            if (m_angleFraction < 1) {
                m_angleFraction += 0.1;
                m_angle = lerp(m_angleStart, m_angleTarget, m_angleFraction);
            }
            //m_position.addVector(m_movingVector);
            /* double angleDiff = m_angleTarget-m_angle;
            if (fabs(angleDiff) > 3) {
                double spinNow = 4*(angleDiff)/fabs(angleDiff);
                m_angleTarget -= spinNow;
                m_angle = m_angle + spinNow;
            } */
        }

        CVector2D getTarget() const {
            return m_targetVector;
        }

        CCoord getPosition() const {
            return m_position;
        }
        double getAngle() const {
            return m_angle;
        }
};

#endif // DRONE_H


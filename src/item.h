#pragma once

#include <memory>

#include "utils.h"

class IItem
{
private:
    static unsigned lastId; // todo initialize
protected:
    unsigned        m_id;
    std::string     m_name,
                    m_textureName;
    CCoord          m_position;
    int             m_width, m_height;
    double          m_angle;
    bool            m_isPickable;

public:
    IItem( const std::string & name,
           const std::string & textureName, 
           CCoord pos,
           int width, 
           int height, 
           double angle
        ) : m_id (++lastId)
          , m_name (name)
          , m_textureName (textureName)
          , m_position (pos)
          , m_width (width)
          , m_height (height)
          , m_angle (angle)
          , m_isPickable (false) {

    }

    virtual ~IItem() =  default;


    CCoord              getPosition() const { return m_position; }
    const std::string & getTextureName () const { return m_textureName; }
    int                 getWidth() const { return m_width; }
    int                 getHeight() const { return m_height; }
    double              getAngle() const { return m_angle; }
    bool                getIsPickable() const { return m_isPickable; }

    void setPosition(CCoord pos) {
        m_position = pos;
    }
    void setAngle(double angle) {
        m_angle = angle;
    }

    void setWidth(int value)  { m_width = value; }
    void setHeight(int value) { m_height = value; }
    void setIsPickable(bool value) { m_isPickable = value; }
};

using AItem = std::shared_ptr<IItem>;



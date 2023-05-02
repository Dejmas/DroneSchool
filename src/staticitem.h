#pragma once
#include <string>
#include <cmath>
#include "utils.h"
#include "item.h"

class CStaticItem : public IItem {
private:        
    
public:
    CStaticItem(const std::string & name, const std::string & textureName, CCoord pos = CCoord())
    : IItem(name, textureName, pos, 50, 50, 0)
        {}

    

};



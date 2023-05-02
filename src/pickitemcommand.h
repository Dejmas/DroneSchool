#pragma once

#include "command.h"
#include "item.h"
#include "utils.h"

class CPickItemCommand : public ICommand {

    AItem m_item;

public: 

    CPickItemCommand(AItem item) : m_item(item) {};

    virtual ~CPickItemCommand() {}

    virtual bool isDone (CDrone & drone) const override {
        return drone.getBindedItem() == m_item;
    }

    virtual void workOnIt (CRemoteControl * remote) override {
        remote->pick();
    }    

};


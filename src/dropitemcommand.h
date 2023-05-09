#pragma once

#include "command.h"
#include "item.h"
#include "utils.h"

class CDropItemCommand : public ICommand {

    AItem m_item;

public: 

    CDropItemCommand(AItem item) : m_item(item) {};

    virtual ~CDropItemCommand() {}

    virtual bool isDone (CDrone & drone) const override {
        return drone.getBindedItem() == nullptr;
    }

    virtual void workOnIt (CRemoteControl * remote) override {
        remote->pick();
    virtual void undo () override {
        // TODO:
    }

};


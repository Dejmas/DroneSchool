#pragma once

#include "command.h"
#include "item.h"
#include "utils.h"

class CDropItemCommand : public ICommand {

    AItem m_item;
    CRemoteControl * m_remoteBackup;

public: 

    CDropItemCommand(AItem item) : m_item(item) {};

    virtual ~CDropItemCommand() {}

    virtual bool isDone (CDrone & drone) const override {
        return drone.getBindedItem() == nullptr;
    }

    virtual void workOnIt (CRemoteControl * remote) override {
        remote->pick();
        m_remoteBackup = remote;
    }

    virtual void undo () override {
        m_item->setPosition(m_remoteBackup->getDronesLocation());
        m_remoteBackup->pick();
    }

};


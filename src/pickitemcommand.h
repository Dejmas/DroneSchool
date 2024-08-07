#pragma once

#include "command.h"
#include "item.h"
#include "utils.h"

class CPickItemCommand : public ICommand {

    AItem m_item;
    bool  m_started = false;
    CCoord m_itemBeginLocationBackup;
    CRemoteControl * m_remoteBackup;

public: 

    CPickItemCommand(AItem item) : m_item(item) {};

    virtual ~CPickItemCommand() {}

    virtual bool isDone (CDrone & drone) const override {
        return drone.getBindedItem() == m_item;
    }

    virtual void workOnIt (CRemoteControl * remote) override {
        if (!m_started) {
            m_started = true;
            m_itemBeginLocationBackup = m_item->getPosition();
            m_remoteBackup = remote;
        }
        remote->pick();
    }    

    virtual void undo () override {
        if (m_started) {
            m_item->setPosition(m_itemBeginLocationBackup);
            m_started = true;
            m_remoteBackup->pick();
        }
    }

};


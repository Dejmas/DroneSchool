#pragma once

#include <string>
#include <vector>
#include <deque>
#include <memory>

#include "item.h"
#include "command.h"


class CLesson
{
private:
    std::string             m_name;
    std::deque <ACommand>   m_commands;
    std::deque <ACommand>::iterator    m_commandIter;
    std::vector <AItem>     m_items;
    bool                    m_isComplete;
    IUser                 * m_user;
    CDrone                * m_drone;
    CCoord                  m_startLocation;
public:
    CLesson(const std::string & name);
    ~CLesson() = default;

    void addCommand (ACommand command);
    void addItem (AItem item);

    void setStartLocation(CCoord);
    void start(IUser *, CDrone *);
    void update();
    
    bool isComplete() const;
    const std::vector <AItem> & getItems() const { return m_items; }
};

using ALesson = std::shared_ptr<CLesson>;


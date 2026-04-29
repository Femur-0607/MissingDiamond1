#pragma once
#include "Room.h"

class ItemRequiredRoom : public Room
{
private:
    string keyItemName;
public:
    ItemRequiredRoom(const string& name, const string& keyItemName);
    ~ItemRequiredRoom();
    
    bool HasRequiredItem(const vector<unique_ptr<Item>>& inventory) const override;
};

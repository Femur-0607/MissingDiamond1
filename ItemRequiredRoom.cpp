#include "ItemRequiredRoom.h"

ItemRequiredRoom::ItemRequiredRoom(const string& name, const string& keyItemName)
    : Room(name), keyItemName(keyItemName){}

ItemRequiredRoom::~ItemRequiredRoom(){}

bool ItemRequiredRoom::HasRequiredItem(const vector<unique_ptr<Item>>& inventory) const
{
    for (const auto& item : inventory)
    {
        if (item->GetItemName() == keyItemName)
        {
            return true;
        }
    }
    return false;
}

#include <algorithm>
#include "ItemRequiredRoom.h"


ItemRequiredRoom::ItemRequiredRoom(const string& name, const string& keyItemName)
    : Room(name), keyItemName(keyItemName){}

ItemRequiredRoom::~ItemRequiredRoom(){}

bool ItemRequiredRoom::HasRequiredItem(const vector<unique_ptr<Item>>& inventory) const
{
    auto it = find_if(inventory.begin(), inventory.end(), [this](const auto& item)
    {
        return item->GetItemName() == keyItemName;
    });
    // end()가 아니라면 keyItemName과 일치하는 아이템을 찾았다는 뜻이므로 true, 못찾아서 end()까지 가면 false
    return it != inventory.end();
}

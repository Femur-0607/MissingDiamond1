#include "Item.h"
#include "ItemManager.h"

using namespace std;

Item::Item(int itemID): itemID(itemID){}

int Item::GetItemID() const
{
    return itemID;
}

const string& Item::GetItemName() const
{
    return ItemManager::GetItemInstance().GetItemData(itemID).name;
}

ItemType Item::GetItemType() const
{
    return ItemManager::GetItemInstance().GetItemData(itemID).type;
}
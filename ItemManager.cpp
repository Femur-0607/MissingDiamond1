#include "ItemManager.h"

ItemManager::ItemManager()
{
    itemDB = createItemDB();
}

const ItemData& ItemManager::GetItemData(int id)
{
    return itemDB[id];
}
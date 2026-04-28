#include "Item.h"

Item::Item(const string& itemName, const string& itemDescription, ItemType itemType)
: itemName(itemName), itemDescription(itemDescription), itemType(itemType) {}
Item::~Item() {}

const string& Item::GetItemName() const
{
    return itemName;
}

const string& Item::GetItemDescription() const
{
    return itemDescription;
}

ItemType Item::GetItemType() const
{
    return itemType;
}

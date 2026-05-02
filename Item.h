#pragma once
#include <string>

enum class ItemType { Clue, Evidence, Normal }; // 단서, 증거, 평범한 아이템

class Item
{
private:
    int itemID;
public:
    Item(int itemID);
    int GetItemID() const;
    const std::string& GetItemName() const;
    ItemType GetItemType() const;
};

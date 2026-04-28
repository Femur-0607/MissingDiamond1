#pragma once
#include <string>

using namespace std;

enum class ItemType { Clue, Evidence, Normal }; // 단서, 증거, 평범한 아이템

class Item
{
private:
    string itemName;
    string itemDescription; // 아이템 설명
    ItemType itemType;
public:
    Item(const string& itemName, const string& itemDescription, ItemType itemType);
    virtual ~Item();
    const string& GetItemName() const;
    const string& GetItemDescription() const;
    ItemType GetItemType() const;
};

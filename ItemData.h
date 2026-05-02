#include <string>
#include <unordered_map>
#include "Item.h"

struct ItemData 
{
    int id;
    std::string name;
    std::string description;
    ItemType type;
};

std::unordered_map<int, ItemData> createItemDB();
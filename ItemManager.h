#pragma once
#include <unordered_map>
#include "ItemData.h"

class ItemManager {
private:
    std::unordered_map<int, ItemData> itemDB;

    ItemManager();

    ItemManager(const ItemManager&) = delete;
    ItemManager& operator=(const ItemManager&) = delete;

public:
    static ItemManager& GetItemInstance() {
        static ItemManager instance;
        return instance;
    }

    const ItemData& GetItemData(int id);
};
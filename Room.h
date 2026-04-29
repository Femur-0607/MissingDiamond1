#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Item.h"

using namespace std;

class Room
{
protected:
    string roomName;
public:
    Room(const string& name);
    virtual ~Room() {}
    
    virtual const string& GetRoomName() { return roomName; }
    virtual void ShowSearchMessage();
    // 방 입장 가능 여부 체크 로직
    virtual bool HasRequiredItem(const vector<unique_ptr<Item>>& inventory) const {return true;};
    
};

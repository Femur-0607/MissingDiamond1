#pragma once
#include <string>

using namespace std;

class Room
{
private:
    string roomName;
    int searchCount;
public:
    Room(const string& n);
    ~Room() {}
    
    string Search(); 
    
    const string& GetRoomName() { return roomName; }
};

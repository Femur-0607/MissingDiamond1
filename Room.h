#pragma once
#include <string>

using namespace std;

class Room
{
private:
    string roomName;
public:
    Room(const string& n);
    ~Room() {}
    
    void ShowSearchMessage(); 
    
    const string& GetRoomName() { return roomName; }
};

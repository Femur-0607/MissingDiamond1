#include "Room.h"
#include <iostream>

using namespace std;

Room::Room(const string& n) : roomName(n), searchCount(0) 
{
}

// 수색 기능
string Room::Search() 
{
    searchCount++;
    cout << "\n[" << roomName << " 수색 중... (현재 " << searchCount << "회)]" << endl;
    cout << "구석구석 단서가 될 만한 것을 찾고 있다." << endl;
    
    // 수색을 3번 하면 수색 단서를 반환합니다.
    if (searchCount == 3) {
        return roomName + " 수색 단서"; 
    }
    return "";
}
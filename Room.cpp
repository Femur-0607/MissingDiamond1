#include "Room.h"
#include <iostream>
#include <vector>

#include "Item.h"

Room::Room(const string& name) : roomName(name) {}

// 수색 연출 메시지 출력
void Room::ShowSearchMessage() 
{
    cout << "구석구석 단서가 될 만한 것을 찾고 있다." << endl;
}
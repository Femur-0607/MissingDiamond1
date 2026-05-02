#include "ItemData.h"

using namespace std;

unordered_map<int, ItemData> createItemDB()
{
    // 100번대 Clue / 200번대 Evidence / 300번대 Normal
    unordered_map<int, ItemData> db;

    db[101] = { 101, "심문 단서", "심문 단서", ItemType::Clue };
    db[102] = { 102, "수색 단서", "수색 단서", ItemType::Clue };

    db[201] = { 201, "깨진 안경테", "집사 증거물", ItemType::Evidence };
    db[202] = { 202, "피 묻은 손수건", "가정부 증거물", ItemType::Evidence };
    db[203] = { 203, "찢어진 장갑", "정원사 증거물", ItemType::Evidence };

    db[301] = { 301, "열쇠", "어떤 방을 열 수 있다.", ItemType::Normal };

    return db;
}
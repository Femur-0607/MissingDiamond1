#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "ItemRequiredRoom.h"

using namespace std;

GameManager::GameManager() : currentTurn(1), guiltyPerson(nullptr) {
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < 5; ++i) rand();
}

GameManager::~GameManager(){}

void GameManager::InitializeGame() {
    rooms.clear();
    rooms.push_back(make_unique<Room>("주방"));
    rooms.push_back(make_unique<Room>("거실"));
    rooms.push_back(make_unique<ItemRequiredRoom>("회장님 집무실", "열쇠"));
    
    evidence.clear();
    evidence.push_back(make_unique<Item>("깨진 안경테","집사 증거물", ItemType::Evidence));
    evidence.push_back(make_unique<Item>("피 묻은 손수건","가정부 증거물", ItemType::Evidence));
    evidence.push_back(make_unique<Item>("찢어진 장갑","정원사 증거물", ItemType::Evidence));
    
    suspects.clear();
    int luckyNumber = rand() % 3;
    suspects.push_back(make_unique<Suspect>("집사", (luckyNumber == 0), evidence[0]->GetItemName()));
    suspects.push_back(make_unique<Suspect>("가정부", (luckyNumber == 1), evidence[1]->GetItemName()));
    suspects.push_back(make_unique<Suspect>("정원사", (luckyNumber == 2), evidence[2]->GetItemName()));
    
    guiltyPerson = suspects[luckyNumber].get();

    // 카운트 벡터 초기화
    roomSearchCounts.assign(rooms.size(), 0);
    suspectInterrogateCounts.assign(suspects.size(), 0);
    
    cout << "\n[DEBUG] 시스템: 이번 판의 진범은 [" << guiltyPerson->GetName() << "]입니다." << endl;
    cout << "[DEBUG] 증거품: " << guiltyPerson->GetEvidenceName() << endl;
    cout << "\n확인했으면 아무 키나 누르세요..." << endl;
    system("pause > nul"); 
}

void GameManager::ShowIntro() {
    system("cls");
    cout << "... 폭풍우가 치는 밤, '다이아몬드'가 사라졌습니다." << endl;
    cout << "저택 안에는 3명의 용의자가 있습니다." << endl;
    cout << "당신은 3일 안에 진범과 결정적 증거를 찾아야 합니다." << endl;
}

void GameManager::Run() {
    InitializeGame();
    ShowIntro();
    
    while (currentTurn <= maxTurns) {
        system("cls");
        ShowStatus();

        int choice = 0;
        while (true) {
            cout << "\n[행동 선택] 1. 심문  2. 수색" << endl;
            cout << "선택: ";
            if (!(cin >> choice)) {
                cin.clear(); cin.ignore(1000, '\n');
                continue;
            }
            if (choice == 1 || choice == 2) break;
            else cout << "잘못된 입력입니다. 1 또는 2를 선택하세요." << endl;
        }

        if (choice == 1) InterrogatePhase();
        else SearchPhase();
        
        CombineEvidence();
        
        bool hasFinalEvidence = false;
        for (const auto& item : inventory) {
            if (item->GetItemType() == ItemType::Evidence) {
                hasFinalEvidence = true;
                break;
            }
        }
        
        if (hasFinalEvidence) {
            cout << "\n[!] 모든 진실이 밝혀졌습니다. 범인을 지목하러 갑니다!" << endl;
            system("pause > nul");
            break;
        }

        currentTurn++;
        cout << "\n아무 키나 누르면 다음으로...";
        system("pause > nul");
    }
    
    FinalSelection();
    cout << "\n===========================================" << endl;
    cout << "게임을 종료하려면 아무 키나 누르세요..." << endl;
    system("pause > nul");
}

void GameManager::ShowStatus() {
    int day = (currentTurn - 1) / 3 + 1;
    string timeOfDay;
    int phase = currentTurn % 3;
    if (phase == 1) timeOfDay = "아침";
    else if (phase == 2) timeOfDay = "점심";
    else timeOfDay = "저녁";
    
    cout << "-------------------------------------------" << endl;
    cout << " 현재 시간: " << day << "일차 (" << timeOfDay << ")" << endl;
    cout << " 인벤토리: ";
    if (inventory.empty()) cout << "비어 있음";
    for (const unique_ptr<Item>& item : inventory) cout << "[" << item->GetItemName() << "] ";
    cout << "\n-------------------------------------------" << endl;
}

void GameManager::InterrogatePhase() {
    cout << "\n누구를 심문하시겠습니까?" << endl;
    for (int i = 0; i < suspects.size(); ++i) {
        cout << i + 1 << ". " << suspects[i]->GetName() << "  ";
    }
    
    int target;
    if (!(cin >> target) || target < 1 || target > suspects.size()) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "잘못된 선택입니다." << endl;
        return;
    }
    
    int idx = target - 1;
    suspectInterrogateCounts[idx]++;
    
    cout << "\n[" << suspects[idx]->GetName() << " 심문 중... (현재 " << suspectInterrogateCounts[idx] << "회)]" << endl;
    suspects[idx]->Interrogate();
    
    if (suspectInterrogateCounts[idx] == 2 && suspects[idx]->IsGuilty()) {
        string itemName = suspects[idx]->GetName() + " 심문 단서";
        cout << "\n[!] " << suspects[idx]->GetName() << "에게서 [" << itemName << "]를 발견했습니다!" << endl;
        inventory.push_back(make_unique<Item>(itemName, itemName, ItemType::Clue));
    }
}

void GameManager::SearchPhase() {
    cout << "\n어디를 수색하시겠습니까?" << endl;
    for (int i = 0; i < rooms.size(); ++i) {
        cout << i + 1 << ". " << rooms[i]->GetRoomName() << "  ";
    }

    int target;
    if (!(cin >> target) || target < 1 || target > rooms.size()) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "잘못된 선택입니다." << endl;
        return;
    }
    
    int idx = target - 1;
    Room* selectedRoom = rooms[idx].get();
    
    if (selectedRoom->HasRequiredItem(inventory) == true) {
        cout << "방에 입장하여 수색을 시작합니다!" << endl;
    }
    else
    {
        cout << "방 문이 닫혀있어 입장하지 못하였습니다." << endl;
        cout << "열쇠가 필요할꺼 같습니다." << endl;
        return;
    }
    
    roomSearchCounts[idx]++;
    
    cout << "\n[" << rooms[idx]->GetRoomName() << " 수색 중... (현재 " << roomSearchCounts[idx] << "회)]" << endl;
    rooms[idx]->ShowSearchMessage();
    
    if (target == 2) // 거실 수색 시
    {
        inventory.push_back(make_unique<Item>("열쇠", "어떤 방을 열 수 있다.", ItemType::Normal));
        cout << "\n[!] " << rooms[idx]->GetRoomName() << "에서 [" << "열쇠" << "]를 발견했습니다!" << endl;
    }
    
    if (roomSearchCounts[idx] == 3) {
        string itemName = rooms[idx]->GetRoomName() + " 수색 단서";
        cout << "\n[!] " << rooms[idx]->GetRoomName() << "에서 [" << itemName << "]를 발견했습니다!" << endl;
        inventory.push_back(make_unique<Item>(itemName, itemName, ItemType::Clue));
    }
}

void GameManager::CombineEvidence() {
    string targetEvidence = guiltyPerson->GetEvidenceName();
    int clueCount = 0;
    for (const auto& item : inventory) {
        if (item->GetItemType() == ItemType::Evidence) return;
        if (item->GetItemType() == ItemType::Clue) clueCount++;
    }

    if (clueCount >= 2) {
        cout << "\n===========================================" << endl;
        cout << " [추리 시작] 흩어진 정보들이 하나로 모입니다..." << endl;
        
        int evidenceIdx = -1;
        if (targetEvidence == "깨진 안경테") evidenceIdx = 0;
        else if (targetEvidence == "피 묻은 손수건") evidenceIdx = 1;
        else if (targetEvidence == "찢어진 장갑") evidenceIdx = 2;

        if (evidenceIdx != -1) {
            if (evidenceIdx == 0) cout << " '안경을 잃어버렸다'는 집사의 말과 수색 중 발견한 유리 조각..." << endl;
            else if (evidenceIdx == 1) cout << " 가정부의 다친 손과 현장에 떨어진 천 조각의 무늬가 일치합니다!" << endl;
            else if (evidenceIdx == 2) cout << " 정원사가 잃어버렸다던 장갑 한 쪽이 여기서 발견되는군요." << endl;
            
            inventory.push_back(move(evidence[evidenceIdx]));
            cout << " [!] 결정적 증거 [" << targetEvidence << "]를 확보했습니다!" << endl;
        }
        cout << "===========================================\n" << endl;
    }
}

void GameManager::FinalSelection() {
    system("cls");
    cout << "===========================================" << endl;
    cout << "              최종 지목의 시간             " << endl;
    cout << "===========================================" << endl;
    cout << "당신이 생각하는 진범은 누구입니까?\n" << endl;
    
    for (int i = 0; i < suspects.size(); ++i) {
        cout << i + 1 << ". " << suspects[i]->GetName() << endl;
    }
    
    int choice = 0;
    while (true) {
        cout << "\n범인 선택 (번호 입력): ";
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n');
            continue;
        }
        if (choice >= 1 && choice <= suspects.size()) break;
        cout << "존재하지 않는 번호입니다!" << endl;
    }
    
    Suspect* picked = suspects[choice - 1].get();
    system("cls");
    cout << "...당신은 " << picked->GetName() << "을(를) 진범으로 지목했습니다." << endl;
    
    if (picked->IsGuilty()) {
        cout << "\n[정답!] " << picked->GetName() << "이(가) 진짜 범인이었습니다!" << endl;
    } else {
        cout << "\n[오답!] " << picked->GetName() << "은(는) 범인이 아니었습니다..." << endl;
    }
}

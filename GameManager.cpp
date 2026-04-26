#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

GameManager::GameManager() : currentTurn(1) {
    // 현재 시간으로 시드 설정
    srand(static_cast<unsigned int>(time(NULL)));
    
    // 시드 설정 직후 첫 번째 숫자가 비슷하게 나오는 현상을 방지합니다.
    for (int i = 0; i < 5; ++i) {
        rand();
    }
}

GameManager::~GameManager(){
}

void GameManager::InitializeGame() {
    // 1. 장소 생성
    rooms.push_back(new Room("주방"));
    rooms.push_back(new Room("거실"));
    rooms.push_back(new Room("회장님 집무실"));

    // 2. 용의자 생성 (3명 중 1명만 무작위 범인)
    int luckyNumber = rand() % 3;
    string evidenceList[] = { "깨진 안경테", "피 묻은 손수건", "찢어진 장갑" };
    
    suspects.push_back(new Suspect("집사", (luckyNumber == 0), evidenceList[0]));
    suspects.push_back(new Suspect("가정부", (luckyNumber == 1), evidenceList[1]));
    suspects.push_back(new Suspect("정원사", (luckyNumber == 2), evidenceList[2]));
    
    guiltyPerson = suspects[luckyNumber];
    
    // ================= [개발자 디버그 모드 추가] =================
    // 게임 시작 시 범인이 잘 바뀌는지 확인하기 위한 용도입니다.
    cout << "\n[DEBUG] 시스템: 이번 판의 진범은 [" << guiltyPerson->GetName() << "]입니다." << endl;
    cout << "[DEBUG] 증거품: " << guiltyPerson->GetEvidenceName() << endl;
    cout << "\n확인했으면 아무 키나 누르세요..." << endl;
    system("pause > nul"); 
    // ============================================================
}

void GameManager::ShowIntro() {
    system("cls");
    cout << "... 폭풍우가 치는 밤, '다이아몬드'가 사라졌습니다.";
    cout << "저택 안에는 3명의 용의자가 있습니다.";
    cout << "당신은 3일 안에 진범과 결정적 증거를 찾아야 합니다.";
}

void GameManager::Run() {
    InitializeGame();
    ShowIntro();
    
    while (currentTurn <= maxTurns) {
        system("cls");
        ShowStatus();

        int choice = 0;
        // 올바른 입력이 들어올 때까지 무한 반복
        while (true) {
            cout << "\n[행동 선택] 1. 심문  2. 수색" << endl;
            cout << "선택: ";
            
            // choice는 int값으로 char이 들어오면 false지만 !로 true가 되서 밑에 예외처리 실행
            if (!(cin >> choice)) {
                cin.clear(); // 에러 플래그 초기화
                cin.ignore(1000, '\n'); // 버퍼 비우기
                cout << "숫자로 입력해주세요!" << endl;
                continue;
            }
            
            // choice 입력값은 그대로 담아져 있어서 값을 비교함
            if (choice == 1 || choice == 2) break; // 1이나 2면 통과
            else cout << "잘못된 입력입니다. 1 또는 2를 선택하세요." << endl;
        }

        if (choice == 1) InterrogatePhase();
        else SearchPhase();
        
        CombineEvidence();
        
        auto it = find(inventory.begin(), inventory.end(), guiltyPerson->GetEvidenceName());
        if (it != inventory.end()) {
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
    system("pause > nul");;
}

void GameManager::ShowStatus() {
    // 1일차, 2일차, 3일차 계산
    int day = (currentTurn - 1) / 3 + 1;
    
    // 아침, 점심, 저녁 계산
    string timeOfDay;
    int phase = currentTurn % 3;
    if (phase == 1) timeOfDay = "아침";
    else if (phase == 2) timeOfDay = "점심";
    else timeOfDay = "저녁"; // 나머지가 0일 때
    
    cout << "-------------------------------------------" << endl;
    cout << " 현재 시간: " << day << "일차 (" << timeOfDay << ")" << endl;
    cout << " 인벤토리: ";
    if (inventory.empty()) cout << "비어 있음";
    for (const string& item : inventory) cout << "[" << item << "] ";
    cout << "\n-------------------------------------------" << endl;
}

// 심문 기능
void GameManager::InterrogatePhase() {
    cout << "\n누구를 심문하시겠습니까?" << endl;
    for (int i = 0; i < suspects.size(); ++i) {
        cout << i + 1 << ". " << suspects[i]->GetName() << "  ";
    }
    
    int target;
    cin >> target;
    if (target >= 1 && target <= suspects.size()) {
        suspects[target - 1]->Interrogate();
        
        // 심문 후 증거 획득 조건 체크
        string item = suspects[target - 1]->CheckEvidence();
        if (!item.empty() && find(inventory.begin(), inventory.end(), item) == inventory.end()) {
            cout << "\n[!] " << suspects[target - 1]->GetName() << "에게서 [" << item << "]를 발견했습니다!" << endl;
            inventory.push_back(item);
        }
    }
}

void GameManager::SearchPhase() 
{
    cout << "\n어디를 수색하시겠습니까?" << endl;
    for (int i = 0; i < rooms.size(); ++i) 
    {
        cout << i + 1 << ". " << rooms[i]->GetRoomName() << "  ";
    }

    int target;
    cin >> target;
    if (target >= 1 && target <= rooms.size())
    {
        string item = rooms[target - 1]->Search();
    
        if (!item.empty() && find(inventory.begin(), inventory.end(), item) == inventory.end())
        {
            cout << "\n[!] " << rooms[target - 1]->GetRoomName() << "에서 [" << item << "]를 발견했습니다!" << endl;
            inventory.push_back(item);
        }
    }
}

void GameManager::FinalSelection()
{
    system("cls");
    cout << "===========================================" << endl;
    cout << "              최종 지목의 시간             " << endl;
    cout << "===========================================" << endl;
    cout << "3일의 시간이 모두 지났습니다." << endl;
    cout << "당신이 생각하는 진범은 누구입니까?\n" << endl;
    
    // 1. 용의자 목록 보여주기
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
    
    // 2. 결과 판정하기
    if (choice >= 1 && choice <= suspects.size()) {
        Suspect* picked = suspects[choice - 1];
        
        system("cls");
        cout << "...당신은 " << picked->GetName() << "을(를) 진범으로 지목했습니다." << endl;
        
        if (picked->IsGuilty()) {
            cout << "\n[정답!] " << picked->GetName() << "이(가) 진짜 범인이었습니다!" << endl;
            cout << "사건을 무사히 해결했습니다! (승리)" << endl;
        } else {
            cout << "\n[오답!] " << picked->GetName() << "은(는) 범인이 아니었습니다..." << endl;
            cout << "진범은 유유히 빠져나갔습니다. (패배)" << endl;
        }
    } else {
        cout << "잘못된 선택입니다. 진범을 놓쳤습니다! (패배)" << endl;
    }
}
    
void GameManager::CombineEvidence()
{
    string targetEvidence = guiltyPerson->GetEvidenceName();
    
    int interrogateCount = 0;
    int searchCount = 0;

    for (const string& item : inventory) {
        // string::npos는 "그런 단어 못 찾았음!"이라는 뜻입니다.
        // 즉, npos가 아니라는 건 단어를 성공적으로 찾았다는 뜻입니다.
        if (item.find("심문 단서") != string::npos) interrogateCount++;
        if (item.find("수색 단서") != string::npos) searchCount++;
    }

    // 심문 단서 1개, 수색 단서 1개 이상 모이면 조합
    if (interrogateCount >= 1 && searchCount >= 1) {
        cout << "\n===========================================" << endl;
        cout << " [추리 시작] 흩어진 정보들이 하나로 모입니다..." << endl;
    
        // 범인에 따른 추리 대사
        if (targetEvidence == "깨진 안경테") {
            cout << " '안경을 잃어버렸다'는 집사의 말과 수색 중 발견한 유리 조각..." << endl;
        } 
        else if (targetEvidence == "피 묻은 손수건") {
            cout << " 가정부의 다친 손과 현장에 떨어진 천 조각의 무늬가 일치합니다!" << endl;
        }
        else if (targetEvidence == "찢어진 장갑") {
            cout << " 정원사가 잃어버렸다던 장갑 한 쪽이 여기서 발견되는군요." << endl;
        }

        cout << " [!] 결정적 증거 [" << targetEvidence << "]를 확보했습니다!" << endl;
        cout << "===========================================\n" << endl;
    
        inventory.push_back(targetEvidence);
    }
}
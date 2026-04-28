#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Suspect.h"
#include "Room.h"

using namespace std;

class GameManager {
private:
    vector<unique_ptr<Suspect>> suspects;   // 용의자 목록
    vector<unique_ptr<Room>> rooms; // 장소 목록
    vector<string> inventory;   // 획득한 증거물 저장소
    Suspect* guiltyPerson;  // 진범을 담는 변수
    
    int currentTurn;
    const int maxTurns = 9; // 3일(아침, 점심, 저녁)

public:
    GameManager();
    ~GameManager();

    void InitializeGame();           // 게임 초기 세팅 (용의자, 범인 설정)
    void Run();                      // 메인 게임 루프
    
private:
    void ShowIntro();                // 인트로 연출
    void ShowStatus();               // 현재 턴 및 상황 출력
    void InterrogatePhase();         // 심문 단계
    void SearchPhase();              // 수색 단계
    void FinalSelection();           // 최종 범인 지목
    void CombineEvidence();          // 단서 조합 로직 추가
};
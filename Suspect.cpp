#include "Suspect.h"
#include <iostream>

using namespace std;

Suspect::Suspect(const string& name, bool guilty, const string& evidence)
    : Person(name), isGuilty(guilty), evidenceName(evidence) 
{
    if (name == "집사") {
        dialogueList.push_back("전 평생을 회장님 곁에서 보냈습니다. 제가 왜 그런 짓을 하겠습니까?");
        dialogueList.push_back("아이쿠... 눈이 침침하군요. 제 금테 안경을 혹시 못 보셨습니까?");
    }
    else if (name == "가정부") {
        dialogueList.push_back("전 그 시간에 지하실에서 빨래를 하고 있었어요. 정말이에요!");
        dialogueList.push_back("손을 베어서 손수건으로 감싸두었는데... 그게 어디로 갔을까요?");
    }
    else if (name == "정원사") {
        dialogueList.push_back("난 밤새 정원 창고에 있었소. 비가 와서 도구들을 정리하느라 바빴지.");
        dialogueList.push_back("장미 가시 때문에 장갑이 찢어졌지 뭐요. 그런데 한 쪽이 보이질 않네.");
    }
}

// 취조 기능: 대사만 출력
void Suspect::Interrogate() {
    int randomIndex = rand() % dialogueList.size();
    cout << name << " : \"" << dialogueList[randomIndex] << "\"" << endl; 
}

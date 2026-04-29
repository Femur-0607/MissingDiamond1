#pragma once
#include "Person.h"
#include <vector>
#include <string>

using namespace std;

class Suspect : public Person
{
private:
    vector<string> dialogueList;    // 대사 목록
    bool isGuilty;  // 진범 여부
    string evidenceName;    // 가지고 있는 단서 이름
public:
    Suspect(const string& name, bool guilty, const string& evidence);
    ~Suspect();
    
    void Interrogate() override;
    
    // 진범인지 확인하는 함수
    bool IsGuilty() const { return isGuilty; }
    
    // 진범의 결정적 증거를 확인하는 함수
    string GetEvidenceName() const { return evidenceName; }
};

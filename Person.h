#pragma once
#include <string>

using namespace std;

class Person
{
protected:
    string name;
    
public:
    Person(const string& name) : name(name) {}
    virtual ~Person() {}
    
    string GetName() const { return name; }
    
    // 심문 메서드
    virtual void Interrogate()  = 0;
};

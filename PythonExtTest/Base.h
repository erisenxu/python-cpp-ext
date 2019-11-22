
#ifndef BASE_H
#define BASE_H

#include <string>
using namespace std;

class Base
{
protected:
    string m_sName;
public:
    Base(const string& sName="") : m_sName(sName) {}
    virtual ~Base() {}
    void SetName(const string& sName="") {m_sName = sName;}
    virtual const string& GetName() const {return m_sName;}
    virtual string GetName() {return m_sName;}
};

#endif


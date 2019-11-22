
#ifndef OTHER_H
#define OTHER_H

#include <string>
using namespace std;

class Other
{
protected:
    string m_sName;
public:
    Other(const string& sName="") : m_sName(sName) {}
    virtual ~Other() {}
    void SetName(const string& sName="") {m_sName = sName;}
    virtual const string& GetName() const {return m_sName;}
    virtual string GetName() {return m_sName;}
};

#endif


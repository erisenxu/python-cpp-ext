
#ifndef SUB_CLASS_H
#define SUB_CLASS_H

#include "Base.h"
#include "Other.h"

class SubClass : public Base
{
protected:
    int m_iValue;
    Other* m_pOther;
public:
    SubClass(const string& sName = "", int iValue = 0) : Base(sName), m_iValue(iValue), m_pOther(NULL) {}
    ~SubClass() {}
    void SetValue(int iValue) {m_iValue = iValue;}
    int GetValue() const {return m_iValue;}
    void SetOther(Other* pOther) {m_pOther = pOther;}
    Other* GetOther() {return m_pOther;}
};

#endif


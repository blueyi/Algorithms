/*
 * operator=.cpp
 * Copyright (C) 2016 blueyi <blueyi@blueyi-lubuntu>
 *
 * Distributed under terms of the MIT license.
 */
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <utility>

class CMyString {
public:
    friend void swap(CMyString&, CMyString&);
    CMyString() = default;
    CMyString(const std::string &str);
    CMyString(const CMyString& str);
//    CMyString& operator=(const CMyString& rhs);
    CMyString& operator=(const CMyString rhs);
    char* get() const { return m_pdata; }
    ~CMyString(void);
private:
    char *m_pdata;
};

CMyString::CMyString(const CMyString& str)
{
    m_pdata = new char[sizeof(str.get()) / sizeof(char) + 1];
    std::strcpy(m_pdata, str.get());
}

CMyString::CMyString(const std::string &str)
{
    m_pdata = new char[str.length() + 1];
    std::strcpy(m_pdata, str.c_str());
}

CMyString::~CMyString()
{
    delete[] m_pdata;
}

//对于自赋值效率更高，但无法保证异常安全
/*
CMyString& CMyString::operator=(const CMyString& rhs)
{
    if (this != &rhs) {
        CMyString trhs(rhs);
        char *t_mdata = trhs.m_pdata;
        trhs.m_pdata = m_pdata;
        m_pdata = t_mdata;
    }
    return *this;
}
*/

//可以成员类的私有成员函数，省去this指针的传递
inline void swap(CMyString  &lhs, CMyString &rhs)
{
    std::swap(lhs.m_pdata, rhs.m_pdata);
}

//可以保证异常安全，但自赋值效率较低
CMyString& CMyString::operator=(CMyString rhs)
{
    swap(*this, rhs);
    return *this;
}

int main(void)
{
    char cs[] = "I love china!";
    CMyString str1(cs);
    std::string tstr = "I love dlut!";
    CMyString str2(tstr);
    std::cout << "str1: " << str1.get() << std::endl;
    std::cout << "str2: " << str2.get() << std::endl;
    CMyString temp(str1);
    str1 = str2;
    str2 = temp;
    std::cout << "str1: " << str1.get() << std::endl;
    std::cout << "str2: " << str2.get() << std::endl;
    return 0;
}

/*
 * BigNum.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 * Support big integer number + - * /
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <fstream>
#include <chrono>

#define NDEBUG

template <typename T>
std::ostream& DEBUG(const T& t, const std::string &msg = "DEBUG", std::ostream& os = std::cout)
{
    os << "=" << msg << "=" << t << "==" << std::endl;
    return os;
}
std::ostream& DEBUG(const std::vector<uint32_t> &vec, const std::string &msg = "DEBUG", std::ostream& os = std::cout)
{
    os << "=" << msg << "=" ;
    for (auto v : vec)
        os << std::setw(4) << std::setfill('0') << v << " ";
    os << "==" << std::endl;
    return os;
}



//按10000进制划分数字，因为相乘后的10^8不会越界
const int DEC = 4; 

//10进制码表，以快速计算10^n
//由于使用int最多只能存到10^9，够用了
int quick_pow10(int n)
{
    static int pow10[10] = {
        1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
        100000000, 1000000000 
    };
    return pow10[n];
}


//比较含整型vector的大小
int vcompare(const std::vector<uint32_t>&, const std::vector<uint32_t>&);

class BigInt {
public:
    friend bool operator>(const BigInt&, const BigInt&);
    friend bool operator<(const BigInt&, const BigInt&);
    friend bool operator==(const BigInt&, const BigInt&);
    friend bool operator!=(const BigInt&, const BigInt&);
    // 存有正整数的vec相加
    friend std::vector<uint32_t> vadd(const std::vector<uint32_t> &, const std::vector<uint32_t> &);
    // 存有正整数的vec相减，大减小，lsh - rhs
    friend std::vector<uint32_t> vsub(const std::vector<uint32_t> &, const std::vector<uint32_t> &);
    // 存有正整数的vec相乘
    friend std::vector<uint32_t> vmul(const std::vector<uint32_t> &, const std::vector<uint32_t> &);


    BigInt() : negative(false), zero(true) { vnum.push_back(0); }
    BigInt(const std::string &);
    BigInt(const BigInt&);
    BigInt& operator=(const BigInt&);
    //负加负、负加正、正加负转化为正减负
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    ~BigInt() = default;

//    void setnegative(bool ne) { negative = ne; }
//    void setzero(bool ze) { zero = ze; }
//    bool getnegative() const { return negative; }
//    bool getzero() const { return zero; }
//    void setvnum(const std::vector<uint32_t> num) { vnum = num; setzero(false); }
    std::ostream& print(std::ostream& os = std::cout) const;

    //将string按n位一组划分为整型，存入vector
    void strtovec(std::vector<uint32_t> &, const std::string &, const int n);

private:
    std::vector<uint32_t> vnum;  //存放读取的数字
    bool negative;  //是否为负数
    bool zero;
    int ctoi(char ch) { return (ch - '0'); }  //字符转整型
    char itoc(int i) { return (i + '0'); }  //整数转字符
    uint32_t strtoi(const std::string &str);  //字符串转整型
};

int vcompare(const std::vector<uint32_t>&lhs, const std::vector<uint32_t>&rhs)
{
    if (lhs.size() > rhs.size())
        return 1;

    if (lhs.size() < rhs.size()) 
        return -1;

    for (std::vector<uint32_t>::size_type i = 0; i < lhs.size(); ++i) {
        if ( lhs[i] > rhs[i] )
            return 1;
        else if ( lhs[i] < rhs[i] )
            return -1;
    }

    return 0;
}


bool operator>(const BigInt&lhs, const BigInt&rhs)
{
    const std::vector<uint32_t> &lhsv = lhs.vnum;
    const std::vector<uint32_t> &rhsv = rhs.vnum;
/*
#ifndef NDEBUG
    DEBUG(lhs, "lhs");
    DEBUG(rhs, "rhs");
#endif
*/
    if (lhs.negative && ((!rhs.negative) || rhs.zero))
        return false;

    if (!lhs.negative && rhs.negative)
        return true;

    if ((lhs.negative && rhs.negative) || (!lhs.negative && !rhs.negative)) {
/*
#ifndef NDEBUG
        DEBUG(vcompare(lhsv, rhsv), "vcom");
#endif
*/
        int vcom = vcompare(lhsv, rhsv);
        if (vcom == 1) {
            if (!lhs.negative)
                return true;
            else
                return false;
        }
        else if (vcom == -1) {
            if (lhs.negative)
                return true;
            else
                return false;
        }

    }
    return false;
}

bool operator<(const BigInt&lhs, const BigInt&rhs)
{
    const std::vector<uint32_t> &lhsv = lhs.vnum;
    const std::vector<uint32_t> &rhsv = rhs.vnum;
    if (lhs.negative && (!rhs.negative || rhs.zero))
        return true;

    if (!lhs.negative && rhs.negative)
        return false;

    if ((lhs.negative && rhs.negative) || (!lhs.negative && !rhs.negative)) {
       int vcom = vcompare(lhsv, rhsv);
        if (vcom == -1) {
            if (!lhs.negative)
                return true;
            else
                return false;
        }
        else if (vcom == 1) {
            if (lhs.negative)
                return true;
            else
                return false;
        }
    }
    return false;
}

bool operator==(const BigInt&lhs, const BigInt&rhs)
{
    if (lhs.zero && rhs.zero)
        return true;
    if (lhs.negative == rhs.negative && vcompare(lhs.vnum, rhs.vnum) == 0)
        return true;
    return false;
}

bool operator!=(const BigInt&lhs, const BigInt&rhs)
{
    return (lhs == rhs);
}

uint32_t BigInt::strtoi(const std::string &str)
{
    uint32_t uin = 0;
    for (auto c : str) {
        uin = uin * 10 + ctoi(c);
    }
    return uin;
}

void BigInt::strtovec(std::vector<uint32_t> &vec, const std::string &str, const int n = DEC)
{
    std::string::size_type s_length = str.length();
    int first_item_length = s_length % n;
    if (first_item_length != 0) {
        std::string fir_str = str.substr(0, first_item_length);
        vec.push_back(strtoi(fir_str));
    }
    for (std::string::size_type sec = first_item_length; sec < s_length; sec += n) {
        std::string sstr = str.substr(sec, n);
        vec.push_back(strtoi(sstr));
    }
}

BigInt::BigInt(const std::string &str)
{
    negative = false;
    zero = false;
    std::string tstr = str;
    if (str[0] == '-') {
        negative = true;
        tstr = str.substr(1, str.length());
    }
    else if (str[0] == '+') {
        tstr = str.substr(1, str.length());
    }

    if (tstr.find_first_not_of("0123456789") != std::string::npos || tstr.empty()) {
        throw std::runtime_error("Non-number detected!");
    }

    std::string::size_type nzeropos = tstr.find_first_not_of("0");
    if (nzeropos == std::string::npos) {
        negative = false;
        zero = true;
        vnum.push_back(0);
    }
    else {
        tstr = tstr.substr(nzeropos, tstr.length());
        strtovec(vnum, tstr, DEC);
    }
}

BigInt::BigInt(const BigInt& rhs)
{
    negative = rhs.negative; 
    zero = rhs.zero;
    vnum = rhs.vnum;
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
    if (this != &rhs) {
        negative = rhs.negative; 
        zero = rhs.zero;
        vnum = rhs.vnum;
    }
    return *this;
}

std::ostream& BigInt::print(std::ostream& os) const
{
    if (zero) {
        os << 0 << std::endl;
        return os;
    }

    if (negative)
        os << '-';

    bool first_nozero = false;  //从第一个非0开始输出
    for (std::vector<uint32_t>::size_type i = 0; i < vnum.size(); ++i) {
        if (vnum[i] != 0 )
            first_nozero = true;

        if (i != 0 && first_nozero)
            os << std::setw(4) << std::setfill('0') << vnum[i];
        else if (first_nozero || i == (vnum.size() - 1))
            os << vnum[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const BigInt& num)
{
    num.print(os);
    return os;
}

std::istream& operator>>(std::istream& os, BigInt& num)
{
    std::string str;
    os >> str;
    num = BigInt(str);
    return os;
}

std::vector<uint32_t> vadd(const std::vector<uint32_t> &lhs, const std::vector<uint32_t> &rhs)
{
    std::vector<uint32_t> lvnum(lhs);
    std::vector<uint32_t> rvnum(rhs);
    std::reverse(lvnum.begin(), lvnum.end());
    std::reverse(rvnum.begin(), rvnum.end());

    std::vector<uint32_t> &long_vec = rvnum;
    std::vector<uint32_t> &short_vec = lvnum;

    if (rvnum.size() < lvnum.size()) {
        std::swap(long_vec, short_vec);
    } 

    /*
#ifndef NDEBUG
    DEBUG(long_vec, "lvec");
    DEBUG(short_vec, "svec");
#endif
*/

    int carry = 0;
    std::vector<uint32_t> resvnum;
    std::vector<uint32_t>::size_type sindex = 0;
    int pow = quick_pow10(DEC);

    for (; sindex < short_vec.size(); ++sindex) {
        uint32_t res = long_vec[sindex] + short_vec[sindex] + carry;
        resvnum.push_back(res % pow);
        carry = res / pow;
    }
    for (; sindex < long_vec.size(); ++sindex) {
        uint32_t res = long_vec[sindex] + carry;
        resvnum.push_back(res % pow);
        carry = res / pow;
    }
    if (carry != 0)
        resvnum.push_back(carry);

    std::reverse(resvnum.begin(), resvnum.end());
    return resvnum;
}

std::vector<uint32_t> vadd_reverse(const std::vector<uint32_t> &lhs, const std::vector<uint32_t> &rhs)
{
    std::vector<uint32_t> lvnum(lhs);
    std::vector<uint32_t> rvnum(rhs);

    std::vector<uint32_t> &long_vec = rvnum;
    std::vector<uint32_t> &short_vec = lvnum;

    if (rvnum.size() < lvnum.size()) {
        std::swap(long_vec, short_vec);
    } 

    /*
#ifndef NDEBUG
    DEBUG(long_vec, "lvec");
    DEBUG(short_vec, "svec");
#endif
*/

    int carry = 0;
    std::vector<uint32_t> resvnum;
    std::vector<uint32_t>::size_type sindex = 0;
    int pow = quick_pow10(DEC);

    for (; sindex < short_vec.size(); ++sindex) {
        uint32_t res = long_vec[sindex] + short_vec[sindex] + carry;
        resvnum.push_back(res % pow);
        carry = res / pow;
    }
    for (; sindex < long_vec.size(); ++sindex) {
        uint32_t res = long_vec[sindex] + carry;
        resvnum.push_back(res % pow);
        carry = res / pow;
    }
    if (carry != 0)
        resvnum.push_back(carry);

    return resvnum;
}



std::vector<uint32_t> vsub(const std::vector<uint32_t> &lhs, const std::vector<uint32_t> &rhs)
{
    std::vector<uint32_t> lvnum(lhs);
    std::vector<uint32_t> rvnum(rhs);
    std::reverse(lvnum.begin(), lvnum.end());
    std::reverse(rvnum.begin(), rvnum.end());

    int carry = 0;
    std::vector<uint32_t> resvnum;
    std::vector<uint32_t>::size_type sindex = 0;
    int pow = quick_pow10(DEC);
        
    for (; sindex < rvnum.size(); ++sindex) {
        uint32_t res = 0;
        if (lvnum[sindex] < rvnum[sindex]) {
            res = lvnum[sindex] - carry + pow - rvnum[sindex];
            carry = 1;
        }
        else if (lvnum[sindex] == rvnum[sindex]) {
            if (carry == 1) {
                res = lvnum[sindex] - carry + pow - rvnum[sindex];
                carry = 1;
            }
            else {
                res = lvnum[sindex] - rvnum[sindex];
                carry = 0;
            }
        }
        else {
            res = lvnum[sindex] - carry - rvnum[sindex];
            carry = 0;
        }

        resvnum.push_back(res);
    }

    for (; sindex < lvnum.size(); ++sindex) {
        uint32_t res = 0;
        if (lvnum[sindex] == 0 && carry == 1) {
            res = lvnum[sindex] + pow - carry;
        }
        else {
            res = lvnum[sindex] - carry;
            carry = 0;
        }
        resvnum.push_back(res);
    }

    std::reverse(resvnum.begin(), resvnum.end());
    return resvnum;

}


std::vector<uint32_t> vmul(const std::vector<uint32_t> &lhs, const std::vector<uint32_t> &rhs)
{
    std::vector<uint32_t> lvnum(lhs);
    std::vector<uint32_t> rvnum(rhs);
    std::reverse(lvnum.begin(), lvnum.end());
    std::reverse(rvnum.begin(), rvnum.end());

    std::vector<uint32_t> &long_vec = rvnum;
    std::vector<uint32_t> &short_vec = lvnum;

    if (rvnum.size() < lvnum.size()) {
        std::swap(long_vec, short_vec);
    } 

    std::vector<uint32_t> resvnum{0};
    std::vector<uint32_t>::size_type sindex = 0, lindex = 0;
    int pow = quick_pow10(DEC);

    for (; sindex < short_vec.size(); ++sindex) {
        std::vector<uint32_t> resv;
        uint32_t carry = 0;
        std::vector<uint32_t>::size_type i = 0;
        while (i++ < sindex) {
            resv.push_back(0);
        }
        for (lindex = 0; lindex < long_vec.size(); ++lindex) {
            uint32_t res = long_vec[lindex] * short_vec[sindex] + carry;
            resv.push_back(res % pow);
            carry = res / pow;
        }

        if (carry != 0)
            resv.push_back(carry);

#ifndef NDEBUG
        DEBUG(resv, "resv");
        DEBUG(carry, "carry");
        DEBUG(resvnum, "resvnum");
#endif

        resvnum = vadd_reverse(resvnum, resv);
    }

    std::reverse(resvnum.begin(), resvnum.end());
    return resvnum;
}



BigInt BigInt::operator+(const BigInt&rhs) const
{
    if (rhs.zero)
        return *this;
    if (this->zero)
        return rhs;

    BigInt res;

    res.vnum = vadd(this->vnum, rhs.vnum);  //正加正
    res.zero = false;

    if (negative && rhs.negative) { // 负加负
        res.negative = true;
    }
    else if (negative && !rhs.negative) { //负加正
        BigInt lhs(*this);
        lhs.negative = false;
        res = rhs - lhs;
    }
    else if (!negative && rhs.negative) { //正加负
        BigInt rrhs(rhs);
        rrhs.negative = false;
        res = *this - rrhs;
    }

    return res;
}

BigInt BigInt::operator-(const BigInt&rhs) const
{
    BigInt res;

    if (rhs.zero)
        return *this;

    if (this->zero) {
        res = *this;
        res.negative = !negative;
        if (rhs.zero)
            res.zero = true;
        return res;
    }

    std::vector<uint32_t> long_vec, short_vec;

    if (vcompare(this->vnum, rhs.vnum) == -1) {
        long_vec = rhs.vnum;
        short_vec = this->vnum;
        res.negative = true;
    }
    else {
        long_vec = this->vnum;
        short_vec = rhs.vnum;
    }

    res.vnum = vsub(long_vec, short_vec);
    res.zero = false;

    if (negative && rhs.negative) { // 负减负
        res.negative = !res.negative;
    }
    else if (negative && !rhs.negative) { //负减正
        res.negative = true;
        res.vnum = vadd(vnum, rhs.vnum);
    }
    else if (!negative && rhs.negative) { //正减负
        res.negative = false;
        res.vnum = vadd(vnum, rhs.vnum);
    }

    return res;
}

BigInt BigInt::operator*(const BigInt&rhs) const
{
    BigInt res;
    if (rhs.zero || this->zero) {
        return res;
    }

    res.vnum = vmul(this->vnum, rhs.vnum);  //正乘正，负乘负
    res.zero = false;

    if ((negative && !rhs.negative) || (!negative && rhs.negative)) { //负乘正，正乘负
        res.negative = true;
    }

    return res;
}

BigInt BigInt::operator/(const BigInt&rhs) const
{
    BigInt res;

    return res;
}

BigInt cacBigInt(const std::string &str)
{
    std::istringstream is(str);
    char op;
    BigInt lnum, rnum, res;
    is >> lnum >> op >> rnum;
    /*
#ifndef NDEBUG
DEBUG(lnum);
DEBUG(op);
DEBUG(rnum);
#endif
*/
    switch(op) {
        case '+':
            res = lnum + rnum; break;
        case '-':
            res = lnum - rnum; break;
        case '*':
            res = lnum * rnum; break;
        case '/':
            res = lnum / rnum; break;
    }
    return res;
}

int main(void)
{
    std::ifstream inf("cal.txt");
    std::string line;
    while (std::getline(inf, line) && !line.empty()) {
        std::cout << "==" << std::endl;
        auto t_start = std::chrono::high_resolution_clock::now();

        std::cout << cacBigInt(line) << std::endl;

        auto t_end = std::chrono::high_resolution_clock::now();
        std::cout << std::fixed << std::setprecision(5) << "---Caculate time: "
                  << std::chrono::duration<double, std::micro>(t_end - t_start).count()
                  << " μs---" << std::endl;
        std::cout << "==" << std::endl;
    }
    inf.close();

    getchar();

    return 0;
}


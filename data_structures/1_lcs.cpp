/*
 * 1_lcs.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <string>
#include <vector>

void lcs_recursion(const std::string &str1, const std:: string &str2, std::size_t n, std::size_t m, int &maxl, std::string &lcs)
{
    if (0 == n || 0 == m)
        return;
    if (str1[n] == str2[m]) {
        maxl++;
        lcs_recursion(str1, str2, n - 1, m - 1, maxl, lcs);
        lcs += str1[n];
    }
    else {
        int max1 = 0; std::string lcs1 = ""; lcs_recursion(str1, str2, n - 1, m, max1, lcs1);
        int max2 = 0; std::string lcs2 = ""; lcs_recursion(str1, str2, n, m - 1, max2, lcs2);
        if (max1 > max2) {
            maxl += max1;
            lcs += lcs1;
        }
        else {
            maxl += max2;
            lcs += lcs2;
        }
    }
}

void lcs_iteration(const std::string &str1, const std:: string &str2, int &maxl, std::string &lcs)
{
    std::vector<std::vector<int>> tv(str1.size(), std::vector<int>(str2.size()));
    for (std::size_t i = 0; i < str1.size(); ++i) {
        for (std::size_t j = 0; j < str2.size(); ++j) {
            if (0 == i || 0 == j)
                tv[i][j] = 0;
            else if (str1[i - 1] == str2[j - 1]) {
                tv[i][j] = tv[i-1][j-1] + 1;
                lcs += str1[i];
            }
            else 
                tv[i][j] = tv[i-1][j] > tv[i][j-1] ? tv[i-1][j] : tv[i][j-1];
        }
    }
    maxl = tv[str1.size() - 1][str2.size() - 1];
}

int main()
{
    std::string str1 = "13455";
    std::string str2 = "245576";
    int maxl = 0;
    std::string lcs = "";
    lcs_recursion(str1, str2, str1.size() - 1, str2.size() - 1, maxl, lcs); 
    std::cout << maxl << ": " << lcs << std::endl;

    lcs_iteration(str1, str2, maxl, lcs); 
    std::cout << maxl << ": " << lcs << std::endl;
    
    return 0;
}



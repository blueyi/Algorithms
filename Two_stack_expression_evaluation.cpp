/*
 * Two_stack_expression_evaluation.cpp
 * Copyright (C) 2015  <@BLUEYI-PC>
 *Dijkstra's Two-Stack Algorithm for Expression Evaluation
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

int main(int argc, char **argv)
{
    std::string str;
    if (argc == 2)
      str = argv[1];
    else
      str = "1 + ((2 + 8) * 10) + (3 * 5) + (6 * 7)";

    std::istringstream is(str);
    std::vector<char> ops;
    std::vector<double> vals;
    char ch;
    while ((ch = is.peek()) && (ch != EOF)) {
        if (isdigit(ch)) {
            double temp;
            is >> temp;
            vals.push_back(temp);
        }
        else if (ch == '+') ops.push_back((char)is.get());
        else if (ch == '-') ops.push_back((char)is.get());
        else if (ch == '*') ops.push_back((char)is.get());
        else if (ch == '/') ops.push_back((char)is.get());
        else if (ch == ')') {
            is.get();
            char op = ops.back();
            ops.pop_back();
            double val = vals.back();
            vals.pop_back();
            if (op == '+') val += vals.back();
            else if (op == '-') val -= vals.back();
            else if (op == '*') val *= vals.back();
            else if (op == '/') val /= vals.back();
            vals.pop_back();
            vals.push_back(val);
        }
        else is.get();
    }
    while (ops.size() != 0 && vals.size() > 1) {
        char op = ops.back();
        ops.pop_back();
        double val = vals.back();
        vals.pop_back();
        if (op == '+') val += vals.back();
        else if (op == '-') val -= vals.back();
        else if (op == '*') val *= vals.back();
        else if (op == '/') val /= vals.back();
        vals.pop_back();
        vals.push_back(val);
    }
    std::cout << vals.back() << std::endl;
    return 0;
}



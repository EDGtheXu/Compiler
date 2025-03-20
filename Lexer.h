//#pragma once
//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <cctype>
//#include <unordered_map>
//#include <fstream>
//
//using namespace std;
//
//// Token结构
//struct Token {
//    int LINE;
//    string LEX;
//    string SEM;
//
//    Token(int line, string lex, string sem) : LINE(line), LEX(lex), SEM(sem) {}
//};
//
//// 词法分析器类
//class LexicalAnalyzer {
//private:
//    string input;            // 输入的源代码
//    int pos;                 // 当前字符位置
//    int line;                // 当前行号
//    vector<Token> tokens;    // 存储生成的Token列表
//
//    // DFA状态
//    enum State {
//        START, INID, INNUM, INCHAR, INCOMMENT, INASSIN, INRANGE, DONE, ERROR
//    };
//    string getSymbolDescription(char symbol);
//    // 获取下一非空字符
//    char getNextChar();
//
//    // 回退字符
//    void ungetNextChar();
//
//    // 查找保留字
//    string reservedLookup(const string& id);
//
//    // 处理单词
//    void processToken(const string& buffer, State currentState);
//
//public:
//    // 构造函数
//    LexicalAnalyzer(const string& code) : input(code), pos(0), line(1) {}
//
//    // 获取所有单词
//    vector<Token> getTokenList();
//};
//

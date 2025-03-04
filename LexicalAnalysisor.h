#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>


// 定义词法单元类型
enum class TokenType {
    KEYWORD, IDENTIFIER, INTEGER, REAL, BOOLEAN,
    OPERATOR, DELIMITER, COMMENT, END_OF_FILE
};

// 定义词法单元结构
struct Token {
    TokenType type;
    std::string value;
    int line; // 行号（用于错误提示）
};


// 关键字表
extern const std::unordered_map<std::string, TokenType> KEYWORDS;


// 运算符表
extern const std::unordered_map<std::string, TokenType> OPERATORS;

// 分隔符表
extern const std::unordered_map<char, TokenType> DELIMITERS;



// 词法分析器类
class Lexer {
public:
    Lexer(const std::string& input) : input(input), position(0), line(1) {}

    // 获取下一个词法单元
    Token getNextToken() {
        skipWhitespace();

        if (position >= input.size()) {
            return { TokenType::END_OF_FILE, "", line };
        }

        char currentChar = input[position];

        // 检查标识符或关键字
        if (isalpha(currentChar) || currentChar == '_') {
            return parseIdentifierOrKeyword();
        }

        // 检查数字（整数或实数）
        if (isdigit(currentChar)) {
            return parseNumber();
        }

        // 检查运算符
        if (OPERATORS.find(std::string(1, currentChar)) != OPERATORS.end()) {
            return parseOperator();
        }

        // 检查分隔符
        if (DELIMITERS.find(currentChar) != DELIMITERS.end()) {
            return parseDelimiter();
        }

        // 检查注释
        if (currentChar == '/' && position + 1 < input.size()) {
            char nextChar = input[position + 1];
            if (nextChar == '/') {
                return parseSingleLineComment();
            }
            else if (nextChar == '*') {
                return parseMultiLineComment();
            }
        }

        // 未知字符
        throw std::runtime_error("Unknown character: " + std::string(1, currentChar) + " at line " + std::to_string(line));
    }

private:
    std::string input;
    size_t position;
    int line;

    // 跳过空白字符
    void skipWhitespace() {
        while (position < input.size() && isspace(input[position])) {
            if (input[position] == '\n') {
                line++;
            }
            position++;
        }
    }

    // 解析标识符或关键字
    Token parseIdentifierOrKeyword() {
        std::string value;
        while (position < input.size() && (isalnum(input[position]) || input[position] == '_')) {
            value += input[position++];
        }

        if (KEYWORDS.find(value) != KEYWORDS.end()) {
            return { KEYWORDS.at(value), value, line };
        }

        return { TokenType::IDENTIFIER, value, line };
    }

    // 解析数字（整数或实数）
    Token parseNumber() {
        std::string value;
        bool isReal = false;

        while (position < input.size() && (isdigit(input[position]) || input[position] == '.')) {
            if (input[position] == '.') {
                if (isReal) {
                    throw std::runtime_error("Invalid number format at line " + std::to_string(line));
                }
                isReal = true;
            }
            value += input[position++];
        }

        return { isReal ? TokenType::REAL : TokenType::INTEGER, value, line };
    }

    // 解析运算符
    Token parseOperator() {
        std::string value;
        value += input[position++];

        // 检查双字符运算符（如 <=, >=, <>）
        if (position < input.size() && OPERATORS.find(value + input[position]) != OPERATORS.end()) {
            value += input[position++];
        }

        return { TokenType::OPERATOR, value, line };
    }

    // 解析分隔符
    Token parseDelimiter() {
        char value = input[position++];
        return { DELIMITERS.at(value), std::string(1, value), line };
    }

    // 解析单行注释
    Token parseSingleLineComment() {
        std::string value;
        while (position < input.size() && input[position] != '\n') {
            value += input[position++];
        }
        return { TokenType::COMMENT, value, line };
    }

    // 解析多行注释
    Token parseMultiLineComment() {
        std::string value;
        position += 2; // 跳过 '/*'

        while (position + 1 < input.size() && !(input[position] == '*' && input[position + 1] == '/')) {
            if (input[position] == '\n') {
                line++;
            }
            value += input[position++];
        }

        if (position + 1 >= input.size()) {
            throw std::runtime_error("Unterminated multi-line comment at line " + std::to_string(line));
        }

        position += 2; // 跳过 '*/'
        return { TokenType::COMMENT, value, line };
    }
};

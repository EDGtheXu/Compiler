#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>


// ����ʷ���Ԫ����
enum class TokenType {
    KEYWORD, IDENTIFIER, INTEGER, REAL, BOOLEAN,
    OPERATOR, DELIMITER, COMMENT, END_OF_FILE
};

// ����ʷ���Ԫ�ṹ
struct Token {
    TokenType type;
    std::string value;
    int line; // �кţ����ڴ�����ʾ��
};


// �ؼ��ֱ�
extern const std::unordered_map<std::string, TokenType> KEYWORDS;


// �������
extern const std::unordered_map<std::string, TokenType> OPERATORS;

// �ָ�����
extern const std::unordered_map<char, TokenType> DELIMITERS;



// �ʷ���������
class Lexer {
public:
    Lexer(const std::string& input) : input(input), position(0), line(1) {}

    // ��ȡ��һ���ʷ���Ԫ
    Token getNextToken() {
        skipWhitespace();

        if (position >= input.size()) {
            return { TokenType::END_OF_FILE, "", line };
        }

        char currentChar = input[position];

        // ����ʶ����ؼ���
        if (isalpha(currentChar) || currentChar == '_') {
            return parseIdentifierOrKeyword();
        }

        // ������֣�������ʵ����
        if (isdigit(currentChar)) {
            return parseNumber();
        }

        // ��������
        if (OPERATORS.find(std::string(1, currentChar)) != OPERATORS.end()) {
            return parseOperator();
        }

        // ���ָ���
        if (DELIMITERS.find(currentChar) != DELIMITERS.end()) {
            return parseDelimiter();
        }

        // ���ע��
        if (currentChar == '/' && position + 1 < input.size()) {
            char nextChar = input[position + 1];
            if (nextChar == '/') {
                return parseSingleLineComment();
            }
            else if (nextChar == '*') {
                return parseMultiLineComment();
            }
        }

        // δ֪�ַ�
        throw std::runtime_error("Unknown character: " + std::string(1, currentChar) + " at line " + std::to_string(line));
    }

private:
    std::string input;
    size_t position;
    int line;

    // �����հ��ַ�
    void skipWhitespace() {
        while (position < input.size() && isspace(input[position])) {
            if (input[position] == '\n') {
                line++;
            }
            position++;
        }
    }

    // ������ʶ����ؼ���
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

    // �������֣�������ʵ����
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

    // ���������
    Token parseOperator() {
        std::string value;
        value += input[position++];

        // ���˫�ַ���������� <=, >=, <>��
        if (position < input.size() && OPERATORS.find(value + input[position]) != OPERATORS.end()) {
            value += input[position++];
        }

        return { TokenType::OPERATOR, value, line };
    }

    // �����ָ���
    Token parseDelimiter() {
        char value = input[position++];
        return { DELIMITERS.at(value), std::string(1, value), line };
    }

    // ��������ע��
    Token parseSingleLineComment() {
        std::string value;
        while (position < input.size() && input[position] != '\n') {
            value += input[position++];
        }
        return { TokenType::COMMENT, value, line };
    }

    // ��������ע��
    Token parseMultiLineComment() {
        std::string value;
        position += 2; // ���� '/*'

        while (position + 1 < input.size() && !(input[position] == '*' && input[position + 1] == '/')) {
            if (input[position] == '\n') {
                line++;
            }
            value += input[position++];
        }

        if (position + 1 >= input.size()) {
            throw std::runtime_error("Unterminated multi-line comment at line " + std::to_string(line));
        }

        position += 2; // ���� '*/'
        return { TokenType::COMMENT, value, line };
    }
};

#include "Lexer.h"


// �ؼ��ֱ�
const std::unordered_map<std::string, TokenType> KEYWORDS = {
    {"program", TokenType::KEYWORD},
    {"var", TokenType::KEYWORD},
    {"integer", TokenType::KEYWORD},
    {"real", TokenType::KEYWORD},
    {"boolean", TokenType::KEYWORD},
    {"procedure", TokenType::KEYWORD},
    {"begin", TokenType::KEYWORD},
    {"end", TokenType::KEYWORD},
    {"if", TokenType::KEYWORD},
    {"then", TokenType::KEYWORD},
    {"else", TokenType::KEYWORD},
    {"while", TokenType::KEYWORD},
    {"do", TokenType::KEYWORD},
    {"read", TokenType::KEYWORD},
    {"write", TokenType::KEYWORD},
    {"true", TokenType::BOOLEAN},
    {"false", TokenType::BOOLEAN}
};

// �������
const std::unordered_map<std::string, TokenType> OPERATORS = {
    {"+", TokenType::OPERATOR},
    {"-", TokenType::OPERATOR},
    {"*", TokenType::OPERATOR},
    {"/", TokenType::OPERATOR},
    {"=", TokenType::OPERATOR},
    {"<>", TokenType::OPERATOR},
    {"<", TokenType::OPERATOR},
    {">", TokenType::OPERATOR},
    {"<=", TokenType::OPERATOR},
    {">=", TokenType::OPERATOR},
    {"and", TokenType::OPERATOR},
    {"or", TokenType::OPERATOR},
    {"not", TokenType::OPERATOR}
};

// �ָ�����
const std::unordered_map<char, TokenType> DELIMITERS = {
    {';', TokenType::DELIMITER},
    {',', TokenType::DELIMITER},
    {'(', TokenType::DELIMITER},
    {')', TokenType::DELIMITER},
    {':', TokenType::DELIMITER}
};

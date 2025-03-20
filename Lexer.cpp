//#include "Lexer.h"
//
//// 保留字
//unordered_map<string, string> _reservedWords = {
//    {"program","PROGRAM"},
//    {"type","TYPE"},
//    {"var","VAR"},
//    {"procedure","PROCEDURE"},
//    {"begin","BEGIN"},
//    {"end","END"},
//    {"array","ARRAY"},
//    {"of","OF"},
//    {"record","RECORD"},
//    {"if","IF"},{"then","THEN"},
//    {"else","ELSE"},
//    {"fi","FI"},
//    {"while","WHILE"},
//    {"do","DO"},
//    {"endwh","ENDWH"},
//    {"read","READ"},
//    {"write","WRITE"},
//    {"return","RETURN1"},
//    {"integer","INTEGER"},
//    {"char","CHAR"}
//};
//
//
//string LexicalAnalyzer::getSymbolDescription(char symbol) {
//    switch (symbol) {
//    case '+':
//        return "PLUS";
//    case '-':
//        return "MINUS";
//    case '*':
//        return "MULTIPLY";
//    case '/':
//        return "DIVIDE";
//    case '(':
//        return "LEFT_PARENTHESIS";
//    case ')':
//        return "RIGHT_PARENTHESIS";
//    case ';':
//        return "SEMICOLON";
//    case '[':
//        return "LEFT_BRACKET";
//    case ']':
//        return "RIGHT_BRACKET";
//    case '<':
//        return "LESS_THAN";
//    case ' ':
//        return "NULL_CHARACTER";
//    case '=':
//        return "equal";
//    case '\n':
//
//        return "enter";
//    case EOF:
//        return "END_OF_FILE";
//    default:
//        return "UNKNOWN_SYMBOL";
//    }
//}
//
//
//// 获取下一非空字符
//char LexicalAnalyzer::getNextChar() {
//    //        while (pos < input.size()) {
//    //            if (input[pos] == '\n') line++;
//    //            pos++;
//    //        }
//    if (pos < input.size()) {
//        //if (input[pos] == '\n') line++;
//        return input[pos++];
//    }
//    return '\0';
//}
//
//// 回退字符
//void LexicalAnalyzer::ungetNextChar() {
//    if (pos > 0) {
//        pos--;
//    }
//}
//
//
//// 查找保留字
//string LexicalAnalyzer::reservedLookup(const string& id) {
//    auto it = _reservedWords.find(id);
//    if (it != _reservedWords.end()) {
//        return it->second;
//    }
//    return "ID";
//}
//
//// 处理单词
//void LexicalAnalyzer::processToken(const string& buffer, State currentState) {
//    //cout<<currentState;
//    switch (currentState) {
//    case INID: {//cout<<"###";
//
//        string lexType = reservedLookup(buffer);
//        tokens.push_back(Token(line, lexType, buffer));
//        break;
//    }
//    case INNUM:
//        tokens.push_back(Token(line, "NUM", buffer));
//        break;
//    case INCHAR:
//        tokens.push_back(Token(line, "CHAR", buffer));
//        break;
//    case INASSIN:
//        tokens.push_back(Token(line, "ASSIGN", buffer));
//        break;
//    case INCOMMENT:
//        // 注释不生成Token
//        break;
//    case INRANGE:
//        tokens.push_back(Token(line, "RANGE", buffer));
//        break;
//    case ERROR:
//        tokens.push_back(Token(line, "ERROR", "EMPTY"));
//        break;
//    default:
//        string symbol = getSymbolDescription(buffer[0]);
//        if ((buffer[0] != ' ') && (buffer[0] != '\n'))
//            tokens.push_back(Token(line, symbol, "#"));
//        if (buffer[0] == '\n') line++;
//        break;
//    }
//}
//
//// 获取所有单词
//vector<Token> LexicalAnalyzer::getTokenList() {
//    State currentState = START;
//    string buffer;
//    int end = 1;
//    char ch;
//    while (end) {
//
//
//        //	cout<<currentState;
//        ch = getNextChar();
//        //cout<<ch<<endl;
//        //break;
//
//
//        switch (currentState) {
//        case START:
//
//            buffer.clear();
//
//            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
//                //cout<<ch<<endl;
//                currentState = INID;
//                buffer += ch;
//            }
//            else if (isdigit(ch)) {
//                currentState = INNUM;
//                buffer += ch;
//            }
//            else if (ch == ',') {
//                currentState = INCHAR;
//                buffer += ch;
//            }
//            else if (ch == ':') {
//                buffer += ch;
//                if (getNextChar() == '=') {
//                    currentState = INASSIN;
//                    buffer += '=';
//                }
//                else {
//                    processToken(buffer, ERROR);
//                    currentState = START;
//                    ungetNextChar();
//                }
//            }
//            else if (ch == '.') {
//                buffer += ch;
//                if (getNextChar() == '.') {
//                    currentState = INRANGE;
//                    buffer += ch;
//                }
//                else {
//                    end = 0;
//                }
//            }
//            else if (getSymbolDescription(ch) != "UNKNOWN_SYMBOL") {
//                currentState = DONE;
//                ungetNextChar();
//            }
//            else {
//                cout << ch << endl;
//                processToken(buffer, ERROR);
//            }
//            break;
//
//        case INID:
//            //cout<<buffer<<endl;
//            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
//                //cout<<ch;
//                buffer += ch;
//            }
//            else {
//                ungetNextChar();
//                //currentState = DONE;
//                processToken(buffer, currentState);
//                currentState = START;
//            }
//            break;
//
//        case INNUM:
//            if (isdigit(ch)) {
//                buffer += ch;
//            }
//            else {
//                ungetNextChar();
//                //currentState = DONE;
//                processToken(buffer, currentState);
//                currentState = START;
//            }
//            break;
//
//        case INCHAR:
//            if (ch != ',') {
//                buffer += ch;
//            }
//            else {
//                buffer += ch;
//                //currentState = DONE;
//                processToken(buffer, currentState);
//                currentState = START;
//            }
//            break;
//
//        case INASSIN:
//
//            processToken(buffer, currentState);
//            currentState = START;
//
//            break;
//
//        case INCOMMENT:
//            if (ch == '}') {
//                currentState = START;
//            }
//            break;
//
//        case INRANGE:
//            currentState = START;
//            break;
//
//        case DONE:
//            processToken(string(1, ch), DONE);
//            currentState = START;
//            break;
//        }
//        if (ch == '\0') {
//            break; // EOF
//        }
//    }
//
//    return tokens;
//}
//
//

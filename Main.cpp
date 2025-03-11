#include"Lexer.h"
#include"File_op.h"
// 主函数
int main() {
    string filename = "test.txt";
    string code = readFromFile(filename);
    LexicalAnalyzer analyzer(code);
    vector<Token> tokens = analyzer.getTokenList();
    //cout<<tokens.size();
    for (const auto& token : tokens) {

        cout << "[" << token.LINE << ", " << token.LEX << ", " << token.SEM << "]" << endl;
    }

    return 0;
}
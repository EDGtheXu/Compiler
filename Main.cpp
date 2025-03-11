
#include"Lexer.h"

// 主函数
int main() {
    string code = "program p \n type t=integer;\n var t v1;\n char v2;\n begin \n read(v1);\n v1:=v1+10;\nwrite(v1)\n end.";
    LexicalAnalyzer analyzer(code);
    vector<Token> tokens = analyzer.getTokenList();
    //cout<<tokens.size();
    for (const auto& token : tokens) {

        cout << "[" << token.LINE << ", " << token.LEX << ", " << token.SEM << "]" << endl;
    }


    return 0;
}
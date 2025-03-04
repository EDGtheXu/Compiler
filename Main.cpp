
#include"Lexer.h"

// 主函数
int main() {
    std::string input = R"(
        program Example;
        var x, y: integer;
        begin
            x := 10;
            y := x + 5;
            if y > 10 then
                write("Y is greater than 10");
        end.
    )";

    Lexer lexer(input);
    std::vector<Token> tokens;

    try {
        while (true) {
            Token token = lexer.getNextToken();
            tokens.push_back(token);
            if (token.type == TokenType::END_OF_FILE) {
                break;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // 输出词法单元
    for (const auto& token : tokens) {
        std::cout << "Type: " << static_cast<int>(token.type)
            << ", Value: " << token.value
            << ", Line: " << token.line << std::endl;
    }

    return 0;
}
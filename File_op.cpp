#include "File_op.h"
// 将字符串写入文件
void writeToFile(const std::string& code, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << code;
        outFile.close();
        //std::cout << "Code has been written to " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

// 从文件中读取内容到字符串
std::string readFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::string code;
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            code += line + '\n';
        }
        inFile.close();
       std::cout << "Code has been read from " << filename << std::endl;
    }
    else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
    return code;
}

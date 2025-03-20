#include"Lexer.h"
#include"tm.h"
#include "func.h"
#include "global.h"
#include "globalVar.h"
#include "lexical.h"
#include "ll1.h"
#include "newll1.h"
#include "semantic.h"
#include "mid.h"
#include <iostream>


//LL1语法分析
int mmc = 1;
void STEP2b()
{
    treeroot = programLL1();
    printTreeLL1(treeroot, 0, false);
}
void preOrder(Node* node);

void printParser(SyntaxTree* syntaxTree) // 显示语法分析的结果
{
    Node* root = syntaxTree->getRoot();

    string str = root->nodekind;
    cout << str << endl;
    for (int i = 0; i < 3; i++)
    {
        if (root->child[i] == nullptr)
        {
            continue;
        }
        preOrder(root->child[i]);
    }
}

void preOrder(Node* node)
{
    if (!node)
        return;
    if (node->sibling != nullptr)
    {
        preOrder(node->sibling);
    }
    string str = node->nodekind;

    // 以下用于显示标识符
    for (int i = 0; i < 10; i++)
    {
        if (node->name[i] != "")
        {
            if (i != 0)
            {
                str += ",";
            }
            else
            {
                str += ":";
            }
            str += node->name[i];
        }
    }

    cout << str << endl;

    for (int i = 0; i < 3; i++)
    {
        if (node->child[i] == nullptr)
        {
            continue;
        }
        preOrder(node->child[i]);
    }
}


void Step1(FILE* fp) {
    freopen("step1.txt", "w", stdout);
    cout << "***************************** lexial *****************************" << endl;
    fp = fopen("cifa.txt", "r");
    lexicalAnalyse(fp);
    printTokenList();
    fclose(fp);

    if (lexical_correct == 0)
        longjmp(jump_buffer, 1);
}

void Recursion() {
    freopen("rec.txt", "w", stdout);
    // freopen("!r_1.txt", "w", stdout);

    cout << "***************************** recursion *****************************" << endl;


    TreeNode* t = program();

    if (tokenList[Index].wd.tok == ENDFILE) {
        cout << "Recursion success!" << endl;
        printTree(t, 0, true);
    }

    else {
        cout << "Recursion defeat!" << endl;
        mmc = 0;
        // longjmp(jump_buffer, 1);
    }

    //ppp(t);

}
void LL1old() {
    freopen("LL1old.txt", "w", stdout);
    // freopen("con", "w", stdout);
    cout << "***************************** LL1(old) *****************************" << endl;
    treeroot = programLL1();
    printTreeLL1(treeroot, 0, false);
}

void LL1new(Node*& miao) {
    freopen("LL1new.txt", "w", stdout);
    // freopen("con", "w", stdout);
    cout << "***************************** LL1(new) *****************************" << endl;

    Index = 0;
    initLL1();
    ParserLL1 test;
    SyntaxTree* t_root = test.run();
    Node* res = t_root->getRoot();
    /* vector<int> v(5, 0);
    show(res, 0, v, false);*/


    // TODO 这里有点问题
    // 
    //if (is_newLL1_correct)
    //    printTreeNewLL1(res, 0, true);
    miao = res;

    /*printParser(t_root);
    treeroot = programLL1();
    printTreeLL1(treeroot, 0, false);
    */
}



void STEP3()
{
    if (mmc == 0)
    {
        longjmp(jump_buffer, 1);
    }
    freopen("step3.txt", "w", stdout);
    TreeNode* t = treeroot;

    // freopen("wocaonima.txt", "w", stdout);
    cout << "***************************** Semantic *****************************" << endl;
    t = t->child[1];
    //cout << t->name;
    // 现在t是DeclarePart
    for (int i = 0; i < t->child.size() && t->child[i]; i++)
    {
        TreeNode* temp = t->child[i];
        if (temp->name == "TypeDec")
            typeSaveTable(temp, smbltable);
        else if (temp->name == "VarDec")
            varSaveTable(temp, smbltable);
        else if (temp->name == "ProcDec")
        {
            SymbolTable* p = NULL;
            procSaveTable(temp, smbltable, p);
            // cout << "here"<< endl;
        }
    }


    Check_STEP3(treeroot, smbltable);


    SymbolTable* head = new SymbolTable();
    head->addRecord(treeroot->child[0]->child.back()->child[0]->name, "procKind", "program", t->tk, smbltable);
    head->printTable();

    if (is_correct_semantic == 0)
        longjmp(jump_buffer, 1);
}


void MID(Node* t)
{
    freopen("mid.txt", "w", stdout);
    if (!t)
        return;
    processMid(t);
    printMidCode(midtable);
}


extern vector<SymbolRec*> SRec;
extern int indexp;
extern int beginp[16];
extern int endp[16];
extern string pname[16];
void init()
{
    // memset(tokenList, 0, sizeof(tokenList));
    mmc = 1;
    for (auto& s : tokenList) {
        s.line = 0;
        s.index = -1;
        s.wd.str = "";
        s.wd.tok = (Terminal)0;
    }

    Index = 0;
    if (anlsstack)
        delete(anlsstack);
    anlsstack = new AnalysisStack();
    treeroot = nullptr;
    memset(LL1Tbl, 0, sizeof(LL1Tbl));
    currentTree = NULL;
    currentToken = NULL;
    strline = 0;
    for (auto& s : outstr)
        s = "";
    for (auto& s : outstrLL1)
        s = "";
    for (auto& s : outstrLL1new)
        s = "";
    strlineLL1new = 0;
    strlineLL1 = 0;
    is_newLL1_correct = 1;

    // lexical.cpp
    lexical_correct = 1;

    midtable.resize(0);

    MidPrintNodeTable.resize(0);

    tmpidx = 0;

    // semantic
    if (smbltable)
        delete smbltable;
    smbltable = new SymbolTable();
    SBase.resize(0);
    SRec.resize(0);
    for (auto& s : bstr)
        s = "";
    bindex = 0;
    root = NULL;
    is_correct_semantic = 1;
    memset(procedure, 0, sizeof(procedure));
    indexp = 0;
    memset(beginp, 0, sizeof(beginp));
    memset(endp, 0, sizeof(endp));
    for (auto& s : pname)
        s = "";

}

void process()
{


    init();
    for (int i = 0; i < 1024; i++)
    {
        tokenList[i].index = i;
    }


    if (setjmp(jump_buffer) == 0) // 保存下来当前的环境变量
    {
        freopen("step1.txt", "w", stdout);cout << "";
        freopen("rec.txt", "w", stdout);cout << "";
        freopen("LL1old.txt", "w", stdout);cout << "";
        freopen("LL1new.txt", "w", stdout);cout << "";
        freopen("step3.txt", "w", stdout);cout << "";
        freopen("mid.txt", "w", stdout);cout << "";
        freopen("con", "w", stdout);

        FILE* fp;
        Step1(fp);

        Recursion();

        LL1old();

        Node* miao;
        LL1new(miao);

        STEP3();

        MID(miao);
    }

}


// 主函数
int main() {
    string code = 
"program p \n\
    type t=integer;\n\
    var t v1;\n\
    char v2;\n begin\n\
    read(v1);\n\
    v1:=v1+10;\n\
    write(v1)\n\
 //end.";
 //   LexicalAnalyzer analyzer(code);
 //   vector<Token> tokens = analyzer.getTokenList();
 //   //cout<<tokens.size();
 //   for (const auto& token : tokens) {

 //       cout << "[" << token.LINE << ", " << token.LEX << ", " << token.SEM << "]" << endl;
 //   }

    //tmain("./cod.txt");

    process();

    return 0;
}
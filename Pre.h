#define PRESET_H_INCLUDED
#define PRESET_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <stack>
#include <sstream>

using namespace std;

/*lexical analysis*/
enum Tag
{
    NUM=256,REAL,ID,AND,OR,EQ,NE,GE,LE,STR,TYPE,KEY,THEN,ELSE,IFEND,WHILE,DO,WHEND,FOR,FOR_CHECK,FOR_DO,FOR_JUMP,FOR_END,CONTINUE,BREAK,RET,SSP,SPP,CALL,RETAX,RETT,FUN_S,FUN_E
};
string Tag_Str[]={
        "NUM","REAL","ID","AND","OR","EQ","NE","GE","LE","STR","TYPE","KEY","THEN","ELSE","IFEND","WHILE","DO","WHEND","FOR","FOR_C","FOR_D","FOR_J","FOR_E","CON","BRE","RET","SSP","SPP","CALL","RETAX","RETT","FUN_S","FUN_E"
};
#define NUM_SIZE 2
#define REAL_SIZE 8
#define CHAR_SIZE 1
const int k_w_len=8;
const int t_w_len=4;
string keywords[k_w_len]={"if","else","for","while","do","break","continue","return"};
string typewords[t_w_len]={"int","real","char","const"};
vector<string> idwords;
vector<string> strwords;

class Token
{
private:
    int tag;
public:
    Token(){}
    Token(int i)
    {
        tag=i;
    }
    int get_tag()
    {
        return tag;
    }
    virtual int get_numvalue(){}
    virtual double get_realvalue(){}
    virtual int get_lexeme(){}
    virtual string get_lexeme_str(){}
};
class Num: public Token
{
private:
    int value;
public:
    Num(int t,int v):Token(t),value(v){};
    int get_numvalue()
    {
        return value;
    }
};
class Real: public Token
{
private:
    double value;
public:
    Real(int t,double v):Token(t),value(v){};
    double get_realvalue()
    {
        return value;
    }
};
class Word: public Token
{
private:
    int lexeme;
public:
    Word(int t,int v):Token(t),lexeme(v){};
    int get_lexeme()
    {
        return lexeme;
    }
    string get_lexeme_str()
    {
        if((this->get_tag())==ID) return idwords[lexeme];
        else if((this->get_tag())==TYPE) return typewords[lexeme];
        else if((this->get_tag())==KEY) return keywords[lexeme];
        else return strwords[lexeme];
    }
};

string symbols=",;+-*/(){}[]^?:!~";
int get_keyindex(string a);
int get_typeindex(string a);
int get_idindex(string a);
int get_strindex(string a);
bool isletter(char c);
bool isdigit(char c);
bool issymbol(char c);
void show_Token_List();

bool lexical_error=false;
string error_message="";
string buffer="";
string tmp="";
vector<Token*> Token_List;

/* 递归子程序语法分析*/
bool synax_error=false;
bool semantic_error=false;
void Semantic_Error(string msg);

//符号表设计
int curpid;
struct Synb
{
    int tid;//token_index
    int typ;
    /*
    i r c a
    1 2 3 4
    */
    int cat;
    /*
    c v f
    1 2 3
    */
    int addr;
    int pid;
    Synb(int tid)
    {
        this->tid=tid;
        this->pid=curpid;
        this->typ=this->cat=this->addr=0;
    }
};

int Data_Size(int typ);

vector<Synb> Synbl;
int Tid_To_Sid(int tid);
vector<double> Consl;
int Vall=0;
struct Typeu
{
    int typ;
    vector<int> Tlen;
    /*eg:
    itp
    len1
    len2
    ...
    */
    Typeu(int typ)
    {
        this->typ=typ;
    }
};
vector<Typeu> Typel;
struct Declar_Unit
{
    int tid;
    vector<int> Array_Len_List;
    Declar_Unit(int tid)
    {
        this->tid=tid;
    }
    void Declar_Unit_Push(int len)
    {
        this->Array_Len_List.push_back(len);
    }
};

//四元式结构定义
struct Node{
    int Ein;   // 0: empty  1:identifier 2:num 3:arr 4.ret 5.fun
    int Addr;
    int Size;
    double Num;
    string Name;
};
// function list
struct Pfinf
{
    int Size;
    Node Ret;
};
vector<Pfinf> Pfinfl;
int mainpid;

void Synbl_Push_Name(int tid);
void Synbl_Push(Declar_Unit du,int typ,bool cat,bool arr,double val);   //typ:Type_Op   cat:Const_Type_Op   arr:Array_Op
int Synbl_Push_Fun_Typ(int tid,int typ);
void Synbl_Push_Fun_Size(int tid,int Size);

bool Const_Type_Op=false;
int Type_Op;
int Fun_Type_Op;
bool Array_Op=false;
bool Ret_Op=false;

void Show_Synbl();
void Semantic_Error(string msg);

stack<Node> Sem;
stack<int> Syn;
Node Tid_To_Node(int tid);
Node Num_To_Node(int num);
struct Middle_Code_Unit{
    int Operator;//
    Node Target1;//为零表示空
    Node Target2;//为零表示为空
    Node Result;//为零表示为空，为-1表示此处为跳转地址
};

Middle_Code_Unit Get_Ssp(int pid);
Middle_Code_Unit Get_Spp();
Middle_Code_Unit Call(int tid);
Middle_Code_Unit Fun_Start(int tid);
Middle_Code_Unit Fun_End(int tid);
Middle_Code_Unit Get_Retax(Node node);
Middle_Code_Unit Get_Ret();
Middle_Code_Unit Get_Rett(int typ);

vector<Middle_Code_Unit> Middle_Code;

void Show_Middle_Code();

vector< vector< Middle_Code_Unit> > Block;

/*翻译文法*/

//动作函数声明
void init();
void Pop_Sem();
void Pop_Syn();
void Push_Sem(int tid);
void Push_Syn(int op);
void Quat();
void Quat_a();//array address transfrom
void Unary_Quat();
void Assign();
//if else
void Genth();
void Genel();
void Genie();
//while
void Genwh();
void Gendo();
void Genwe();
//for
void Genfr();
void Genfc();
void Genfd();
void Genfj();
void Genfe();

void Continue();
void Break();

int Tid_To_Sid(int tid);
Node Num_To_Node(int num);
Node Tid_To_Node(int tid);

//by 何雪
int Token_List_Index;
void Conditional_Expression();
void Constant_Expression();
void Logical_Or_Expression();
void Expression();
void Logical_And_Expression();
void Inclusive_Or_Expression();
void Exclusive_Or_Expression();
void And_Expression();
void Equality_Expression();
void Relational_Expression();
void Additive_Expression();
void Multiplicative_Expression();
void Unary_Expression();
void Primary_Expression();
void Assignment_Expression();
//
double Constant();
double Real_Constant();
int Integer_Constant();
//by 王千阁
int TokenList_Index;
void Assignment_Operator();
void Unary_Operator();
void Type_Name();
int Type_Specifier();
Declar_Unit Declarator();
void Declaration();
void Init_Declarator();
void Initializer();
void Initializer_List();
void Initializer_End();
void Compound_Statement();
void Statement();
void Expression_Statement();
void Selection_Statement();
void Iteration_Statement();
void Jump_Statement();
//
void Return_Statement();
void Oringinal_Statements();
int Function_Call_Expression();

/*目标代码声明*/
int acc;
int acc_k;
int ii,jj;
string Temp_Op;
void Basic_Block_Partition();
string num2str(double t)
{
    stringstream ss;
    ss<<t;
    return ss.str();
}

static int Label_Index=0;
string Final_Label;
static vector<string>Label;
static vector<string>For_Label;
static vector<string>For_Do_Label;
struct Final_Code_Unit{
    int   Label_Index;
    string   Op;
    string   Dst;
    string   Sour;
};
static vector<Final_Code_Unit>Final_Code;
void Condition_Check_Final_Code(Node t);
Final_Code_Unit t,t1,t2;
void Send_To_Acc();
void Load1_To_Ax();
void Load2_To_Ax();
void TempOp1();
void TempOp2();
void BackEnd();

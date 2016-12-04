/* 
　　Windows 下c语言PL/0编译程序
　　在Visual C++ 6.0和Visual C.NET上运行
　　使用方法：
　　运行后输入PL/0源程序文件名
　　回答是否输出虚拟机代码
　　回答是否输出名字表
　　fa.tmp输出虚拟机代码
　　fa1.tmp输出源文件及其各行对应的首地址
　　fa2.tmp输出结果
　　fas.tmp输出名字表
*/

/* 关键字个数 */
#define norw 14					/*Linsixin 添加了关键字 这里也要改 */ 
/* 名字表容量 */
#define txmax 100
/* 所有的add1用于定义数组 */
#define txmaxadd1 101
/* number的最大位数 */
#define nmax 14
/* 符号的最大长度 */
#define al 10				
/* 地址上界 */
#define amax 2047
/* 最大允许过程嵌套声明层数 */
#define levmax 3
/* 最多的虚拟机代码数 */
#define cxmax 200
#define cxmaxadd1 201
/* 当函数中会发生fatal error时，返回-1告知调用它的函数，最终退出程序 */
#define getsymdo if(-1==getsym())return -1
#define getchdo if(-1==getch())return -1
#define testdo(a,b,c) if(-1==test(a,b,c))return -1
#define gendo(a,b,c) if(-1==gen(a,b,c))return -1
#define expressiondo(a,b,c) if(-1==expression(a,b,c))return -1
#define factordo(a,b,c) if(-1==factor(a,b,c))return -1
#define termdo(a,b,c) if(-1==term(a,b,c))return -1
#define conditiondo(a,b,c) if(-1==condition(a,b,c))return -1
#define statementdo(a,b,c) if(-1==statement(a,b,c))return -1
#define constdeclarationdo(a,b,c) if(-1==constdeclaration(a,b,c))return -1
#define vardeclarationdo(a,b,c) if(-1==vardeclaration(a,b,c))return -1

//typedef enum{false,true} bool;

/* 符号 */
enum symbol
{nul,ident,number,plus,minus,times,slash,oddsym,eql,neq,lss,leq,//0-11
gtr,geq,lparen,rparen,comma,semicolon,period,becomes,beginsym,	//12-20
endsym,ifsym,thensym,whilesym,writesym,readsym,dosym,callsym,	//21-28
constsym,varsym,procsym											//29-31
,forsym															//32 	//LinSixin 增加 forsym 
};

#define symnum 33											//LinSixin 增加关键字这里要增加 1 

/* 名字表中的类型 */
enum object {constant,variable,procedur};

/* 虚拟机代码 */
enum fct {lit,opr,lod,sto,cal,inte,jmp,jpc};
#define fctnum 8

/* 虚拟机代码结构 */
struct instruction   /*Linsixin 比如 INT 0 A 的意思是在栈顶开辟A个存储单元 */ 
{
	enum fct f; /* 虚拟机代码指令 */ 
	int l; /* 引用层与声明层的层次差 */
	int a; /* 根据f的不同而不同 */
};

FILE* fas; /* 输出名字表 */
FILE* fa; /* 输出虚拟机代码 */
FILE* fa1; /* 输出源文件及其各行对应的首地址 */
FILE* fa2; /* 输出结果 */
bool listswitch; /* 显示虚拟机代码与否 */
bool tableswitch; /* 显示名字表与否 */
char ch; /* 获取字符的缓冲区，getch 使用 */
enum symbol sym; /* 当前的符号 */
char id[al]; /* 当前ident */
int num; /* 当前number */
int cc,ll,kk; /* getch使用的计数器，cc表示当前字符(ch)的位置 */
int cx; /* 虚拟机代码指针 */
char line[81]; /* 读取行缓冲区 */
char a[al]; /* 临时符号 */
struct instruction code[cxmaxadd1]; /* 存放虚拟机代码的数组 */
char word[norw][al]; /* 保留字 */
enum symbol wsym[norw]; /* 保留字对应的符号值 */
enum symbol ssym[256]; /* 单字符的符号值 */

char mnemonic[fctnum][5]; /* 虚拟机代码指令名称 */

bool declbegsys[symnum]; /* 表示声明开始的符号集合 */
bool statbegsys[symnum]; /* 表示语句开始的符号集合 */
bool facbegsys[symnum]; /* 表示因子开始的符号集合 */

/*Linsixin 开始符号集也就是First集 ,有First集的都是有对应函数的,
	因为有First集以为着要判断使用那一条式子去规约 
	没有First集的都直接在Statement中处理了,没有对应的函数 
*/ 

/* 名字表结构 */
struct tablestruct
{
	char name[al]; /* 名字 */
	enum object kind; /* 类型：const,var or procedure */
	int val; /* 数值，仅const使用 */
	int level; /* 所处层，仅const不使用 */
	int adr; /* 地址，仅const不使用 */
	int size; /* 需要分配的数据区空间，仅procedure使用 */
};

struct tablestruct table[txmaxadd1]; /* 名字表 */

FILE* fin;
FILE* fout;
char fname[al];
int err; /* 错误计数器 */

void error(int n);
int getsym();
int getch();
void init();
int gen(enum fct x,int y,int z);
int test(bool* s1,bool* s2,int n);
int inset(int e,bool* s);
int addset(bool* sr,bool* s1,bool* s2,int n);
int subset(bool* sr,bool* s1,bool* s2,int n);
int mulset(bool* sr,bool* s1,bool* s2,int n);
int block(int lev,int tx,bool* fsys);
void interpret();
int factor(bool* fsys,int* ptx,int lev);
int term(bool* fsys,int* ptx,int lev);
int condition(bool* fsys,int* ptx,int lev);
int expression(bool* fsys,int* ptx,int lev);
int statement(bool* fsys,int* ptx,int lev);
void listcode(int cx0);
int vardeclaration(int* ptx,int lev,int* pdx);
int constdeclaration(int* ptx,int lev,int* pdx);
int postion(char* idt,int tx);
void enter(enum object k,int* ptx,int lev,int* pdx);
int base(int l,int* s,int b);



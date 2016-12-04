/* 
����Windows ��c����PL/0�������
������Visual C++ 6.0��Visual C.NET������
����ʹ�÷�����
�������к�����PL/0Դ�����ļ���
�����ش��Ƿ�������������
�����ش��Ƿ�������ֱ�
����fa.tmp������������
����fa1.tmp���Դ�ļ�������ж�Ӧ���׵�ַ
����fa2.tmp������
����fas.tmp������ֱ�
*/

/* �ؼ��ָ��� */
#define norw 14					/*Linsixin ����˹ؼ��� ����ҲҪ�� */ 
/* ���ֱ����� */
#define txmax 100
/* ���е�add1���ڶ������� */
#define txmaxadd1 101
/* number�����λ�� */
#define nmax 14
/* ���ŵ���󳤶� */
#define al 10				
/* ��ַ�Ͻ� */
#define amax 2047
/* ����������Ƕ���������� */
#define levmax 3
/* ��������������� */
#define cxmax 200
#define cxmaxadd1 201
/* �������лᷢ��fatal errorʱ������-1��֪�������ĺ����������˳����� */
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

/* ���� */
enum symbol
{nul,ident,number,plus,minus,times,slash,oddsym,eql,neq,lss,leq,//0-11
gtr,geq,lparen,rparen,comma,semicolon,period,becomes,beginsym,	//12-20
endsym,ifsym,thensym,whilesym,writesym,readsym,dosym,callsym,	//21-28
constsym,varsym,procsym											//29-31
,forsym															//32 	//LinSixin ���� forsym 
};

#define symnum 33											//LinSixin ���ӹؼ�������Ҫ���� 1 

/* ���ֱ��е����� */
enum object {constant,variable,procedur};

/* ��������� */
enum fct {lit,opr,lod,sto,cal,inte,jmp,jpc};
#define fctnum 8

/* ���������ṹ */
struct instruction   /*Linsixin ���� INT 0 A ����˼����ջ������A���洢��Ԫ */ 
{
	enum fct f; /* ���������ָ�� */ 
	int l; /* ���ò���������Ĳ�β� */
	int a; /* ����f�Ĳ�ͬ����ͬ */
};

FILE* fas; /* ������ֱ� */
FILE* fa; /* ������������ */
FILE* fa1; /* ���Դ�ļ�������ж�Ӧ���׵�ַ */
FILE* fa2; /* ������ */
bool listswitch; /* ��ʾ������������ */
bool tableswitch; /* ��ʾ���ֱ���� */
char ch; /* ��ȡ�ַ��Ļ�������getch ʹ�� */
enum symbol sym; /* ��ǰ�ķ��� */
char id[al]; /* ��ǰident */
int num; /* ��ǰnumber */
int cc,ll,kk; /* getchʹ�õļ�������cc��ʾ��ǰ�ַ�(ch)��λ�� */
int cx; /* ���������ָ�� */
char line[81]; /* ��ȡ�л����� */
char a[al]; /* ��ʱ���� */
struct instruction code[cxmaxadd1]; /* ����������������� */
char word[norw][al]; /* ������ */
enum symbol wsym[norw]; /* �����ֶ�Ӧ�ķ���ֵ */
enum symbol ssym[256]; /* ���ַ��ķ���ֵ */

char mnemonic[fctnum][5]; /* ���������ָ������ */

bool declbegsys[symnum]; /* ��ʾ������ʼ�ķ��ż��� */
bool statbegsys[symnum]; /* ��ʾ��俪ʼ�ķ��ż��� */
bool facbegsys[symnum]; /* ��ʾ���ӿ�ʼ�ķ��ż��� */

/*Linsixin ��ʼ���ż�Ҳ����First�� ,��First���Ķ����ж�Ӧ������,
	��Ϊ��First����Ϊ��Ҫ�ж�ʹ����һ��ʽ��ȥ��Լ 
	û��First���Ķ�ֱ����Statement�д�����,û�ж�Ӧ�ĺ��� 
*/ 

/* ���ֱ�ṹ */
struct tablestruct
{
	char name[al]; /* ���� */
	enum object kind; /* ���ͣ�const,var or procedure */
	int val; /* ��ֵ����constʹ�� */
	int level; /* �����㣬��const��ʹ�� */
	int adr; /* ��ַ����const��ʹ�� */
	int size; /* ��Ҫ������������ռ䣬��procedureʹ�� */
};

struct tablestruct table[txmaxadd1]; /* ���ֱ� */

FILE* fin;
FILE* fout;
char fname[al];
int err; /* ��������� */

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



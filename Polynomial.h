#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 1
#define INFEASIBLE -1
// #define OVERFLOW -2

typedef int Status;

typedef struct Term {
	double coef;
	// 系数(头结点为多项式项数)
	int expn;
	// 指数
	struct Term *next;
}Term, *Polynomial;



Status CreatePolyn(Polynomial &P, unsigned m);
// 1. 创建
Status PrintPolyn(Polynomial P);
// 2. 显示
Status CopyPolyn(Polynomial &Pa, Polynomial Pb);
// 3. 复制
Status AddPolyn(Polynomial &Pa, Polynomial Pb);
// 4. 求和
Status SubtractPolyn(Polynomial &Pa, Polynomial &Pb);
// 5. 求差
Status EvaluatePolyn(Polynomial P, double x, double &result);
// 6. 求值
Status DestroyPolyn(Polynomial &P);
// 7. 销毁
Status ClearPolyn(Polynomial &P);
// 8. 清空
Status InsertTerm(Polynomial &P, double coef, int expn);
Status DeleteTerm(Polynomial &P, int expn);
Status ChangeTerm(Polynomial &P, unsigned index, double coef, int expn);
// 9. 修改（①插入新的结点、②删除已有结点、③修改已有结点的系数和指数）


Status DiffPolyn(Polynomial &P, unsigned order);
// 10. 微分（N阶导数）
Status IndefIntegratePolyn(Polynomial &P);
// 11. 不定积分
Status DefIntegratePolyn(Polynomial &P, double LowerLimit, double UpperLimit, double &result);
// 12. 定积分
Status MultiplyPolyn(Polynomial &Pa, Polynomial Pb);
Status PowerPolyn(Polynomial &P, unsigned index);
// 13. 乘法和乘方
Status DividePolyn(Polynomial &Pa, Polynomial Pb, Polynomial &Remainder);
Status DividePolyn(Polynomial &Pa, Polynomial Pb);
// 14. 除法
Status GCDPolyn(Polynomial &Pa, Polynomial Pb);
Status LCMPolyn(Polynomial &Pa, Polynomial Pb);
// 15. 最大公约式和最小公倍式
// 16. 多项式的四则运算（如 “(1+2*3)/4”）





Status InitPolyn(Polynomial &P){
	// 构建一个空的单链表
	P = (Polynomial)malloc(sizeof(Term));
	if(!P)exit(OVERFLOW);
	P->coef = 0.0f;
	P->expn = -1;
	P->next = NULL;
	return OK;
}/*InitPolyn*/

int LocateElem(Polynomial P, Term *e, Term *&q, Status (*compare)(Term*, Term*)){
	// 在多项式P中查找第一个与e满足compare()==0的项并返回前驱指针
	// 找到返回第i项，否则返回0
	unsigned i = 1;
	Term *p = P;
	while(p->next && (*compare)(p->next, e) > 0){
		p = p->next;
		i++;
	}
	q = p;
	if(p->next){
		// 找到满足compare()<=0的项
		return (*compare)(p->next, e) ? 0 : i;
		// compare()==0时返回第i项，否则返回0
	}else{
		// 指数小于所有项
		return 0;
	}
}/*LocateElem*/

int TermCmp(Term *a, Term *b){
	// 依a的指数值<(或=)(或>)b的指数值，返回-1,0,1
	return a->expn > b->expn ? 1 : (a->expn == b->expn ? 0 : -1); 
}/*cmp*/

Status MakeTerm(Term *&T, double coef, int expn){
	// 创建项
	T = (Term*)malloc(sizeof(Term));
	if(!T)exit(OVERFLOW);
	T->coef = coef;
	T->expn = expn;
	T->next = NULL;
	return OK;
}/*MakeTerm*/

void InsFirst(Polynomial &P, Term *p, Term *q){
	// 将q结点插入在p结点之后，多项式长度加1
	q->next = p->next;
	p->next = q;
	P->coef += 1;
}/*InsFirst*/

Status CreatePolyn(Polynomial &P, unsigned m){
	// 创建多项式
	InitPolyn(P);
	// 初始化多项式
	// unsigned m;
	// scanf("%u", &m);
	// // 从标准输入读取多项式项数
	// for (int i = 0; i < m; ++i)	{
	while(P->coef < m){
		double coef;
		int expn;
		scanf("%lf%d", &coef, &expn);
		// 从标准输入读取系数，指数
		if(coef != 0 && expn >= 0){
			// 系数不为0
			Term *t, *q;
			MakeTerm(t, coef, expn);
			if(!LocateElem(P, t, q, TermCmp)){
				// 判断指数是否重复，未重复则按序插入
				InsFirst(P, q, t);
			}
		}
	}
	return OK;
}/*CreatePolyn*/

Status PrintPolyn(Polynomial P){
	// 打印多项式
	putchar('\n');
	if(!P){
		printf("Null Ptr\n");
		return ERROR;
	}
	Term *p = P->next;
	if(!p)putchar('0');
	// P为0多项式
	while(p){
		double coef = p->coef;
		int expn = p->expn;
		if(coef != 0){
			// 不判断系数也可以
			if(p != P->next || coef < 0){
				// 不是首项或系数为负
				putchar(coef > 0 ? '+' : '-');
			}
			// 符号
			coef = abs(coef);
			if(expn == 0 || coef != 1){
				// 常数项或系数不为1
				if(coef == (int)coef){
					// 整数
					printf("%d", (int)coef);
				}else{
					printf("%f", coef);
				}
			}
			// 系数绝对值
			if(expn > 0){
				// 非常数项
				putchar('X');
				if(expn > 1){
					printf("^%d", expn);
				}
			}
			// 指数
		}
		p = p->next;
	}
	putchar('\n');
	return OK;
}/*PrintPolyn*/

Status CopyPolyn(Polynomial &Pa, Polynomial Pb){
	// 将多项式Pb复制到Pa
	// Pa = Pb;
	ClearPolyn(Pa);
	if(!Pb){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *pa = Pa, *pb = Pb->next;
	while(pb){
		Term *t;
		MakeTerm(t, pb->coef, pb->expn);
		pb = pb->next;
		InsFirst(Pa, pa, t);
		pa = t;
	}
	return OK;
}/*CopyPolyn*/

Status AddPolyn(Polynomial &Pa, Polynomial Pb){
	// 将多项式Pb加到Pa
	if(!Pa || !Pb){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *pa = Pa;
	Term *pb = Pb->next;
	// free(Pb);
	while(pb){
		if(pa->next){
			// pa->next不为空，与pb比较
			if(TermCmp(pa->next, pb) > 0){
				pa = pa->next;
			}else if(TermCmp(pa->next, pb) == 0){
				// 将pb系数加到pa->next
				pa->next->coef += pb->coef;
				if(pa->next->coef == 0){
					Term *t = pa->next;
					pa->next = t->next;
					free(t);
					Pa->coef--;
				}
				// Term *t = pb;
				pb = pb->next;
				// free(t);
			}else if(TermCmp(pa->next, pb) < 0){
				Term *t;
				MakeTerm(t, pb->coef, pb->expn);
				pb = pb->next;
				InsFirst(Pa, pa, t);
				pa = t;
			}
		}else{
			// pa为最后一项
			Term *t;
			MakeTerm(t, pb->coef, pb->expn);
			pb = pb->next;
			InsFirst(Pa, pa, t);
			pa = pa->next;
		}
	}
	return OK;
}/*AddPolyn*/
/*
4 1 3 -1 2 +2 1 -2 0

+1.000000x^3-1.000000x^2+2.000000x^1-2.000000x^0
4 -2 0 1 3 -1 2 +2 1

+1.000000x^3-1.000000x^2+2.000000x^1-2.000000x^0

+0.000000x^3+1.000000x^2+0.000000x^1-2.000000x^0

-----------------
5 0 1 1 2 -1 1 0.5 3 -9.9 6

-9.900000X^6+0.500000X^3+X^2-X^1
5 -5 0 1 2 -1 1 0.5 3 -9.9 6

-9.900000X^6+0.500000X^3+X^2-X^1-5

-5

-9.900000X^6+0.500000X^3+X^2-X^1-10
-637.600000
*/

Status SubtractPolyn(Polynomial &Pa, Polynomial &Pb){
	// 从多项式Pa中减去Pb
	Polynomial Pt = NULL;
	CopyPolyn(Pt, Pb);
	if(!Pa || !Pt){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *pt = Pt->next;
	while(pt){
		pt->coef = -pt->coef;
		// 将多项式Pt符号颠倒
		pt = pt->next;
	}
	AddPolyn(Pa, Pt);
	DestroyPolyn(Pt);
	return OK;
}/*SubtractPolyn*/

Status EvaluatePolyn(Polynomial P, double x, double &result){
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	result = 0;
	Term *p = P->next;
	while(p){
		result += p->coef * pow(x, p->expn);
		p = p->next;
	}
	return OK;
}/*EvaluatePolyn*/

Status DestroyPolyn(Polynomial &P){
	Term *p = P;
	P = NULL;
	while(p){
		Term *t = p->next;
		free(p);
		p = t;
	}
	return OK;
}/*DestroyPolyn*/

Status ClearPolyn(Polynomial &P){
	if(!P){
		InitPolyn(P);
	}else{
		Term *p = P->next;
		while(p){
			Term *q = p->next;
			free(p);
			p = q;
		}
		P->coef = 0.0f;
		P->expn = -1;
		P->next = NULL;
	}
	return OK;
}/*ClearPolyn*/

Status InsertTerm(Polynomial &P, double coef, int expn){
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	if(coef == 0 || expn < 0){
		// 不允许这么做
		return ERROR;
	}
	Term *t, *p = P;
	MakeTerm(t, coef, expn);
	while(p->next && TermCmp(p->next, t) > 0){
		p = p->next;
	}
	if(!p->next || TermCmp(p->next, t)){
		// 多项式中无expn次项
		InsFirst(P, p, t);
	}else{
		// p的后继是x^expn项
		// 什么都不做
	}
	return OK;
}/*InsertTerm*/

Status DeleteTerm(Polynomial &P, int expn){
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *p = P;
	while(p->next && p->next->expn != expn){
		p = p->next;
	}
	if(!p->next){
		// 没找到
		return ERROR;
	}
	// 找到了
	Term *t = p->next;
	p->next = t->next;
	free(t);
	P->coef--;
	return OK;
}/*DeleteTerm*/

Status ChangeTerm(Polynomial &P, unsigned index, double coef, int expn){
	// 改变按序排列中的第index项
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *p = P;
	unsigned curIndex = 0;
	while(p->next && curIndex < index){
		curIndex++;
	}
	if(!p->next){
		// 又没找到
		return ERROR;
	}
	if(curIndex == index){
		Term *t = p->next, *q;
		p->next = t->next;
		free(t);
		MakeTerm(t, coef, expn);
		if(!LocateElem(P, t, q, TermCmp)){
			InsFirst(P, q, t);
		}
	}
	return OK;
}/*ChangeTerm*/



Status DiffPolyn(Polynomial &P, unsigned order){
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	for (int i = 0; i < order; ++i){
		Term *p = P;
		while(p->next){
			if(p->next->expn){
				// 非常数项
				p->next->coef *= p->next->expn--;
			}else{
				// 常数项
				P->coef--;
				Term *q = p->next;
				p->next = NULL;
				free(q);
				break;
			}
			p = p->next;
		}
	}
	return OK;
}/*DiffPolyn*/

Status IndefIntegratePolyn(Polynomial &P){
	// 将多项式从0到X积分
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *p = P;
	while(p->next){
		p->next->coef /= ++(p->next->expn);
		p = p->next;
	}
	return OK;
}/*IndefIntegratePolyn*/

Status DefIntegratePolyn(Polynomial &P, double LowerLimit, double UpperLimit, double &result){
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *p = P;
	result = 0;
	while(p = p->next){
		result += p->coef * (pow(UpperLimit, p->expn + 1) - pow(LowerLimit, p->expn + 1)) / (p->expn + 1);
	}
	return OK;
}/*DefIntegratePolyn*/

Status MultiplyPolyn(Polynomial &Pa, Polynomial Pb){
	// 将多项式Pb每一项乘以Pa再求和
	if(!Pa || !Pb){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Term *pb = Pb->next;
	Polynomial P, Pt = NULL;
	InitPolyn(P);
	// P存放求和
	while(pb){
		CopyPolyn(Pt, Pa);
		Term *pt = Pt->next;
		while(pt){
			pt->coef *= pb->coef;
			pt->expn += pb->expn;
			pt = pt->next;
		}
		AddPolyn(P, Pt);
		pb = pb->next;
	}
	DestroyPolyn(Pt);
	CopyPolyn(Pa, P);
	DestroyPolyn(P);
	return OK;
}

Status PowerPolyn(Polynomial &P, unsigned index){
	// 多项式的非负整数次方
	if(index == 0){
		ClearPolyn(P);
		InsertTerm(P, 1, 0);
		// 加入单位元
		return OK;
	}
	if(!P){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Polynomial Pt = NULL;
	CopyPolyn(Pt, P);
	for (int i = 1; i < index; ++i){
		MultiplyPolyn(Pt, P);
	}
	CopyPolyn(P, Pt);
	DestroyPolyn(Pt);
	return OK;
}

Status DividePolyn(Polynomial &Pa, Polynomial Pb, Polynomial &Remainder){
	// Pa整除以Pb，余项次数小于Pb次数
	if(!Pa || !Pb){
		// printf("Null Ptr\n");
		return ERROR;
	}
	Polynomial P;
	// 商
	InitPolyn(P);
	Term *pb = Pb->next;
	if(!pb){
		// 不能除以0
		return ERROR;
	}
	Polynomial Pt = NULL;
	while(Pa->next && Pa->next->expn >= pb->expn){
		double coef = Pa->next->coef / pb->coef;
		int expn = Pa->next->expn - pb->expn;
		InsertTerm(P, coef, expn);
		CopyPolyn(Pt, Pb);
		Term *pt = Pt->next;
		while(pt){
			pt->coef *= coef;
			pt->expn += expn;
			pt = pt->next;
		}
		SubtractPolyn(Pa, Pt);
	}
	DestroyPolyn(Pt);
	CopyPolyn(Remainder, Pa);
	// 剩余项
	CopyPolyn(Pa, P);
	DestroyPolyn(P);
	return OK;
}

Status DividePolyn(Polynomial &Pa, Polynomial Pb){
	// 调用带余除法
	Polynomial Remainder = NULL;
	return DividePolyn(Pa, Pb, Remainder);
}

Status GCDPolyn(Polynomial &Pa, Polynomial Pb){
	// Pa & Pb 的最大公约式
	Polynomial Pt = NULL, Remainder = NULL;
	CopyPolyn(Pt, Pb);
	DividePolyn(Pa, Pt, Remainder);
	while(Remainder->next){
		Polynomial P = NULL;
		DividePolyn(Pt, Remainder, P);
		DestroyPolyn(Pt);
		Pt = Remainder;
		Remainder = P;
	}
	CopyPolyn(Pa, Pt);
	DestroyPolyn(Pt);
	DestroyPolyn(Remainder);
	Term *pa = Pa->next;
	if(pa){
		// 化为首一多项式
		double c = pa->coef;
		pa->coef = 1;
		pa = pa->next;
		while(pa){
			pa->coef /= c;
		}
	}	
	return OK;
}

Status LCMPolyn(Polynomial &Pa, Polynomial Pb){
	// Pa & Pb 的最小公倍式
	Polynomial Pt = NULL;
	CopyPolyn(Pt, Pa);
	GCDPolyn(Pt, Pb);
	// Pt为最大公约式
	MultiplyPolyn(Pa, Pb);
	DividePolyn(Pa, Pt);
	DestroyPolyn(Pt);
	Term *pa = Pa->next;
	if(pa){
		// 化为首一多项式
		double c = pa->coef;
		pa->coef = 1;
		pa = pa->next;
		while(pa){
			pa->coef /= c;
		}
	}	
	return OK;
}
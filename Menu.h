#pragma once

#include "Polynomial.h"
#include <conio.h>

#define ARRAY_INIT_SIZE 10
#define ARRAY_INCREMENT 10



void MenuCreate();
// 1. 创建
void MenuPrint();
// 2. 显示
void MenuCopy();
// 3. 复制
void MenuAdd();
// 4. 求和
void MenuSubtract();
// 5. 求差
void MenuEvaluate();
// 6. 求值
void MenuDestroy();
// 7. 销毁
void MenuClear();
// 8. 清空
void MenuChange();
// 9. 修改（①插入新的结点、②删除已有结点、③修改已有结点的系数和指数）



void MenuDiff();
// 10. 微分（N阶导数）
void MenuIndefInt();
// 11. 不定积分
void MenuDefInt();
// 12. 定积分
void MenuMultiplyAndPower();
// 13. 乘法和乘方
void MenuDivide();
// 14. 除法
void MenuGCDLCM();
// 15. 最大公约式和最小公倍式

Polynomial *PolynArray;
unsigned ArraySize;
unsigned PolynNum = 0;

Status InitPolynArray(){
	// 构造一个空数组
	PolynArray = (Polynomial*)malloc(ARRAY_INIT_SIZE * sizeof(Polynomial));
	if(!PolynArray)exit(OVERFLOW);
	// 存储分配失败
	ArraySize = ARRAY_INIT_SIZE;
	return OK;
}


void MainMenu(){
	if(!InitPolynArray())return;
	while(1){
		system("cls");
		printf("Basic Functions:\n");
		printf("1: Create创建\n");
		printf("2: Print显示\n");
		printf("3: Copy复制\n");
		printf("4: Add求和\n");
		printf("5: Substract求差\n");
		printf("6: Evaluate求值\n");
		printf("7: Destroy销毁\n");
		printf("8: Clear清空\n");
		printf("9: Change修改（①插入新的结点、②删除已有结点、③修改已有结点的系数和指数）\n");
		
		printf("Ex Functions:\n");
		printf("A: Diff微分（N阶导数）\n");
		printf("B: IndefIntegrate不定积分\n");
		printf("C: DefIntegrate定积分\n");
		printf("D: MultiplyAndPower乘法和乘方\n");
		printf("E: Divide除法\n");
		printf("F: GCD&LCM最大公约式和最小公倍式\n");

		printf("Q: Quit\n");
		printf("Please input:");
		char c = getche();
		switch(c){
			case '1':
				MenuCreate();
				system("pause");
				break;
			case '2':
				MenuPrint();
				system("pause");
				break;
			case '3':
				MenuCopy();
				system("pause");
				break;
			case '4':
				MenuAdd();
				system("pause");
				break;
			case '5':
				MenuSubtract();
				system("pause");
				break;
			case '6':
				MenuEvaluate();
				system("pause");
				break;
			case '7':
				MenuDestroy();
				system("pause");
				break;
			case '8':
				MenuClear();
				system("pause");
				break;
			case '9':
				MenuChange();
				system("pause");
				break;
			case 'a':
			case 'A':
				MenuDiff();
				system("pause");
				break;
			case 'b':
			case 'B':
				MenuIndefInt();
				system("pause");
				break;
			case 'c':
			case 'C':
				MenuDefInt();
				system("pause");
				break;
			case 'd':
			case 'D':
				MenuMultiplyAndPower();
				system("pause");
				break;
			case 'e':
			case 'E':
				MenuDivide();
				system("pause");
				break;
			case 'f':
			case 'F':
				MenuGCDLCM();
				system("pause");
				break;
			case 'q':
			case 'Q':
				return;
			default:
				break;
		}

	}
}

void MenuCreate(){
	if(PolynNum >= ArraySize){
		// 满了，追加空间
		PolynArray = (Polynomial*)realloc(PolynArray, (ARRAY_INIT_SIZE + ARRAY_INCREMENT) * sizeof(Polynomial));
		if(!PolynArray)exit(OVERFLOW);
		// 存储分配失败
		ArraySize += ARRAY_INCREMENT;
	}
	printf("\nInput Num of Term:");
	unsigned m;
	scanf("%u", &m);
	printf("Input coef & expn:");
	CreatePolyn(*(PolynArray + PolynNum), m);
	PrintPolyn(*(PolynArray + PolynNum));
	PolynNum++;
}

void MenuPrint(){
	for (int i = 0; i < PolynNum; ++i){
		putchar('\n');
		printf("%d:", i);
		PrintPolyn(*(PolynArray + i));
	}
	putchar('\n');
}

void MenuCopy(){
	MenuPrint();
	printf("\nInput Index of Polynomial(start with 0):");
	unsigned index;
	scanf("%u", &index);
	if(index < PolynNum){
		if(PolynNum >= ArraySize){
			// 满了，追加空间
			PolynArray = (Polynomial*)realloc(PolynArray, (ARRAY_INIT_SIZE + ARRAY_INCREMENT) * sizeof(Polynomial));
			if(!PolynArray)exit(OVERFLOW);
			// 存储分配失败
			ArraySize += ARRAY_INCREMENT;
		}
		*(PolynArray + PolynNum) = NULL;
		CopyPolyn(*(PolynArray + PolynNum), *(PolynArray + index));
		PrintPolyn(*(PolynArray + PolynNum));
		PolynNum++;
	}
}

void MenuAdd(){
	MenuPrint();
	printf("\nInput Index of Polynomial A & B(start with 0):");
	unsigned indexA, indexB;
	scanf("%u%u", &indexA, &indexB);
	if(indexA < PolynNum && indexB < PolynNum){
		AddPolyn(*(PolynArray + indexA), *(PolynArray + indexB));
		PrintPolyn(*(PolynArray + indexA));
	}
}

void MenuSubtract(){
	MenuPrint();
	printf("\nInput Index of Polynomial A & B(start with 0):");
	unsigned indexA, indexB;
	scanf("%u%u", &indexA, &indexB);
	if(indexA < PolynNum && indexB < PolynNum){
		SubtractPolyn(*(PolynArray + indexA), *(PolynArray + indexB));
		PrintPolyn(*(PolynArray + indexA));
	}
}

void MenuEvaluate(){
	MenuPrint();
	printf("\nInput Index of Polynomial(start with 0) & value of X:");
	unsigned index;
	double x;
	scanf("%u%lf", &index, &x);
	if(index < PolynNum){
		PrintPolyn(*(PolynArray + index));
		double result;
		EvaluatePolyn(*(PolynArray + index), x, result);
		printf("= %f\n", result);
	}
}

void MenuDestroy(){
	MenuPrint();
	printf("\nInput Index of Polynomial(start with 0):");
	unsigned index;
	scanf("%u", &index);
	if(index < PolynNum){
		PrintPolyn(*(PolynArray + index));
		DestroyPolyn(*(PolynArray + index));
		for (int i = index; i < PolynNum - 1; ++i){
			*(PolynArray + i) = *(PolynArray + i + 1);
		}
		PolynNum > 0 && PolynNum--;
	}
}

void MenuClear(){
	MenuPrint();
	printf("\nInput Index of Polynomial(start with 0):");
	unsigned index;
	scanf("%u", &index);
	if(index < PolynNum){
		PrintPolyn(*(PolynArray + index));
		ClearPolyn(*(PolynArray + index));
	}
}

void MenuChange(){
	MenuPrint();
	printf("Input Index of Polynomial(start with 0):");
	unsigned index;
	scanf("%u", &index);
	if(index < PolynNum){
		PrintPolyn(*(PolynArray + index));

	}
	printf("①插入新的结点、②删除已有结点、③修改已有结点的系数和指数");
	printf("\nInput Num:");
	char c = getche();
	switch(c){
		case '1':{
			double coef;
			int expn;
			printf("\nInput coef & expn:");
			scanf("%lf%d", &coef, &expn);
			if(InsertTerm(*(PolynArray + index), coef, expn)){
				printf("success\n");
				PrintPolyn(*(PolynArray + index));
			}else{
				printf("failed\n");
			}
			break;
		}
		case '2':{
			int expn;
			printf("\nInput expn:");
			scanf("%d", &expn);
			if(DeleteTerm(*(PolynArray + index), expn)){
				printf("success\n");
				PrintPolyn(*(PolynArray + index));
			}else{
				printf("failed\n");
			}
			break;
		}
		case '3':{
			unsigned tremIndex;
			double coef;
			int expn;
			printf("\nInput tremIndex(start with 0) & coef & expn:");
			scanf("%u%lf%d", &tremIndex, &coef, &expn);
			if(ChangeTerm(*(PolynArray + index), tremIndex, coef, expn)){
				// printf("success\n");
				PrintPolyn(*(PolynArray + index));
			}else{
				printf("failed\n");
			}
			break;
		}
		// case 'q':
		// case 'Q':
	}
}

/////////////////////////////////////////////////////




void MenuDiff(){
	MenuPrint();
	printf("\nInput Index of Polynomial(start with 0) & order:");
	unsigned index, order;
	scanf("%u%u", &index, &order);
	if(index < PolynNum && order >= 0){
		DiffPolyn(*(PolynArray + index), order);
		PrintPolyn(*(PolynArray + index));
	}
}

void MenuIndefInt(){
	MenuPrint();
	printf("\nInput Index of Polynomial(start with 0):");
	unsigned index;
	scanf("%u", &index);
	if(index < PolynNum){
		IndefIntegratePolyn(*(PolynArray + index));
		PrintPolyn(*(PolynArray + index));
	}
}

void MenuDefInt(){
	MenuPrint();
	printf("\nInput Index of Polynomial(start with 0) & LowerLimit & UpperLimit:");
	unsigned index;
	double low, up;
	scanf("%u%lf%lf", &index, &low, &up);
	if(index < PolynNum){
		printf("∫[%f,%f]", low, up);
		PrintPolyn(*(PolynArray + index));
		double result;
		DefIntegratePolyn(*(PolynArray + index), low, up, result);
		printf("dx= %f\n", result);
	}
}

void MenuMultiplyAndPower(){
	MenuPrint();
	printf("1.Multiply\n2.Power:\nInput Num:");
	char c = getche();
	switch(c){
		case '1':{
			printf("\nInput Index of Polynomial A & B(start with 0):");
			unsigned indexA, indexB;
			scanf("%u%u", &indexA, &indexB);
			if(indexA < PolynNum && indexB < PolynNum){
				MultiplyPolyn(*(PolynArray + indexA), *(PolynArray + indexB));
				PrintPolyn(*(PolynArray + indexA));
			}
			break;
		}
		case '2':{
			printf("\nInput Index of Polynomial(start with 0) & power:");
			unsigned index, power;
			scanf("%u%u", &index, &power);
			if(index < PolynNum && power >= 0){
				PowerPolyn(*(PolynArray + index), power);
				PrintPolyn(*(PolynArray + index));
			}
			break;
		}
	}
}

void MenuDivide(){
	MenuPrint();
	printf("1.Divide\n2.Modulo:\nInput Num:");
	char c = getche();
	switch(c){
		case '1':{
			printf("\nInput Index of Polynomial A & B(start with 0):");
			unsigned indexA, indexB;
			scanf("%u%u", &indexA, &indexB);
			if(indexA < PolynNum && indexB < PolynNum){
				DividePolyn(*(PolynArray + indexA), *(PolynArray + indexB));
				PrintPolyn(*(PolynArray + indexA));
			}
			break;
		}
		case '2':{
			printf("\nInput Index of Polynomial A & B(start with 0):");
			unsigned indexA, indexB;
			scanf("%u%u", &indexA, &indexB);
			if(indexA < PolynNum && indexB < PolynNum){
				if(PolynNum >= ArraySize){
					// 满了，追加空间
					PolynArray = (Polynomial*)realloc(PolynArray, (ARRAY_INIT_SIZE + ARRAY_INCREMENT) * sizeof(Polynomial));
					if(!PolynArray)exit(OVERFLOW);
					// 存储分配失败
					ArraySize += ARRAY_INCREMENT;
				}
				*(PolynArray + PolynNum) = NULL;
				DividePolyn(*(PolynArray + indexA), *(PolynArray + indexB), *(PolynArray + PolynNum));
				PrintPolyn(*(PolynArray + indexA));
				PrintPolyn(*(PolynArray + PolynNum));
				PolynNum++;
			}
			break;
		}
	}
}

void MenuGCDLCM(){
	MenuPrint();
	printf("1.GCD\n2.LCM:\nInput Num:");
	char c = getche();
	switch(c){
		case '1':{
			printf("\nInput Index of Polynomial A & B(start with 0):");
			unsigned indexA, indexB;
			scanf("%u%u", &indexA, &indexB);
			if(indexA < PolynNum && indexB < PolynNum){
				GCDPolyn(*(PolynArray + indexA), *(PolynArray + indexB));
				PrintPolyn(*(PolynArray + indexA));
			}
			break;
		}
		case '2':{
			printf("\nInput Index of Polynomial A & B(start with 0):");
			unsigned indexA, indexB;
			scanf("%u%u", &indexA, &indexB);
			if(indexA < PolynNum && indexB < PolynNum){
				LCMPolyn(*(PolynArray + indexA), *(PolynArray + indexB));
				PrintPolyn(*(PolynArray + indexA));
			}
			break;
		}
	}
}
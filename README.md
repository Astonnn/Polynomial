# Polynomial

《数据结构与数据库/操作系统》实验测试数据集

实验一、线性表的应用：稀疏一元多项式运算器

<一>基本功能（55分）
1.创建(6分)：
初始多项式：X3+3X2+2X+6
X3-X2+2X-2
2.显示(6分)：
3.复制(6分)： 复制多项式X3+3X2+2X+6
4.和(6分)：2X3+2X2+4X+4
5.差(6分)：4X2+8
6.值(6分)： x=1，X3+3X2+2X+6=12
X3-X2+2X+2=4
7.销毁(6分)： 在其余测试结束后进行检验
8.清空(6分)： 在销毁结束后进行检验
9.修改(7分)：对功能3中复制得到的多项式，增加一项X4删除2X，并将3X2变为4X2

<二>扩展功能（每个功能5分，上不封顶）
10.微分(5分)：N=1  ：X3+3X2+2X+6→3X2+6X+2
11.不定积分(5分)： 
12.定积分(5分)： 

13.乘法和乘方(5分)： 
注：进行乘法、乘方、除法检验时，需再创建一个新的多项式 X2+1
乘法  (X2+3X+2X+6) * (X3-X2+2X-2) = X6+2X5+X4+8X3-8X2+8X-12
乘方  (X2+1)3 = X6+3X4+3X2+1

14. 除法(5分)：
(X3+3X2+2X+6)/(X2+1) = X+3（商）....X+3（余数）

15.最大公约式和最小公倍式(5分)：

16.多项式的四则运算(5分)：
注：进行四则运算时，需再创建一个新的多项式 X
((X3+3X2+2X+6)-(X3-X2+2X-2))*(X2+1)/X = 4X5+4X3+8X（商）……8（余数）

<三>健壮性（10分）
输入X3-X2+2X-2时，按X3、-X2、+2X、-2顺序输入 和 按-2、X3、-X2、+2X顺序输入时，结果显示的是否相同(2分)
极端数据测试: \int_{5}^{5}{X^3+3X^2+2X+6} dx = 0 （2分）
(X2+1)0=1（3分）
复制并不存在的某一项，程序不发生错误并汇报不能复制的原因(3分)

<四>规范性（10分）
代码注释（3分）
程序模块化（3分）
人机交互友好（4分）

<五>按时性（10分）
注：若未达到要求，即扣分，扣完为止。
1.实验按时完成  (未达到要求扣10分)
2.不存在早退或迟到现象 (未达到要求扣3分/次)
3.不存在无缘故缺课现象(未达到要求扣5分/次)
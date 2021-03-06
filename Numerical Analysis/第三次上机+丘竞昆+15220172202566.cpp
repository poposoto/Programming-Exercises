/* Step 1: 导入头文件+宏定义 */
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

/* Step 2: 按书p.75实现复化梯形数值积分算法 */
void trapezium(double LowerBound, double UpperBound, auto integrand)
{
	int n = 1, i;
	double T_new, T_old, T_delta, epsilon=1e-10;
	double b = UpperBound, a = LowerBound;
	auto f = (*integrand);
	
	T_new = (b - a) / 2 * (f(a) + f(b));
	do {
		T_old = T_new;
		T_delta = 0;
		for (i = 1; i <= n; i++)
			T_delta = T_delta + f(a + (2 * i - 1) * (b - a) / 2 / n);
		T_delta = T_delta * (b - a) / n;
		T_new = (T_old + T_delta) / 2;
		n = 2 * n;
	} while (fabs(T_new - T_old) > epsilon);
	n = n / 2;
	
	printf("T2n = %.16f, n = %d\n", T_new, n);
}

/* Step 3: 按书p.76实现复化抛物线数值积分算法 */
void parabola(double LowerBound, double UpperBound, auto integrand)
{
	int n = 2, i;
	double T_new, T_old, T_delta, S_new, S_old, epsilon=1e-10;
	double b = UpperBound, a = LowerBound;
	auto f = (*integrand);
	
	T_old = (b - a) / 2 * (f(a) + f(b));
	T_delta = (b - a) * f((a + b) / 2);
	T_new = (T_old + T_delta) / 2;
	S_new = (4 * T_new - T_old) / 3;
	do {
		T_old = T_new;
		S_old = S_new;
		T_delta = 0;
		for (i = 1; i <= n; i++)
			T_delta = T_delta + f(a + (2 * i - 1) * (b - a) / 2 / n);
		T_delta = T_delta * (b - a) / n;
		T_new = (T_old + T_delta) / 2;
		S_new = (4 * T_new - T_old) / 3;
		n = 2 * n;
	} while (fabs(S_new - S_old) > epsilon);
	n = n / 2;
	
	printf("S2n = %.16f, n = %d\n", S_new, n);
}

/* Step 4: 分别将题给三个被积函数及相应的积分区间代入上述算法 */
int main(int argc, char *argv[])
{
	printf("x -> sin(x) / x from 1 to 2\n");
	auto f1 = [](double x)->double{ return sin(x) / x; };
	trapezium(1, 2, f1);
	parabola(1, 2, f1);
	
	printf("\nx -> 1 / (log(x) * log(x) * log(x)) from 2 to 3\n");
	auto f2 = [](double x)->double{ return 1 / (log(x) * log(x) * log(x)); };
	trapezium(2, 3, f2);
	parabola(2, 3, f2);
	
	printf("\nx -> cos(x) from 0 to pi / 2\n");
	trapezium(0, M_PI_2, cos);
	parabola(0, M_PI_2, cos);
}

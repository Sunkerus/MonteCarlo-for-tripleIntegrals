 //Подключение необходимых библиотек
#include <iostream>
#include <random>
#include <omp.h>
#include <cmath>
//Функция с интересующим нас интегралом
double func(double x, double y, double z) {
return 8*y*y+z*exp(2*x*y*z);
 }
 using std::cout;
 using std::endl;
 //Границы интегрирования
 const double a = 0.0, b = 2, c = 0.0, d = 1.0, e = -1.0, f = 0 ;
 const uint64_t n = 100000;


 int main() {
setlocale(LC_ALL, "Rus");
double sum = 0.0;
//Генератор случайных величин
std::default_random_engine randomize;
 //Первоначальные и последующие состояния
 #pragma omp parallel
{
uint32_t seed;
 #pragma omp critical
{
seed = randomize();
}
std::mt19937 gen(seed);
std::uniform_real_distribution<double> unirnd(0.0, 1.0);
#pragma omp for reduction (+ : sum)
double x, y, z, ans;
 //Расчёт для каждого аргумента
for (uint64_t i = 0; i <= n; i++) {
x = a + (b - a) * unirnd(gen);
y = c + (d - c) * unirnd(gen);
z = e + (f - e) * unirnd(gen);
sum += func(x, y, z);
}
ans = sum * (b - a) * (d - c) * (f - e) / n;
//Вывод ответа
cout << "Исходный тройной интеграл:\iiint(8*y*y+z*exp(2*x*y*z))dxdydz = "<<"\n\n"<< ans;
}
return 0;
}
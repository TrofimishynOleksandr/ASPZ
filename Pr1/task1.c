#include <stdio.h>
#include <math.h>

// Функція для обчислення коренів квадратного рівняння
void solve_quadratic(double a, double b, double c) {
    double D = b * b - 4 * a * c;
    if (D > 0) {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        printf("Два дійсних корені: x1 = %.2f, x2 = %.2f\n", x1, x2);
    } else if (D == 0) {
        double x = -b / (2 * a);
        printf("Один дійсний корінь: x = %.2f\n", x);
    } else {
        double real = -b / (2 * a);
        double imag = sqrt(-D) / (2 * a);
        printf("Комплексні корені: x1 = %.2f + %.2fi, x2 = %.2f - %.2fi\n", real, imag, real, imag);
    }
}

// Функція для обчислення коренів кубічного рівняння
void solve_cubic(double a, double b, double c, double d) {
    if (a == 0) {
        printf("Це не кубічне рівняння!\n");
        return;
    }
    
    double A = b / a, B = c / a, C = d / a;
    double Q = (3 * B - A * A) / 9;
    double R = (9 * A * B - 27 * C - 2 * A * A * A) / 54;
    double D = Q * Q * Q + R * R;
    
    if (D > 0) {
        double S = cbrt(R + sqrt(D));
        double T = cbrt(R - sqrt(D));
        double x1 = S + T - A / 3;
        printf("Один дійсний корінь: x = %.2f\n", x1);
    } else if (D == 0) {
        double S = cbrt(R);
        double x1 = 2 * S - A / 3;
        double x2 = -S - A / 3;
        printf("Два або три дійсних корені: x1 = %.2f, x2 = %.2f\n", x1, x2);
    } else {
        double theta = acos(R / sqrt(-Q * Q * Q));
        double x1 = 2 * sqrt(-Q) * cos(theta / 3) - A / 3;
        double x2 = 2 * sqrt(-Q) * cos((theta + 2 * M_PI) / 3) - A / 3;
        double x3 = 2 * sqrt(-Q) * cos((theta + 4 * M_PI) / 3) - A / 3;
        printf("Три дійсних корені: x1 = %.2f, x2 = %.2f, x3 = %.2f\n", x1, x2, x3);
    }
}

int main() {
    int choice;
    printf("Оберіть тип рівняння:\n1 - Квадратне (ax^2 + bx + c = 0)\n2 - Кубічне (ax^3 + bx^2 + cx + d = 0)\nВибір: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        double a, b, c;
        printf("Введіть коефіцієнти a, b, c через пробіл: ");
        scanf("%lf %lf %lf", &a, &b, &c);
        if (a == 0) {
            printf("Це не квадратне рівняння!\n");
        } else {
            solve_quadratic(a, b, c);
        }
    } else if (choice == 2) {
        double a, b, c, d;
        printf("Введіть коефіцієнти a, b, c, d через пробіл: ");
        scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
        solve_cubic(a, b, c, d);
    } else {
        printf("Невірний вибір!\n");
    }
    return 0;
}
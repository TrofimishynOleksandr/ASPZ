# Solving quadratic and cubic equations on C

## Description

This C program is designed to calculate the roots of quadratic and cubic equations, taking into account all possible cases:

- Two real roots

- One real root

- Complex roots (for a quadratic equation)

- Three real roots (for a cubic equation)

## Requirements

A C compiler (such as GCC).

## Compilation

The program is compiled using GCC.
You need to add the ```-lm``` flag to include the math library.
```
gcc -Wall task1.c -o task1 -lm
```
## Execution

```
./task1
```
## Usage

After executing, the program will prompt you to select the equation type:

```
Оберіть тип рівняння:
1 - Квадратне (ax^2 + bx + c = 0)
2 - Кубічне (ax^3 + bx^2 + cx + d = 0)
Вибір:
```

Enter ```1``` for a quadratic equation or ```2``` for a cubic equation, then enter the coefficients of the equation.

### Input and output examples
#### Example 1: Quadratic equation with two roots
#### Input data:
```
1
1 -3 2
```
#### Output data:
```
Два дійсних корені: x1 = 2.00, x2 = 1.00
```
#### Example 2: Quadratic equation with complex roots
#### Input data:
```
1
1 1 1
```
#### Output data:
```
Комплексні корені: x1 = -0.50 + 0.87i, x2 = -0.50 - 0.87i
```
#### Example 3: Cubic equation with three real roots
#### Input data:
```
2
1 -6 11 -6
```
#### Output data:
```
Три дійсних корені: x1 = 3.00, x2 = 2.00, x3 = 1.00
```
## Dependencies
The program uses the ```math.h``` library, so you need to add ```-lm``` when compiling.

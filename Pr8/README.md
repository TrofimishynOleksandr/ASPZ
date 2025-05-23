
# Практична робота №8

## Завдання 1

Чи може виклик count = write(fd, buffer, nbytes); повернути в змінній count значення, відмінне від nbytes? Якщо так, то чому? Наведіть робочий приклад програми, яка демонструє вашу відповідь.

### Реалізація

Так, може. Це трапляється, якщо:

-   запис йде в неблокуючий файловий дескриптор (наприклад, сокет або pipe);
-   сталося часткове заповнення буфера (через обмеження ядра);
-   файлова система обмежена (немає місця на диску або ліміт квоти);
-   сигнал перервав операцію.

```shell
admin@FreeBSD:~/ASPZ/Pr8 % gcc -Wall task1.c -o task1
admin@FreeBSD:~/ASPZ/Pr8 % ./task1
Partial write: wrote 65536 bytes out of 100000
admin@FreeBSD:~/ASPZ/Pr8 %
```

## Завдання 2

Є файл, дескриптор якого — fd. Файл містить таку послідовність байтів: 4, 5, 2, 2, 3, 3, 7, 9, 1, 5. У програмі виконується наступна послідовність системних викликів:

lseek(fd, 3, SEEK_SET);

read(fd, &buffer, 4);

де виклик lseek переміщує покажчик на третій байт файлу. Що буде містити буфер після завершення виклику read? Наведіть робочий приклад програми, яка демонструє вашу відповідь.

### Реалізація


**Умова:** Файл: байти `4, 5, 2, 2, 3, 3, 7, 9, 1, 5`  
Виконано:
```
lseek(fd, 3, SEEK_SET);
read(fd, &buffer, 4);
``` 

Результат: Буфер міститиме байти `2, 3, 3, 7`.

```shell
admin@FreeBSD:~/ASPZ/Pr8 % gcc -Wall task2.c -o task2
admin@FreeBSD:~/ASPZ/Pr8 % ./task2
Buffer contents: 2 3 3 7 
admin@FreeBSD:~/ASPZ/Pr8 %
```

## Завдання 3

Бібліотечна функція qsort призначена для сортування даних будь-якого типу. Для її роботи необхідно підготувати функцію порівняння, яка викликається з qsort кожного разу, коли потрібно порівняти два значення.

Оскільки значення можуть мати будь-який тип, у функцію порівняння передаються два вказівники типу void* на елементи, що порівнюються.

Напишіть програму, яка досліджує, які вхідні дані є найгіршими для алгоритму швидкого сортування. Спробуйте знайти кілька масивів даних, які змушують qsort працювати якнайповільніше. Автоматизуйте процес експериментування так, щоб підбір і аналіз вхідних даних виконувалися самостійно.

Придумайте і реалізуйте набір тестів для перевірки правильності функції qsort.

### Реалізація

Аналіз результатів:

Sorted (відсортовані дані): ~0.06-0.09 секунди
Reverse sorted (зворотно відсортовані дані): ~0.09-0.12 секунди
Equal (всі елементи однакові): ~0.04 секунди
Random (випадкові дані): ~0.72-1.33 секунди

Виходить, що найгіршим набором вхідних даних є випадковий, а найкращим - набір з однаковими даними.

```shell
admin@FreeBSD:~/ASPZ/Pr8 % gcc -Wall task3.c -o task3
admin@FreeBSD:~/ASPZ/Pr8 % ./task3
Sorted          | Time: 0.09375  sec | PASS
Sorted          | Time: 0.06250  sec | PASS
Sorted          | Time: 0.08594  sec | PASS
Reverse sorted  | Time: 0.09375  sec | PASS
Reverse sorted  | Time: 0.11719  sec | PASS
Reverse sorted  | Time: 0.12500  sec | PASS
Equal           | Time: 0.03906  sec | PASS
Equal           | Time: 0.03906  sec | PASS
Equal           | Time: 0.03906  sec | PASS
Random          | Time: 1.32812  sec | PASS
Random          | Time: 0.71875  sec | PASS
Random          | Time: 1.25781  sec | PASS
admin@FreeBSD:~/ASPZ/Pr8 %
```

## Завдання 4

Виконайте наступну програму на мові програмування С:
```c
int main() {
  int pid;
  pid = fork();
  printf("%d\n", pid);
}
```
Завершіть цю програму. Припускаючи, що виклик fork() був успішним, яким може бути результат виконання цієї програми?

### Реалізація

Програма виведе два числа:

Спочатку батьківський процес виведе PID дочірнього процесу (11720).

Потім дочірній процес виведе 0.

```shell
admin@FreeBSD:~/ASPZ/Pr8 % gcc -Wall task4.c -o task4
admin@FreeBSD:~/ASPZ/Pr8 % ./task4
11720
0
admin@FreeBSD:~/ASPZ/Pr8 %
```

## Завдання по варіанту 21

Реалізуйте аналог tail -f без використання select(), poll() або inotify.

### Опис рішення

У реалізації регулярно перевіряється розмір файлу і зчитуються нові дані в циклі з затримкою (`sleep`).

### Запуск програми

Створюємо файл:

```shell
admin@FreeBSD:~/ASPZ/Pr8 % echo "Hello" > test.log
```

Запускаємо програму:

```shell
admin@FreeBSD:~/ASPZ/Pr8 % gcc -Wall task21variant.c -o task21variant
admin@FreeBSD:~/ASPZ/Pr8 % ./task21variant test.log

```

Після чого у іншому терміналі записуємо дані у файл:

```shell
admin@FreeBSD:~/ASPZ/Pr8 % echo "World" >> test.log
admin@FreeBSD:~/ASPZ/Pr8 % echo "!" >> test.log
admin@FreeBSD:~/ASPZ/Pr8 %
```

У результаті програма зчитає зміни:

```shell
admin@FreeBSD:~/ASPZ/Pr8 % gcc -Wall task21variant.c -o task21variant
admin@FreeBSD:~/ASPZ/Pr8 % ./task21variant test.log
World
!
```

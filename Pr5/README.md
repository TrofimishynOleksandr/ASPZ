
# Практична робота №5

## Завдання по варіанту 21

Напишіть програму, в якій помилка читання одного байта за межами буфера призводить до пошкодження іншого модуля.

## Опис рішення

Написано програму що демонструє помилку читання за межами буфера, що призводить до пошкодження даних в іншому модулі (змінній).

-   Створюється буфер з 5 байтів.
-   В нього копіюється рядок "ABCDEFG" (який має 8 байтів з '\0').
-   Це призводить до переписування пам'яті, яка знаходиться після buffer, включно з полем secret.
-   В результаті значення secret змінюється (тобто пошкоджується).

## Запуск програми

```shell
admin@FreeBSD:~/ASPZ/Pr5 % gcc task21variant.c -o task21variant
task21variant.c: In function 'main':
task21variant.c:10:5: warning: '__builtin_memcpy' writing 8 bytes into a region of size 5 overflows the destination [-Wstringop-overflow=]
   10 |     strcpy(buffer, "ABCDEFG");
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~
task21variant.c:5:10: note: destination object 'buffer' of size 5
    5 |     char buffer[5];
      |          ^~~~~~
admin@FreeBSD:~/ASPZ/Pr5 % ./task21variant
Before: secret = 12345
After: secret = 18246
admin@FreeBSD:~/ASPZ/Pr5 %
```

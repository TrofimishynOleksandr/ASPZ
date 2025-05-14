
# Практична робота №4

## Завдання 1

Скільки пам’яті може виділити malloc(3) за один виклик? 
-   На 64-бітній платформі `size_t` = 8 байт, отже `SIZE_MAX = 2^64 - 1`.
-   Але реально ОС не дозволяє виділити 16 ексабайт через:
    -   Обмеження віртуального адресного простору,
    -   Ліміти ОС (ulimits, фізична пам'ять),
    -   Питання вирівнювання.

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task1.c -o task1
admin@FreeBSD:~/ASPZ/Pr4 % ./task1
sizeof(size_t) = 8 bytes
Maximum size_t = 18446744073709551615
malloc failed: Cannot allocate memory
admin@FreeBSD:~/ASPZ/Pr4 % gcc task1.c -m32 -o task1
admin@FreeBSD:~/ASPZ/Pr4 % ./task1
sizeof(size_t) = 4 bytes
Maximum size_t = 4294967295
malloc failed: Cannot allocate memory
admin@FreeBSD:~/ASPZ/Pr4 %
```

## Завдання 2

Що станеться, якщо передати malloc(3) від’ємний аргумент? 
-   Якщо `num` переповнений і став від’ємним -> `malloc()` бачить негативне число як велике `size_t`.
-   `malloc()` не перевіряє "знаковість", а просто інтерпретує значення.

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task2.c -o task2
admin@FreeBSD:~/ASPZ/Pr4 % ./task2
xa = 1000000, xb = 1000000, num = -727379968 (overflowed)
malloc failed: cannot allocate 18446744072982171648 bytes
admin@FreeBSD:~/ASPZ/Pr4 % gcc task2.c -m32 -o task2
admin@FreeBSD:~/ASPZ/Pr4 % ./task2
xa = 1000000, xb = 1000000, num = -727379968 (overflowed)
malloc failed: cannot allocate 3567587328 bytes
admin@FreeBSD:~/ASPZ/Pr4 %
```

## Завдання 3

Що станеться, якщо використати malloc(0)?

-   Поведінка `malloc(0)` **не визначена** за стандартом C.
-   Деякі реалізації повертають `NULL`, інші — валідний вказівник, який можна передати в `free()`.

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task3.c -o task3
admin@FreeBSD:~/ASPZ/Pr4 % ./task3
malloc(0) returned non-NULL pointer: 0x3a1674c08008
admin@FreeBSD:~/ASPZ/Pr4 % ltrace ./task3
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820f9a840, 0x820f9a850, 0x7ada68ffcc0, 0x400652 <unfinished ...>
malloc(0)                                                                                                  = 0x8947a408008
printf("malloc(0) returned non-NULL poin"...malloc(0) returned non-NULL pointer: 0x8947a408008
)                                                              = 51
free(0x8947a408008)                                                                                        = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/Pr4 %
```

## Завдання 4

**Проблема:**
-   Ми виділяємо пам’ять лише один раз (на першій ітерації), але звільняємо її **на кожній**.
-   На 2+ ітерації — ми працюємо з **вже звільненою** пам’яттю.

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task4_2.c -o task4_2
admin@FreeBSD:~/ASPZ/Pr4 % ./task4_2
ptr: Hello
ptr: Hello
ptr: Hello
admin@FreeBSD:~/ASPZ/Pr4 % ltrace ./task4_2
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x8209fb7a0, 0x8209fb7b0, 0x3774d935acc0, 0x400612 <unfinished ...>
malloc(8)                                                                                                  = 0x10cbc2c08008
printf("ptr: %s\n", "Hello"ptr: Hello
)                                                                               = 11
free(0x10cbc2c08008)                                                                                       = <void>
malloc(8)                                                                                                  = 0x10cbc2c08008
printf("ptr: %s\n", "Hello"ptr: Hello
)                                                                               = 11
free(0x10cbc2c08008)                                                                                       = <void>
malloc(8)                                                                                                  = 0x10cbc2c08008
printf("ptr: %s\n", "Hello"ptr: Hello
)                                                                               = 11
free(0x10cbc2c08008)                                                                                       = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/Pr4 %
```

## Завдання 5

Що станеться, якщо realloc(3) не зможе виділити пам’ять?

Якщо realloc() не може виділити новий блок, воно повертає NULL, але старий ptr залишається валідним.

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task5.c -o task5
admin@FreeBSD:~/ASPZ/Pr4 % ./task5
realloc failed: Cannot allocate memory
admin@FreeBSD:~/ASPZ/Pr4 %
```

## Завдання 6

Що станеться, якщо realloc(3) викликати з NULL або size == 0?

realloc(NULL, size) еквівалентно malloc(size).

realloc(ptr, 0) працює.

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task6.c -o task6
admin@FreeBSD:~/ASPZ/Pr4 % ./task6
realloc(NULL, 128) = 0x16c654809000
realloc(ptr, 0) = 0x16c654808008
admin@FreeBSD:~/ASPZ/Pr4 %
```

## Завдання 7

Переписано код, використовуючи reallocarray(3)

Досліджено за допомогою ltrace

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task7_1.c -o task7_1
admin@FreeBSD:~/ASPZ/Pr4 % ./task7_1
Memory allocated for 1000 elements
Memory reallocated to 500 elements
admin@FreeBSD:~/ASPZ/Pr4 % ltrace ./task7_1
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820f683c8, 0x820f683d8, 0x2024b3e9dcc0, 0x400662 <unfinished ...>
calloc(1000, 4)                                                                                          = 0x38614f609000
printf("Memory allocated for %d elements"..., 1000Memory allocated for 1000 elements
)                                                      = 35
realloc(0x38614f609000, 2000)                                                                            = 0x38614f613000
printf("Memory reallocated to %d element"..., 500Memory reallocated to 500 elements
)                                                       = 35
free(0x38614f613000)                                                                                     = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/Pr4 % gcc task7_2.c -o task7_2
admin@FreeBSD:~/ASPZ/Pr4 % ./task7_2
Memory allocated for 1000 elements
Memory reallocated to 500 elements
admin@FreeBSD:~/ASPZ/Pr4 % ltrace ./task7_2
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x82078c6d8, 0x82078c6e8, 0x877428fdcc0, 0x4006c2 <unfinished ...>
calloc(1000, 4)                                                                                          = 0x1772b9c09000
printf("Memory allocated for %zu element"..., 1000Memory allocated for 1000 elements
)                                                      = 35
reallocarray(0x1772b9c09000, 500, 4, 500, 0x8217eb618)                                                   = 0x1772b9c13000
printf("Memory reallocated to %zu elemen"..., 500Memory reallocated to 500 elements
)                                                       = 35
free(0x1772b9c13000)                                                                                     = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/Pr4 %
```

## Завдання по варіанту 21

Перевірено роботу malloc у середовищі з обмеженим обсягом пам’яті.

```shell
admin@FreeBSD:~/ASPZ/Pr4 % gcc task21variant.c -o task21variant
admin@FreeBSD:~/ASPZ/Pr4 % ./task21variant
Allocated 1 MB
Allocated 2 MB
Allocated 3 MB
Allocated 4 MB
Allocated 5 MB
Allocated 6 MB
malloc: Cannot allocate memory
Total allocated before failure: 6 MB
admin@FreeBSD:~/ASPZ/Pr4 %
```

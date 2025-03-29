# Практична робота №2
## Завдання 1
### Визначення моменту, коли time_t закінчиться
- **32-бітна архітектура:**  
  Максимальне значення time_t: 2147483647  
  Дата і час: Tue Jan 19 05:14:07 2038
- **64-бітна архітектура:**  
  Максимальне значення time_t: 9223372036854775807  
  Дата і час: (null) (ctime не може перевести)

### Вивід у консолі
```shell
admin@FreeBSD:~/ASPZ/Pr2 % gcc -m32 task1.c -o task1
admin@FreeBSD:~/ASPZ/Pr2 % ./task1
Максимальне значення time_t: 2147483647
Дата і час: Tue Jan 19 05:14:07 2038

admin@FreeBSD:~/ASPZ/Pr2 % gcc -m32 task1.c -o time_check32
admin@FreeBSD:~/ASPZ/Pr2 % gcc -m64 task1.c -o time_check64
admin@FreeBSD:~/ASPZ/Pr2 % ./time_check32
Максимальне значення time_t: 2147483647
Дата і час: Tue Jan 19 05:14:07 2038

admin@FreeBSD:~/ASPZ/Pr2 % ./time_check64
Максимальне значення time_t: 9223372036854775807
Дата і час: (null)
```

## Завдання 2
### Аналіз впливу змін у коді на розмір виконуваного файлу та сегменти пам'яті

У цій роботі досліджено, як різні конструкції в коді та параметри компіляції впливають на розмір виконуваного файлу, а також на розподіл пам’яті між сегментами `.text`, `.data` та `.bss`.  
Метою експерименту є визначення, які зміни призводять до збільшення чи зменшення розміру файлу та як працює управління пам’яттю у виконуваних файлах.

### Вивід у консолі
```shell
admin@FreeBSD:~/ASPZ/Pr2 % gcc task2_1.c -o task2_1
admin@FreeBSD:~/ASPZ/Pr2 % ls -l task2_1
-rwxr-xr-x  1 admin admin 8200 Mar 29 01:08 task2_1
admin@FreeBSD:~/ASPZ/Pr2 % size task2_1
   text	   data	    bss	    dec	    hex	filename
   1079	    552	     16	   1647	    66f	task2_1
admin@FreeBSD:~/ASPZ/Pr2 % gcc task2_2.c -o task2_2
admin@FreeBSD:~/ASPZ/Pr2 % ls -l task2_2
-rwxr-xr-x  1 admin admin 8232 Mar 29 01:08 task2_2
admin@FreeBSD:~/ASPZ/Pr2 % size task2_2
   text	   data	    bss	    dec	    hex	filename
   1079	    552	   4032	   5663	   161f	task2_2
admin@FreeBSD:~/ASPZ/Pr2 % gcc task2_3.c -o task2_3
admin@FreeBSD:~/ASPZ/Pr2 % ls -l task2_3
-rwxr-xr-x  1 admin admin 8232 Mar 29 01:08 task2_3
admin@FreeBSD:~/ASPZ/Pr2 % size task2_3
   text	   data	    bss	    dec	    hex	filename
   1079	    552	   4032	   5663	   161f	task2_3
admin@FreeBSD:~/ASPZ/Pr2 % gcc task2_4.c -o task2_4
admin@FreeBSD:~/ASPZ/Pr2 % ls -l task2_4
-rwxr-xr-x  1 admin admin 8320 Mar 29 01:08 task2_4
admin@FreeBSD:~/ASPZ/Pr2 % size task2_4
   text	   data	    bss	    dec	    hex	filename
   1167	    552	     16	   1735	    6c7	task2_4
admin@FreeBSD:~/ASPZ/Pr2 % gcc task2_4.c -g -o task2_4
admin@FreeBSD:~/ASPZ/Pr2 % ls -l task2_4
-rwxr-xr-x  1 admin admin 9096 Mar 29 01:09 task2_4
admin@FreeBSD:~/ASPZ/Pr2 % size task2_4
   text	   data	    bss	    dec	    hex	filename
   1167	    552	     16	   1735	    6c7	task2_4
admin@FreeBSD:~/ASPZ/Pr2 % gcc task2_4.c -O3 -o task2_4
admin@FreeBSD:~/ASPZ/Pr2 % ls -l task2_4
-rwxr-xr-x  1 admin admin 8264 Mar 29 01:10 task2_4
admin@FreeBSD:~/ASPZ/Pr2 % size task2_4
   text	   data	    bss	    dec	    hex	filename
   1118	    552	     16	   1686	    696	task2_4
```
### Пояснення
#### Базова програма (`task2_1.c`)
Це стандартна програма "Hello, World!". Вона містить лише основний код, тому сегмент 
`.text` займає близько 1КБ, а `.data` та `.bss` залишаються мінімальними.

#### Додавання глобального масиву (`task2_2.c`)
Неініціалізований масив i`nt arr[1000];` додає 4КБ до `.bss`. Це не збільшує файл, але 
вимагає більше пам’яті під час виконання.

#### Додавання ініціалізованого масиву (`task2_3.c`)
Масив `int arr[1000] = {0};` переміщається у `.data`, збільшуючи файл. Розмір `.bss` 
повертається до мінімального.

#### Локальні масиви (`task2_4.c`)
Локальні масиви у функціях виділяються у стеку, тому `.bss` та `.data` не змінюються. Проте 
`.text` збільшується через додатковий код.

#### Компіляція з `-g`
Налагоджувальна інформація збільшує розмір файлу, але не впливає на `size`.

#### Оптимізація `-O3`
Код `.text` стає меншим, оскільки компілятор оптимізує програму.

## Завдання 3


### Визначення вершини стека (`task3_1.c`)
Вершина стека знаходиться приблизно за адресою `0x8208821bc`.

### Розташування сегментів пам’яті (`task3_2.c`)
- **Сегмент тексту:** знаходиться в області `0x400600`.

- **Сегмент даних:** глобальні змінні розташовані біля `0x401b60`.

- **Сегмент BSS:** знаходиться неподалік від сегмента даних (`0x401b64`).

- **Купа (heap):** динамічна пам'ять починається в районі `0x3b2510608008` і зростає вгору.

- **Стек (stack):** локальні змінні розташовані біля `0x8211692f4`, і стек росте вниз.

- **Зміна вершини стека після виділення пам’яті:** після виклику функції вершина стека
змістилася до `0x8210692e0`, що підтверджує, що стек росте вниз.

### Вивід у консолі
```shell
admin@FreeBSD:~/ASPZ/Pr2 % gcc task3_1.c -o task3_1
admin@FreeBSD:~/ASPZ/Pr2 % ./task3_1
The stack top is near 0x8208821bc
admin@FreeBSD:~/ASPZ/Pr2 % gcc task3_2.c -o task3_2
admin@FreeBSD:~/ASPZ/Pr2 % ./task3_2
Text segment (function): 0x400662
Data segment (global var): 0x401b60
Data segment (static var): 0x401b64
Heap (malloc): 0x3b2510608008
Stack (local var): 0x8211692f4
After allocation, stack top is near 0x8210692e0
```

## Завдання 4

### Вивід програми

```shell
admin@FreeBSD:~/ASPZ/Pr2 % gcc task4.c -o task4
admin@FreeBSD:~/ASPZ/Pr2 % ./task4
In function                 main; &localvar = 0x820540f9c
In function                  foo; &localvar = 0x820540f6c
In function                  bar; &localvar = 0x820540f4c
In function    bar_is_now_closed; &localvar = 0x820540f2c

 Now blocking on pause()...
```

### Вивід gdb
```shell
admin@FreeBSD:~/ASPZ/Pr2 % pgrep task4
2335
admin@FreeBSD:~/ASPZ/Pr2 % gdb --quiet -p 2335
Attaching to process 2335
Reading symbols from /home/admin/ASPZ/Pr2/task4...
Reading symbols from /lib/libc.so.7...
(No debugging symbols found in /lib/libc.so.7)
Reading symbols from /libexec/ld-elf.so.1...
(No debugging symbols found in /libexec/ld-elf.so.1)
0x000000082266a77a in _sigsuspend () from /lib/libc.so.7
(gdb) bt
#0  0x000000082266a77a in _sigsuspend () from /lib/libc.so.7
#1  0x00000008225e0c35 in pause () from /lib/libc.so.7
#2  0x000000000040068b in bar_is_now_closed ()
#3  0x00000000004006bd in bar ()
#4  0x00000000004006ef in foo ()
#5  0x0000000000400728 in main ()
```

## Завдання 5

Ні, без IP не обійтись. Він вказує, яку команду виконувати далі. 
Стек лише зберігає адреси повернення при викликах процедур. 
Якщо замінити IP вершиною стека, довелося б щоразу вручну оновлювати 
стек після кожної інструкції, що зробило б виконання коду складним і повільним.

## Завдання 21 варіанту

Використано valgrind для профілювання пам’яті.

### Вивід програми

```shell
admin@FreeBSD:~/ASPZ/Pr2 % clang -fsanitize=address -g task21.c -o task21
admin@FreeBSD:~/ASPZ/Pr2 % valgrind --leak-check=full ./task21
==2476== Memcheck, a memory error detector
==2476== Copyright (C) 2002-2024, and GNU GPL’d, by Julian Seward et al.
==2476== Using Valgrind-3.24.0 and LibVEX; rerun with -h for copyright info
==2476== Command: ./task21
==2476== 
=================================================================
==2476==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x506000000052 at pc 0x0000002ae875 bp 0x7fffffffe590 sp 0x7fffffffdd40
WRITE of size 63 at 0x506000000052 thread T0
    #0 0x2ae874 in strcpy /usr/src/contrib/llvm-project/compiler-rt/lib/asan/asan_interceptors.cpp:556:5
    #1 0x2ed713 in memory_leak /home/admin/ASPZ/Pr2/task21.c:7:5
    #2 0x2ed793 in main /home/admin/ASPZ/Pr2/task21.c:19:5
    #3 0x800456c39 in __libc_start1 (/lib/libc.so.7+0x85c39)
    #4 0x249d7f in _start /usr/src/lib/csu/amd64/crt1_s.S:83

0x506000000052 is located 0 bytes after 50-byte region [0x506000000020,0x506000000052)
allocated by thread T0 here:
    #0 0x2b9eaf in malloc /usr/src/contrib/llvm-project/compiler-rt/lib/asan/asan_malloc_linux.cpp:68:3
    #1 0x2ed701 in memory_leak /home/admin/ASPZ/Pr2/task21.c:6:18
    #2 0x2ed793 in main /home/admin/ASPZ/Pr2/task21.c:19:5
    #3 0x800456c39 in __libc_start1 (/lib/libc.so.7+0x85c39)
    #4 0x249d7f in _start /usr/src/lib/csu/amd64/crt1_s.S:83
    #5 0x800314007  (<unknown module>)

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/admin/ASPZ/Pr2/task21.c:7:5 in memory_leak
Shadow bytes around the buggy address:
  0x505ffffffd80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x505ffffffe00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x505ffffffe80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x505fffffff00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x505fffffff80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x506000000000: fa fa fa fa 00 00 00 00 00 00[02]fa fa fa fa fa
  0x506000000080: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x506000000100: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x506000000180: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x506000000200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x506000000280: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==2476==ABORTING
```

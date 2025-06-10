
# Практична робота №12-13

## Завдання за варіантом 21

Створіть фреймворк, який дозволяє будь-якому додатку підключити власний логгер падіння (core-dump обробник), не впливаючи на основну логіку.

### Опис

Ця програма демонструє обробку фатальних помилок (наприклад, segmentation fault) за допомогою власного обробника сигналів (`SIGSEGV`, `SIGABRT` тощо). У разі аварійного завершення:

-   створюється файл `crash.log`,    
-   записується стек викликів (stack trace),
-   фіксується час помилки.
    
Обробник працює незалежно від логіки програми і не впливає на основний потік.

### Вивід у консоль

```shell
admin@FreeBSD:~/ASPZ/Pr12-13 % gcc -o task21variant task21variant.c crash_logger.c -g -lexecinfo
admin@FreeBSD:~/ASPZ/Pr12-13 % ./task21variant
admin@FreeBSD:~/ASPZ/Pr12-13 %
```


### Вивід у crash.log

```
=== Crash Report ===
Signal: 11 (Segmentation fault)
Fault address: 0x0
Sender PID: 0
0x400967 <crash_handler+0xda> at /home/admin/ASPZ/Pr12-13/task21variant
0x8217072d3 <_fini+0x82130689b> at ???
0x400880 <main+0x1e> at /home/admin/ASPZ/Pr12-13/task21variant
0x822b7bc3a <__libc_start1+0x12a> at /lib/libc.so.7
=== End of Report ===
```

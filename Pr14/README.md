
# Практична робота №14

## Завдання за варіантом 21

Дослідіть поведінку таймерів у багатопоточному додатку — створіть таймер у кожному потоці і порівняйте результат.

### Опис

Ця програма дозволяє вибрати один із двох режимів:

1.  Відображення цифрового годинника за допомогою `setitimer`.
2.  Запуск POSIX-таймерів у кількох потоках для демонстрації паралельної роботи таймерів.
    
Користувач обирає режим через меню в терміналі. Програма демонструє роботу як старих (`setitimer`), так і сучасних (`timer_create`) таймерних механізмів у Unix/FreeBSD.

### Вивід у консоль

```shell
admin@FreeBSD:~/ASPZ/Pr14 % gcc -o task21variant task21variant.c -lpthread -lrt
admin@FreeBSD:~/ASPZ/Pr14 % ./task21variant
Select mode:
1 - CLI clock (setitimer)
2 - POSIX timers in threads
Choice: 1
CLI clock started (setitimer). Press Ctrl+C to stop.
16:36:16^C
admin@FreeBSD:~/ASPZ/Pr14 % ./task21variant
Select mode:
1 - CLI clock (setitimer)
2 - POSIX timers in threads
Choice: 2
POSIX timers started in 2 threads. Press Ctrl+C to stop.
Thread 1: tick
Thread 0: tick
Thread 0: tick
Thread 1: tick
Thread 0: tick
Thread 1: tick
Thread 0: tick
^C
admin@FreeBSD:~/ASPZ/Pr14 %
```

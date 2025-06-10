
# Практична робота №10-11

## Завдання 1

Створити просту оболонку, яка запускає команди користувача.

### Вивід

```shell
admin@FreeBSD:~/ASPZ/Pr10-11 % gcc -Wall task1.c -o task1
admin@FreeBSD:~/ASPZ/Pr10-11 % ./task1
dumbsh> ls
task1           task1.c         task2.c         task21variant.c task3.c
dumbsh> whoami
admin
dumbsh> exit
admin@FreeBSD:~/ASPZ/Pr10-11 %
```

## Завдання 2

API wait — деталі

### Вивід

```shell
admin@FreeBSD:~/ASPZ/Pr10-11 % gcc -Wall task2.c -o task2
admin@FreeBSD:~/ASPZ/Pr10-11 % ./task2
Child: I'm running!
Parent: Child exited with code 42
admin@FreeBSD:~/ASPZ/Pr10-11 %
```

## Завдання 3

Приклад створення кількох дітей:

### Вивід

```shell
admin@FreeBSD:~/ASPZ/Pr10-11 % gcc -Wall task3.c -o task3
admin@FreeBSD:~/ASPZ/Pr10-11 % ./task3
Child 0
Child 1
Child 2
admin@FreeBSD:~/ASPZ/Pr10-11 %
```

## Завдання за варіантом 21

Реалізуйте програму, яка створює два дочірні процеси, кожен з яких виводить своє повідомлення.

### Вивід

```shell
admin@FreeBSD:~/ASPZ/Pr10-11 % gcc -Wall task21variant.c -o task21variant
admin@FreeBSD:~/ASPZ/Pr10-11 % ./task21variant
Child 1: Hello from the first child process!
Child 2: Hello from the second child process!
Parent: Both child processes have finished.
admin@FreeBSD:~/ASPZ/Pr10-11 %
```

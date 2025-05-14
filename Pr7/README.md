
# Практична робота №7

## Завдання 1

Використайте popen(), щоб передати вивід команди rwho (команда UNIX) до more (команда UNIX) у програмі на C.

### Реалізація

Використовується `popen("rwho | more", "r")` для запуску конвеєра команд і зчитування його виводу через програму.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task1.c -o task1
admin@FreeBSD:~/ASPZ/Pr7 % ./task1
admin            ttyv8        Apr 29 17:08 (:0)
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання 2

Напишіть програму мовою C, яка імітує команду ls -l в UNIX — виводить список усіх файлів у поточному каталозі та перелічує права доступу тощо.

### Реалізація

Зчитуються файли через `opendir()/readdir()`, отримуються права доступу через `stat()`, форматуються та виводяться вручну як у `ls -l`.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task2.c -o task2
admin@FreeBSD:~/ASPZ/Pr7 % ./task2
drwxr-xr-x 2 admin admin   512 May 14 23:58 .
drwxr-xr-x 12 admin admin   512 May 14 20:03 ..
-r--r--r-- 1 admin admin   314 May 11 19:39 task1.c
-rwxr-xr-x 1 admin admin  8912 May 14 23:57 task1
-r--r--r-- 1 admin admin  1170 May 11 19:41 task2.c
-rwxr-xr-x 1 admin admin  9808 May 14 23:58 task2
-rw-r--r-- 1 admin admin   426 May 11 19:42 task3.c
-rw-r--r-- 1 admin admin   571 May 11 19:43 task4.c
-r--r--r-- 1 admin admin   763 May 11 19:46 task5.c
-r--r--r-- 1 admin admin   748 May 11 19:51 task6.c
-rw-r--r-- 1 admin admin   701 May 11 19:54 task7.c
-rw-r--r-- 1 admin admin   497 May 11 19:58 task8.c
-rw-r--r-- 1 admin admin   388 May 11 19:59 task9.c
-rw-r--r-- 1 admin admin   611 May 11 20:07 task10.c
-rw-r--r-- 1 admin admin  1901 May 11 20:09 task21variant.c
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання 3

Напишіть програму, яка друкує рядки з файлу, що містять слово, передане як аргумент програми (проста версія утиліти grep в UNIX).

### Реалізація

Зчитується файл рядок за рядком, шукається підрядок через `strstr()`, при збігу — рядок виводиться.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task3.c -o task3
admin@FreeBSD:~/ASPZ/Pr7 % ./task3
Usage: ./task3 <word> <filename>
admin@FreeBSD:~/ASPZ/Pr7 % ./task3 main task2.c
int main() {
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання 4

Напишіть програму, яка виводить список файлів, заданих у вигляді аргументів, з зупинкою кожні 20 рядків, доки не буде натиснута клавіша (спрощена версія утиліти more в UNIX).

### Реалізація

Виводяться аргументні файли посторінково по 20 рядків, зупинка на `getchar()` після кожного блоку.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task4.c -o task4
admin@FreeBSD:~/ASPZ/Pr7 % ./task4 task3.c
#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, argv[1])) {
            printf("%s", line);
        }
    }

--Press Enter to continue--
    fclose(fp);
    return 0;
}
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання 5

Напишіть програму, яка перелічує всі файли в поточному каталозі та всі файли в підкаталогах.

### Реалізація

Використовується рекурсивна функція з `opendir()`/`readdir()`/`stat()` для обходу всіх підкаталогів.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task5.c -o task5
admin@FreeBSD:~/ASPZ/Pr7 % cd ..
admin@FreeBSD:~/ASPZ % ./Pr7/task5
[DIR] ./Pr1
Pr1/task1.c
Pr1/README.md
[DIR] ./.git
.git/description
[DIR] .git/hooks
hooks/applypatch-msg.sample
hooks/commit-msg.sample
hooks/fsmonitor-watchman.sample
hooks/post-update.sample
hooks/pre-applypatch.sample
hooks/pre-commit.sample
hooks/pre-merge-commit.sample
hooks/pre-push.sample
hooks/pre-rebase.sample
hooks/pre-receive.sample
hooks/prepare-commit-msg.sample
hooks/push-to-checkout.sample
hooks/sendemail-validate.sample
hooks/update.sample
[DIR] .git/info
info/exclude
[DIR] .git/refs
[DIR] refs/heads
heads/main
[DIR] refs/tags
[DIR] refs/remotes
[DIR] remotes/origin
origin/main
.git/config
[DIR] .git/objects
[DIR] objects/pack
[DIR] objects/info
[DIR] objects/f1
f1/7096694ab672e5176bb5b3a0d2548b7ae123a9
[DIR] objects/35
35/1367a5f2deb439aea5aa179084281c9a091315
[DIR] objects/98
98/fc46f8d6ae3ea48ed98d9cf6fb61d5c346b73c
98/10d72ba3d3d65bf8903a4165a0597cdaea38d5
[DIR] objects/83
83/782c48aa08847b792ad1638a2b49ca18ce35f8
83/21e25d3174e06bfbcc553517e13c5250e25772
83/5cb19b53dfd025c52e21761d6efd524f4415f2
[DIR] objects/c9
c9/d1b9efbc9b4cdea7b0c51e5f9acb6e7f063b28
[DIR] objects/e8
e8/03d8bac14e37fb6fe8ba7c7df5f6ca412be419
e8/188ad3ee20136d486fe18cdd05c60efa541af0
[DIR] objects/c8
c8/838aacdcef61728699835cea0d89de8fea739f
c8/4ed9ea71d14b55ea014fc76b81550fe7927925
[DIR] objects/ae
ae/82d57b0787c893fc304f5c8c796d41fd3a9d1f
[DIR] objects/56
56/c8d57cbf8aac55a877b6f381c13a1c31558862
[DIR] objects/81
81/ece7d368dc2e003298c0ea2ef45fb781341e24
81/24214132102b5f9223e0efb72b179b05ff59e4
[DIR] objects/b0
b0/3dd24f21a8b075e41eacacd1275612e1cbc408
[DIR] objects/1d
1d/37c6849b31fb0d2def907fbc11fbbd70e50ac8
[DIR] objects/03
03/1ceb2cfd6684740444f17cf492920c32a3f1f8
[DIR] objects/bc
bc/7fcc972e2c872ecc4387155afa3cec5c228213
[DIR] objects/8b
8b/6720178005432f09f9d010d9f53f2a79b7125d
[DIR] objects/7c
7c/e913295835c403d6d0550b84d8f143dd7f2ee1
7c/71a3760940e8b9e2fe74b6a4bf468e84e53887
[DIR] objects/27
27/677c555302ce51866e5eb3e5e75bd2194608a2
[DIR] objects/02
02/f6e446e9119485dbf66d386835f2d2a6f9a5d3
02/a94625871589490c7a198c954fe0ee1534981b
[DIR] objects/93
93/a9ac54bc2f0c9b177cb95f45f0edb9a2aaebf1
[DIR] objects/11
11/e31f9b93e0e7c7404985ff30d82e13e86aeb39
[DIR] objects/d3
d3/c7e781c8db39725676a03accfcb852aa9e1423
[DIR] objects/2b
2b/555e4f41a5ed614f020c29882d94767f9c5d10
[DIR] objects/4a
4a/31da512999aa14253ddac474dc9c685ae5c2c0
[DIR] objects/78
78/14fd95ac2574e92b8839afa2163c383c08428a
[DIR] objects/7f
7f/05ad86c1fa812e9b74db9c220a4cb1560f28bd
[DIR] objects/db
db/5dd7a42d1c06cf4bb8bc8aaa619f0440bb5f56
[DIR] objects/ea
ea/f03b7cad41f3143709eaaf05b09b45e74f5a7e
[DIR] objects/bf
bf/4df780731833071edd734d1c8847928bd076b7
[DIR] objects/5c
5c/88fdb4a3cc14117397bda39dd080558ee1ec87
5c/4c686d1a97bb709e4d20e7f11dd36bd8ab69a6
[DIR] objects/0a
0a/c95533b002396a49a7b6e59b256a40191dddca
[DIR] objects/24
24/8463304c20e1e400166d29f0bf871eaf678a11
[DIR] objects/1e
1e/81d629603d27a49c604cf3c876a57069535686
[DIR] objects/36
36/b2fc92314e871b906750749cc0a93529d775f2
[DIR] objects/c1
c1/25d861fc8d33a885ef98c2dd2b469fbe350cd3
c1/72b5e3ab8f7cb91d881fefd472ed3cea75a316
[DIR] objects/0f
0f/096cefd8a55817065361481a1bdeb201af474c
[DIR] objects/73
73/9dce5ed0fc8910fe72a261de34f9abdd98afe7
[DIR] objects/64
64/cac849af69218da206d3d2acd70b0e918bf4e3
[DIR] objects/de
de/1ffa29b04576e0432356f687b51451f7d0a27e
[DIR] objects/b4
b4/ec5d5284c13581a721bd20ca023ea28c03c9fb
b4/7fc04f0e1d3d9b283200e102a5a782be04118a
[DIR] objects/80
80/e5894040f1828e4b400fc8b8d9a5901833dacf
80/d622555bd114833fecc2bb21bc61abbac81412
[DIR] objects/3c
3c/ee4cad080360c8b6deda4ad7c6df4bcb59c4e9
[DIR] objects/9f
9f/d7b23af5a62129b5c516043f0d97536b437200
[DIR] objects/5f
5f/cd23bccc4134e6ffb533f24358f72715af7c8c
[DIR] objects/14
14/a1fcd2b95d438f0725da3480ef0d354c3f8d03
[DIR] objects/94
94/54c403dbc3660227879cfa781fdff2f6225f2d
[DIR] objects/9a
9a/9d5f594f6992181f7eee473ccbfe456551f8fe
9a/51278e21333a5f2ed72098c5403006ef9a2ec8
[DIR] objects/b1
b1/3eaad7a9d30a66c3a06b0e9959b6068722434d
[DIR] objects/00
00/8be9eec46af61f2b85ca6d8630404fbfadd63d
[DIR] objects/9e
9e/9527ccbb865cfefdba0933b23ab637c0ace1aa
9e/943566f0d190e637b016b88659fa20d87e28d3
[DIR] objects/d9
d9/db41a58cfcd6b6b56f2c0bc5b8f3d5e1eb5a0e
[DIR] objects/2a
2a/3db94110ac384d7756e106949e2efd3731beb2
2a/97b1f724e7ee3aa949ee06af4ba24756a0b7fc
[DIR] objects/f5
f5/cec42b49e7b913cf49f65700f554d861cf82ca
f5/ff31187d9fe402a1b0d69fc2fb393e8817794d
[DIR] objects/8a
8a/b5b51abf98739d64ac8b217a619269eda56d75
[DIR] objects/da
da/cc21d59b7bc87ffc8478736e9384ed216808a2
[DIR] objects/a1
a1/9632aa25b705560034d674255910dfba814102
[DIR] objects/7d
7d/f343393c7de12bdf0aad0dc716228f930840ac
[DIR] objects/d4
d4/82c751095a8169d6d88ad919f4dfc777ddf1f6
[DIR] objects/a5
a5/a9c61f35ea1bed288a3941f641db03f5d877c0
[DIR] objects/f2
f2/64168a4cdcb9e3b06184617ae48d114ac7a2cc
f2/daa515dcc72006b945614693b9c90afdc614f3
[DIR] objects/59
59/157199d44e296cdcba47522ccc2f1534302cec
59/8eb1c4d0749089cbe0566d48b7f4157f829700
[DIR] objects/fb
fb/5d39a63b5bd3aa6591aab86aa6500a9a8613eb
[DIR] objects/e9
e9/4cae3242cbe56ac229b81822d3280a5d4c803a
[DIR] objects/ce
ce/32eb32604388afabe4ce0adf3c066f67764c8c
[DIR] objects/c3
c3/e68ae3e057b1205cd7660ea11d89a2b7d277e1
[DIR] objects/e1
e1/b0e09e7ef11672320b6dfa0e26798f6d0a742d
[DIR] objects/e6
e6/1d4b80c2536a21d67375c670b719c1911811a3
[DIR] objects/fe
fe/306c9f392d51d27f22e3fe2421e3b5b64e9458
[DIR] objects/20
20/bf1813cd536d887ca2de94919e08f9ce4522af
[DIR] objects/90
90/4324aab3df4493702e4c7e42190d80e2649a4b
[DIR] objects/e2
e2/aae0c9eeffae75a291a88a380b91871290fc0f
[DIR] objects/e7
e7/3829d9081a682752277f2302d87b0e9ef0b7df
[DIR] objects/b3
b3/bd037dda6b971ba47d42012a48bc8c388520a1
[DIR] objects/71
71/857033d112bed0bd89f70aa3fb06d7ec42eea0
71/1362d0799237beb715bd7099b82584e0f4dfa1
[DIR] objects/6e
6e/99d211d9445f52d06db94bcd1dce44571a7b2f
[DIR] objects/96
96/6b561757ecf6cc1ee1be1a5ee7b54dd281c89c
[DIR] objects/26
26/3b8021f6946f77fb75e1191f91285f91e58b76
[DIR] objects/86
86/63850c672eade1743a6b276a596be14a96b16b
86/22fc71195c29462a16a3b8a20134f8ead8eeb8
[DIR] objects/97
97/24c0499f563728ff22a94f293d71ef01b02a2a
97/38d23b51fd0847baeecd1df315af007a5079c5
[DIR] objects/69
69/6449d83c85a11c954ba2b69753f631d3d6aa90
[DIR] objects/ab
ab/e907ae666215fb84700cd54e80239eb96b24db
[DIR] objects/70
70/dbdd2b34f0ac24f0db156a752df5286ff4d2c7
[DIR] objects/4d
4d/2cd40c67c097d27c774f10f74d6cd048c927b0
[DIR] objects/30
30/876aa5944233b6172a4a3e31f33cafd82d6be3
[DIR] objects/29
29/87cd814fabda86c6e23a7a83448d457fb34a48
29/066254fdbbb2ba1f8f6e5a9741904141acec45
[DIR] objects/ac
ac/ba1a55642dae250617888dbcb9418310d1e82f
[DIR] objects/ed
ed/58b83ce0f63b12f7f74758cc1d48f02c0f8c6e
[DIR] objects/18
18/4be5d6d688e5005d5355d3bbcaf9cd3c59e4a9
[DIR] objects/25
25/792f70ee99c8954f5a83f5eed245a4f562ae59
[DIR] objects/10
10/1e1a1b28905a03d8f4996e7b6b60f44ac30545
[DIR] objects/34
34/00ae98091529131e4a63ee838a981fe22c3e0a
[DIR] objects/46
46/7d246a37f0f4668679fc2b580a01c68f2f2894
46/4f1208ebe3cfc9f83a742b2a2e12265cd66e2c
[DIR] objects/79
79/979687df00ec5651d4efdba162fe94956ada5a
[DIR] objects/42
42/7385c512d373d50bf1bc63e31b8fe593e31844
[DIR] objects/fc
fc/d27bb93f7be452519dace9929116b0fd2c7646
.git/HEAD
.git/FETCH_HEAD
.git/index
.git/COMMIT_EDITMSG
[DIR] .git/logs
logs/HEAD
[DIR] logs/refs
[DIR] refs/heads
heads/main
[DIR] refs/remotes
[DIR] remotes/origin
origin/main
.git/ORIG_HEAD
[DIR] ./Pr2
Pr2/task2_1.c
Pr2/task1.c
Pr2/README.md
Pr2/task2_2.c
Pr2/task2_3.c
Pr2/task2_4.c
Pr2/task3_1.c
Pr2/task3_2.c
Pr2/task4.c
Pr2/task21.c
[DIR] ./Pr3
[DIR] Pr3/task1
task1/Dockerfile
[DIR] Pr3/task2
task2/Dockerfile
[DIR] Pr3/task21variant
task21variant/Dockerfile
task21variant/test_limits.sh
[DIR] Pr3/task3
task3/Dockerfile
task3/dice_roll.c
[DIR] Pr3/task4
task4/Dockerfile
task4/lottery.c
[DIR] Pr3/task5
task5/Dockerfile
task5/file_copy.c
task5/input.txt
[DIR] Pr3/task6
task6/Dockerfile
task6/stack_limit.c
Pr3/README.md
[DIR] ./Pr5
Pr5/task21variant.c
Pr5/task21variant
[DIR] ./Pr4
Pr4/task1.c
Pr4/task1
Pr4/task2.c
Pr4/task2
Pr4/task3.c
Pr4/task3
Pr4/task4_2
Pr4/task4_1.c
Pr4/task4_2.c
Pr4/task5
Pr4/task5.c
Pr4/task6
Pr4/task6.c
Pr4/task7_1
Pr4/task7_1.c
Pr4/task7_2.c
Pr4/task7_2
Pr4/task21variant.c
Pr4/task21variant
[DIR] ./Pr6
[DIR] ./Pr7
Pr7/task1.c
Pr7/task1
Pr7/task2.c
Pr7/task2
Pr7/task3.c
Pr7/task3
Pr7/task4.c
Pr7/task4
Pr7/task5.c
Pr7/task5
Pr7/task6.c
Pr7/task7.c
Pr7/task8.c
Pr7/task9.c
Pr7/task10.c
Pr7/task21variant.c
[DIR] ./Pr8
Pr8/task1.c
Pr8/task2.c
Pr8/task3.c
Pr8/task4.c
Pr8/task21variant.c
[DIR] ./Pr9
Pr9/task1.c
Pr9/task2.c
Pr9/task3.c
Pr9/task4.c
Pr9/task5.c
Pr9/task6.c
Pr9/task21variant.c
admin@FreeBSD:~/ASPZ %
```

## Завдання 6

Напишіть програму, яка перелічує лише підкаталоги у алфавітному порядку.

### Реалізація

Збираються лише директорії з `stat()`, сортуються алфавітно за `qsort()` і виводяться.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task6.c -o task6
admin@FreeBSD:~/ASPZ/Pr7 % cd ..
admin@FreeBSD:~/ASPZ % ./Pr7/task6
Pr1
.git
Pr2
Pr3
Pr5
Pr4
Pr6
Pr7
Pr8
Pr9
admin@FreeBSD:~/ASPZ %
```

## Завдання 7

Напишіть програму, яка показує користувачу всі його/її вихідні програми на C, а потім в інтерактивному режимі запитує, чи потрібно надати іншим дозвіл на читання (read permission); у разі ствердної відповіді — такий дозвіл повинен бути наданий.

### Реалізація

Знаходяться всі файли з розширенням `.c`, перевіряються `stat()`, після підтвердження від користувача застосовується `chmod()`.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task7.c -o task7.out
admin@FreeBSD:~/ASPZ/Pr7 % ./task7.out
Allow read permission for others on task7.out? (y/n): y
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання 8

Напишіть програму, яка надає користувачу можливість видалити будь-який або всі файли у поточному робочому каталозі. Має з’являтися ім’я файлу з запитом, чи слід його видалити.

### Реалізація

Виводиться список файлів, на кожен — запит на видалення. Видалення — через `remove()`.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task8.c -o task8
admin@FreeBSD:~/ASPZ/Pr7 % ./task8
Delete file task1.c? (y/n): n
Delete file task1? (y/n): n
Delete file task2.c? (y/n): n
Delete file task2? (y/n): n
Delete file task3.c? (y/n): n
Delete file task3? (y/n): n
Delete file task4.c? (y/n): n
Delete file task4? (y/n): n
Delete file task5.c? (y/n): n
Delete file task5? (y/n): n
Delete file task6.c? (y/n): n
Delete file task6? (y/n): n
Delete file task7.c? (y/n): n
Delete file task7? (y/n): n
Delete file task7.out? (y/n): n
Delete file task8? (y/n): n
Delete file task8.c? (y/n): n
Delete file task9.c? (y/n): n
Delete file task10.c? (y/n): n
Delete file task21variant.c? (y/n): n
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання 9

Напишіть програму на C, яка вимірює час виконання фрагмента коду в мілісекундах.

### Реалізація

Використовується `clock_gettime()` до і після блоку коду. Обчислюється різниця в мілісекундах.

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task9.c -o task9
admin@FreeBSD:~/ASPZ/Pr7 % ./task9
Execution time: 3 ms
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання 10
Напишіть програму мовою C для створення послідовності випадкових чисел з плаваючою комою у діапазонах:

 (a) від 0.0 до 1.0
 
 (b) від 0.0 до n, де n — будь-яке 
 дійсне число з плаваючою точкою.
 Початкове значення генератора випадкових чисел має бути встановлене так, щоб гарантувати унікальну послідовність.

### Реалізація

Використовується `srand(time(NULL))` та `rand()`/`RAND_MAX`, далі масштабування до потрібного діапазону:
-   `rand() / (float)RAND_MAX` — для [0.0, 1.0]
-   `(rand() / (float)RAND_MAX) * n` — для [0.0, n]

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task10.c -o task10
admin@FreeBSD:~/ASPZ/Pr7 % ./task10
From 0.0 to 1.0:
0.346375
0.724834
0.265214
0.228171
0.259299

Enter value n for numbers generaation in [0.0; n]: 6
From 0.0 to 6.000000:
0.781816
4.655622
3.100272
0.264592
5.164845
admin@FreeBSD:~/ASPZ/Pr7 %
```

## Завдання по варіанту 21

Напишіть утиліту, яка аналізує "заплутаність" структури директорій за спеціальним критерієм вашого вибору.

### Опис рішення


Програма рекурсивно обходить каталог, рахуючи:

-   глибину вкладеності (`max_depth`),
-   кількість символічних посилань (`symlink_count`),
-   переповнені директорії (>100 файлів),
-   підозрілі символічні посилання на `..` (як ознака циклів).

Для обходу використовується `opendir()` / `readdir()`, для перевірки типів файлів — `lstat()`.  
В кінці виводиться зведена оцінка заплутаності структури.

### Запуск програми

```shell
admin@FreeBSD:~/ASPZ/Pr7 % gcc -Wall task21variant.c -o task21variant
admin@FreeBSD:~/ASPZ/Pr7 % ./task21variant /
=== Directory Complexity Analysis ===
Analyzed path: /
Max depth: 15
Number of symbolic links: 18329
Cluttered directories (> 100 files): 480
Suspected cycles (symbolic '..'): 0
Complexity score: 100 / 100
admin@FreeBSD:~/ASPZ/Pr7 %
```

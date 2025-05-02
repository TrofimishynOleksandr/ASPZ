# Практична робота №3
## Завдання 1

Використання --privileged ulimit

Запуск без --privileged

```shell
$ ulimit -n
1048576
$ ulimit -aS | grep "open files"
open files                          (-n) 1048576
$ ulimit -aH | grep "open files"
open files                          (-n) 1048576
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
open files                          (-n) 3000
$ ulimit -aH | grep "open files"
open files                          (-n) 3000
$ ulimit -n 3001
/bin/bash: line 1: ulimit: open files: cannot modify limit: Operation not permitted
$ ulimit -n 2000
$ ulimit -n
2000
$ ulimit -aS | grep "open files"
open files                          (-n) 2000
$ ulimit -aH | grep "open files"
open files                          (-n) 2000
$ ulimit -n 3000
/bin/bash: line 1: ulimit: open files: cannot modify limit: Operation not permitted
```

Запуск з --privileged

```shell
$ ulimit -n
1048576
$ ulimit -aS | grep "open files"
open files                          (-n) 1048576
$ ulimit -aH | grep "open files"
open files                          (-n) 1048576
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
open files                          (-n) 3000
$ ulimit -aH | grep "open files"
open files                          (-n) 3000
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
2000
$ ulimit -aS | grep "open files"
open files                          (-n) 2000
$ ulimit -aH | grep "open files"
open files                          (-n) 2000
$ ulimit -n 3000
```

## Завдання 2

Поекспериментовано з досягненням процесом встановленого ліміту з використанням утиліти perf

```shell
$ perf --version
perf version 6.1.135
$ perf stat echo Hello World
Hello World!

 Performance counter stats for 'echo Hello World!':
   
              0.48 msec task-clock:u                     #    0.113 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
                57      page-faults:u                    #  119.048 K/sec
            352507      cycles:u                         #    0.736 GHz
            115176      instructions:u                   #    0.33  insn per cycle
             24289      branches:u                       #   50.729 M/sec
              2412      branch-misses:u                  #    9.93% of all branches
           1762535      slots:u                          #    3.681 G/sec
            152061      topdown-retiring:u               #      8.6% Retiring
            228092      topdown-bad-spec:u               #     12.9% Bad Speculation
            857075      topdown-fe-bound:u               #     48.6% Frontend Bound
            525304      topdown-be-bound:u               #     29.8% Backend Bound

       0.004231068 seconds time elapsed

       0.002543000 seconds user
       0.000000000 seconds sys
```

# Завдання 3

Написано програму, що імітує кидання шестигранного кубика

Результати записуються у файл, для якого попередньо встановлено обмеження на його максимальний розмір за допомогою prlimit --fsize=16:16 ./dice_roll

Оброблено коректно ситуацію перевищення ліміту

```shell
$ prlimit --fsize=16:16 ./dice_roll
File size limit reached. Program terminated.
Contents of dice_rolls.txt:
6
5
3
5  
5
1
1
2
```

# Завдання 4

Написано програму що імітує лотерею, вибираючи 7 різних цілих чисел у діапазоні від 1 до 49 і ще 6 з 36.

Встановлено ліміт та оброблено ситуації перевищення

```shell
$ prlimit --cpu=1:2 ./lottery
7 of 49: 9 44 31 40 13 10 1
6 of 36: 11 5 16 18 21 19
```

Додамо навантаження у вигляді бескінечного циклу перед printf("6 of 36: ")

Відпрацює обробка помилки

```shell
$ prlimit --cpu=1:2 ./lottery
7 of 49: 12 18 44 49 10 30 4
CPU time limit exceeded. Program terminated.
```

# Завдання 5

Написано програму для копіювання одного іменованого файлу в інший

Встановлено ліміт програмно (setrlimit) та обробленно ситуації перевищення ліміту

```shell
$ ./file_copy input.txt outpux.txt
Reached file size limit.
Contents of outpux.txt:
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor.
Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi.
Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat.
Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue.
Ut in risus volutpat libero pharetra tempor. Cras vestibulum bibendum augue. Praesent egestas leo in pede.
Praesent blandit odio eu enim. Pellentesque sed dui ut augue blandit sodales. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae;
Aliquam nibh. Mauris ac mauris sed pede pellentesque fermentum. Maecenas adipiscing ante non diam sodales hendrerit.
Ut velit mauris, egestas sed, gravida nec, ornare ut, mi. Aenean ut orci vel massa suscipit pulvinar.
Nulla sollicitudin. Fusce varius, ligula non tempus aliquam, nunc
```

# Завдання 6

Написано програму, що демонструє використання обмеження (max stack segment size)

```shell
$ prlimit --stack=100000:100000 ./stack_limit
Stack size limit: 100000 bytes
Recursion depth: 1
Recursion depth: 2
Recursion depth: 3
Recursion depth: 4
Recursion depth: 5
Recursion depth: 6
Recursion depth: 7
Recursion depth: 8
Recursion depth: 9
```

# Завдання по варіанту 21

Досліджено взаємодію ulimit та cgroups у Docker.

Команда для запуску з лімітами:
```shell
docker run --rm --ulimit nofile=1024:1024 --ulimit nproc=256:256 --memory=100m --cpus="0.5" --pids-limit=128 ulimit-cgroups-test
```

Результати
```shell
===== ulimit (user limits) =====
ulimit -n (open files): 1024
ulimit -u (max user processes): 256
ulimit -v (virtual memory): unlimited
ulimit -f (file size): unlimited
ulimit -t (CPU time): unlimited

===== cgroup limits =====
CPU max (cgroup): 0.50 CPUs
Memory max (cgroup): 104857600 bytes (100 MB)
PIDs max (cgroup): 128
```

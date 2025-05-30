
# Практична робота №6

## Завдання по варіанту 21

Напишіть короткий звіт (до 1 сторінки): “Valgrind vs ASan — що краще для великих програм? Для CI/CD? Для роботи з Docker?”

Valgrind та AddressSanitizer (ASan) — популярні інструменти для виявлення помилок пам’яті, однак вони мають різні сильні сторони.


1.	Якість виявлення
- Valgrind працює без модифікації бінарного коду — емулює виконання, що дозволяє йому точно виявляти витоки пам’яті, use-after-free, double free, переповнення тощо.
- ASan вбудовується на рівні компіляції й перевіряє доступи до пам’яті під час виконання, часто швидше, але менш точний у складних багатопотокових ситуаціях.

2. Швидкість виконання
- Valgrind приблизно у 20–50 разів повільніший за реальний запуск (через емулювання CPU).
- ASan приблизно у 2–5 разів повільніший, значно швидший для великих програм або інтеграції в CI.

3. Зручність для великих програм
- Valgrind не потребує перекомпіляції, але погано працює з великими програмами через повільність.
- ASan потребує перекомпіляції з -fsanitize=address, але масштабується краще.

4. У CI/CD
- ASan — кращий вибір: швидкий, інтегрується з CMake/Makefile, дозволяє запуск тестів автоматично після кожного коміту.
- Valgrind повільний, але корисний для фінальної перевірки або специфічного тестування.

5. У Docker
- ASan краще працює у Docker: потребує лише компілятора, не потребує емуляції.
- Valgrind у Docker можливий, але важче налаштувати й дуже ресурсозатратний.


| Сценарій                     | Краще використовувати |
|-----------------------------|-----------------------|
| Розробка великих проектів   | ASan                  |
| CI/CD перевірки             | ASan                  |
| Пошук точного memory leak   | Valgrind              |
| Робота в Docker-контейнері  | ASan                  |

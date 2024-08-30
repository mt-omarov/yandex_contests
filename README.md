# Решения задач Яндекс контестов

## [Тренировки 1.0](https://yandex.ru/yaintern/algorithm-training_2021)
|№ ДЗ| Ссылки | A | B | C | D | E | F | G | H | I | J |
|:-----------------------:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|3. Множества							|[Задачи](https://contest.yandex.ru/contest/27663/problems/), [Решения](./1_training/3_hw.cpp)|+|+|+|+|+|+|+|+|+|+|
|4. Словари и сортировка подсчетом 	|[Задачи](https://contest.yandex.ru/contest/27663/problems/), [Решения](./1_training/4_hw.cpp)|+|+|+|+|+|+|+|+|+|+|
|5. Префиксные суммы и два указателя	|[Задачи](https://contest.yandex.ru/contest/27794/problems/), [Решения](./1_training/5_hw.cpp)|+|+|+|+|+|+|–|+|+|–|
|6. Бинарный поиск						|[Задачи](https://contest.yandex.ru/contest/27844/problems/), [Решения](./1_training/6_hw.cpp)|+|+|+|+|+|+|+|+|–|–|
|7. Сортировка событий					|[Задачи](https://contest.yandex.ru/contest/27883/problems/), [Решения](./1_training/7_hw.cpp)|+|+|–|–|+|–|–|–|–|–|
|8. Деревья							|[Задачи](https://contest.yandex.ru/contest/28069/problems/), [Решения](./1_training/8_hw.cpp)|+|+|+|+|+|+|+|+|+|+|

## [Тренировки 2.0](https://yandex.ru/yaintern/algorithm-training_june_2021?from=contest_new)
### Дивизион B
|№ ДЗ| Ссылки | A | B | C | D | E |
|:-------:|:------:|:-:|:-:|:-:|:-:|:-:|
|1|[Задачи](https://contest.yandex.ru/contest/28730/problems/), [Решения](./2_B_training/1_hw.cpp)|+|+|+|+|+|
|2|[Задачи](https://contest.yandex.ru/contest/28738/problems/), [Решения](./2_B_training/2_hw.cpp)|+|+|+|+|+|
|3|[Задачи](https://contest.yandex.ru/contest/28964/problems/), [Решения](./2_B_training/3_hw.cpp)|+|+|+|+|+|
|4|[Задачи](https://contest.yandex.ru/contest/28970/problems/), [Решения](./2_B_training/4_hw.cpp)|+|+|+|–|+|
|5|[Задачи](https://contest.yandex.ru/contest/29075/problems/), [Решения](./2_B_training/5_hw.cpp)|+|+|+|+|+|
|6|[Задачи](https://contest.yandex.ru/contest/29188/problems/), [Решения](./2_B_training/6_hw.cpp)|+|+|+|+|+|
|7|[Задачи](https://contest.yandex.ru/contest/29396/problems/), [Решения](./2_B_training/7_hw.cpp)|+|+|+|+|–|
|8|[Задачи](https://contest.yandex.ru/contest/29403/problems/), [Решения](./2_B_training/8_hw.cpp)|+|+|+|+|–|

### Дивизион A
|№ ДЗ| Ссылки | A | B | C | D | E |
|:-------:|:------:|:-:|:-:|:-:|:-:|:-:|
|1|[Задачи](https://contest.yandex.ru/contest/28724/problems/), [Решения](./2_A_training/1_hw.cpp)|+|+|+|+|+|
|2|[Задачи](https://contest.yandex.ru/contest/28736/problems/), [Решения](./2_A_training/2_hw.cpp)|+|+|+|+|–|
|3|[Задачи](https://contest.yandex.ru/contest/28963/problems/), [Решения](./2_A_training/3_hw.cpp)|+|–|+|+|+|
|4|[Задачи](https://contest.yandex.ru/contest/28969/problems/), [Решения](./2_A_training/4_hw.cpp)|+|+|–|+|+|
|5|[Задачи](https://contest.yandex.ru/contest/29072/problems/), [Решения](./2_A_training/5_hw.cpp)|+|+|–|–|–|
|6|[Задачи](https://contest.yandex.ru/contest/29189/problems/), [Решения](./2_A_training/6_hw.cpp)|+|+|–|–|–|

## [Тренировки 3.0](https://yandex.ru/yaintern/training/algorithm-training_feb_2023)

## [Тренировочный контест](https://contest.yandex.ru/contest/50668/)
|Задание| Ссылки | Статус |
|:-----:|:-------:|:------:|
|A. Хитрый шифр| [Решение](./test/A.cpp) | + |
|B. Через тернии к клиенту| [Решение](./test/B.cpp) | + |
|C. Приснится же такое...| [Решение](./test/C.cpp) | + |
|D. Лей, лей, не жалей| [Решение](./test/D.cpp) | + |
|E. Занимательная алхимия| [Решение](./test/E.cpp) | – (WA на 38 тесте) |

## [Хендбук "Основы алгоритмов"](https://education.yandex.ru/handbook/algorithms)

## Компиляция программ
bash-скрипт [`compile`](./compile):
```bash
clang++ -std=c++20 -fsanitize=address,undefined -Wall -Wextra -Werror $1 -o hw || exit
```
пример использования: `$ ../compile your_hw.cpp`
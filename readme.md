﻿== Возможности копмилятора

1. Локальные переменные
	- объявление только внутри функций
	- переменные в global scope запрещены

	Объявление переменных без базового значения запрещены:
	Другими словами, доступно объявление сразу же с определением.

		int a;      //compile error
		int b = 0;

2. Статическая типизация переменных
	- любое неявное преобразование типов запрещено

		int a;
		bool b = a; //compiler error

	Допустимые типы данных:

	void, int  /////, bool

	2.1 void

		используется только для указания что функция ничего не возвращает

	2.2 int

		целое 16-битное знаковое число, в диапазоне [-(2^16), (2^16)-1]
		т.е. [-32'768, 32'767]

		допустимо умножение, сложение, деление и вычитание
		если итоговое выражение не влезает в допустимый диапазон

	///////2.3 bool
	///////
	///////	Возможные значения:
	///////	bool: 'true', 'false'
	///////	или вывод из выражения-условия
	///////
	///////	преобразование к 0 или 1 запрещено
	///////	преобразование выражения int к bool запрещено:
	///////
	///////	int a = 3;
	///////	bool b = a; //compile error

3.  Поддержка выражений (expressions)

	Выражение - запись вида x ob y, где x и y -
	переменные или выражения

	А 'ob' - бинарный оператор

	ИЛИ запись вида ou x,
	где x - операнд, а 'ou' - унарный оператор

	Допустимы подвыражения
	Каждое выражение заканчивается на ';'

	Выражения, которые не записывают результат никуда, нужно запрещать,
	например:

		int i = 123 * 100 * -30 / 300 * 100; //to delete
		int a = 0;

	return a;

4. Операторы

	3.1 Операторы присвоения, деления, умножения, сложения, вычитания:
		'=', '+', '-', '*', '/'
		Пример:
			'a = x'

		Где 'x' переменная типа 'a' или допустимое значение типа 'a'

		У каждого оператора есть свой приоритет, который
		определяет последовательность выполнения оператора

		Похожие операторы:

		- (унарный минус)
		- (бинарный минус)
		+ (бинарный плюс)
		* (знак умножения)
		/ (знак деления)

	3.2 Оператор return
		Обязателен в функциях, которые возвращают значения

		Запись вида 'return x', где 'x' - выражение

5. Функции

	Синтаксис:
		<return-type> <name> ( [<argument-typeN> <argument-nameN>, ...] ) { [expressions] [return [expression]] }

	Поддерживается произвольное количество аргументов функций

	Возвращаемые значения доступны все из доступных типов данных

	Вложенные функции запрещены



6. Комментарии

	Поддерживаются только однострочные комментарии,
	начинающиеся на '//'





Исходя из вышесказанного, у нас есть ключевые слова:

int, return, void


Дополнительная общая информация и ограничения:

	Вызывающий код не видит функции и переменные, объявленные ниже текущего выражения

	Единицей трансляции считается один единственный файл, переданный компилятору

	Препроцессор не поддерживается

	Модификаторы const, static, inline не поддерживаются
	Доступна только стековая модель памяти, статическая модель памяти не поддерживается

	Арифметика указателей и массивы не поддерживаются

	В выражениях допускается любая скобочная вложенность
	Задача раскрытия скобок ложится на компилятор


Что планируется:
	todo: if, elseif, bool, for, while, do, conditions, #include, #pragma once

				- LexicalAnalyser должен возвращать ошибки
				- Придумать формат ошибок с кодом ошибки, строкой, символом
				  и указанием на оригинальную строку полностью

				  Например:

				  "
					bool b = false;
					int a = 000000000001;
				  "

				  Хочется чтоб примерно такая ошибка:

				  ==========================================================================
				  Lexical error (L100) in file.cpp:20 at
				  'int a = 0000000000001;'
						   ^
				  '000000000001' is not an number. Did you expect '1'?
				  ==========================================================================

				  Какой была бы структура такого сообщения об ошибке?







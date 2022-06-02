#include "info.h"

void free_memory(Rgb** arr, int height){
	for(int i = 0; i < height; i++)
		free(arr[i]);
	free(arr);

}

void printHelp(){
	puts("Программа по обработке bmp-изображений, реализованная с помощью CLI.");
	puts("Общие сведения:");
	puts("\tИзображение должно соответствовать формату BMP 3 версии;");
	puts("\t24 бита на цвет;");
	puts("\tБез сжатия;");
	puts("\tИспользуются цвета из определенной палитры;");
	
	puts("Палитра:");
	puts("\t* red");
	puts("\t* green");
	puts("\t* blue");
	puts("\t* black");
	puts("\t* white");
	puts("\t* yellow");
	puts("\t* orange");
	puts("\t* brown");
	puts("\t* grey");
	puts("\t* pink");
	puts("\t* olive");

	puts("Первым аргументом введите название файла (путь), который нужно обработать.");
	puts("Далее введите ключь.");
	puts("Последним аргументом введите название файла (путь), в который нужно записать результат работы программы.\n");

	puts("Ключи для вызова доступных функций:\n");
	puts("-h/--help: Меню.\n");
	puts("-c/--collage: Создание коллажа размера N*M.");
	puts("\t-x/--count_x <value>: Количество изображений по 'оси' X;"); 
	puts("\t-y/--count_y <value>: Количество изображений по 'оси' У;\n");
	puts("-r/--reflection: Отражение заданной области.");
	puts("\t-a/--axis <x/y>: Ось, относительно которой отражать('x' - горизонтальная, 'y' - вертикальная);");
	puts("\t-l/--left_up_corner <value> <value>: Координаты левого верхнего угла;");
	puts("\t-r/--right_down_corner <value> <value>: Координаты нижнего правого угла;\n");
	puts("-d/--demon: Рисование пентаграммы в круге.");
	puts("\tОкружность задается:");
	puts("\t-c/--center <value> <value>: Координаты центра окружности;");
	puts("\t-r/--radius <value>: Радиус окружности;");
	puts("\t-l/--line <value>: Толщина линии окружности и звезды;");
	puts("\t-C/--color <value>: Цвет окружности и звезды;");
	puts("\t или");
	puts("\t-u/--left_up_corner <value> <value>: Координаты левого верхнего угла;");
	puts("\t-d/--right_down_corner <value> <value>: Координаты нижнего правого угла;");
	puts("\t-l/--line <value>: Толщина линии окружности и звезды;");
	puts("\t-C/--color <value>: Цвет окружности и звезды;\n");
	puts("-R/--rectangle: Рисование прямоугольника.");
	puts("\t-l/--left_up_corner <value> <value>: Координаты левого верхнего угла;");
	puts("\t-r/--right_down_corner <value> <value>: Координаты правого нижнего угла;");
	puts("\t-t/--line_thickness <value>: Толщина линии;");
	puts("\t-c/--line_color <value>: Цвет линии;");
	puts("\t-f/--fill <y/n>: Прямоугольник может быть залит или нет;");
	puts("\t-C/--color <value>: Цвет, которым залит прямоугольник;\n");
	
}


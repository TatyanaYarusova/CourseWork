#include "info.h"

void check_color(char* color){
	if((strcmp(color, "black") != 0)&&(strcmp(color, "red") != 0)&&(strcmp(color, "green") != 0)&&(strcmp(color, "blue") != 0)&&
	(strcmp(color, "white") != 0)&&(strcmp(color, "yellow") != 0)&&(strcmp(color, "orange") != 0)&&(strcmp(color, "pink") != 0)&&
	(strcmp(color, "brown") != 0)&&(strcmp(color, "grey") != 0)&&(strcmp(color, "olive") != 0)){
		printf("К сожалению, цвета <<""%s"">> нет в предложенной палитре, на данный момент был установлен цвет по умолчанию - <<black>>\n", color);
		puts("Палитра:");
		puts("* red");
		puts("* green");
		puts("* blue");
		puts("* black");
		puts("* white");
		puts("* yellow");
		puts("* orange");
		puts("* brown");
		puts("* grey");
		puts("* pink");
		puts("* olive");
		strcpy(color, "black");
	}

}

void color(Rgb* elem, char* c){

	if(strcmp(c, "black") == 0){
		elem->b = 0;
		elem->g = 0;
		elem->r = 0;
	}
	if(strcmp(c, "white") == 0){
		elem->b = 255;
		elem->g = 255;
		elem->r = 255;
	}
	if(strcmp(c, "red") == 0){
		elem->b = 0;
		elem->g = 0;
		elem->r = 255;
	}
	if(strcmp(c, "green") == 0){
		elem->b = 0;
		elem->g = 255;
		elem->r = 0;
	}
	if(strcmp(c, "blue")== 0){
		elem->b = 255;
		elem->g = 0;
		elem->r = 0;
	}
	if(strcmp(c, "pink")== 0){
		elem->b = 203;
		elem->g = 192;
		elem->r = 255;
	}
	if(strcmp(c, "yellow")== 0){
		elem->b = 0;
		elem->g = 255;
		elem->r = 255;
	}
	if(strcmp(c, "orange")== 0){
		elem->b = 0;
		elem->g = 165;
		elem->r = 255;
	}
	if(strcmp(c, "grey")== 0){
		elem->b = 190;
		elem->g = 190;
		elem->r = 190;
	}
	if(strcmp(c, "brown")== 0){
		elem->b = 0;
		elem->g = 51;
		elem->r = 153;
	}
	if(strcmp(c, "olive")== 0){
		elem->b = 0;
		elem->g = 128;
		elem->r = 128;
	}

}

void recBmp(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, Point left_corner, Point right_corner, int line, char* color_line, char* fill, char* color_rec, char* file_out){
	FILE* f_out = fopen(file_out, "wb");
	if(!f_out){
		puts("К сожалению, не удалось открыть файл.");
		return;
	}
	
	fwrite(&bmfh, 1, sizeof(BitmapFileHeader),f_out);
	fwrite(&bmif, 1, sizeof(BitmapInfoHeader),f_out);
	
	unsigned int height = bmif.height;
	unsigned int width = bmif.width ;
	// n - строка (arr[n][])
	// m - столбец (arr[][m])
	int start_n = right_corner.n , start_m = left_corner.m ;
	int end_n = left_corner.n, end_m = right_corner.m;
	
	if((start_n > end_n) || (start_m > end_m)){
        puts("Точки левого верхнего левого угла не могут лежать правее и ниже точек правого нижнего угла");
        return;
    }
    if((end_n > height) || (end_m > width)){
        printf("Вы вышли за границы изображения, повторите попытку.\nВысота:%d\nШирина:%d\n", height, width);
        return;
    }
	
	if(strcmp(color_line, "black_standart") == 0){
		puts("Вы не выбрали цвет из предложенной палитры, на данный момент цвет рамки прямоугольника был установлен по умолчанию - ""black""");
		puts("Палитра:");
		puts("* red");
		puts("* green");
		puts("* blue");
		puts("* black");
		puts("* white");
		puts("* yellow");
		puts("* orange");
		puts("* brown");
		puts("* grey");
		puts("* pink");
		puts("* olive");
		strcpy(color_line, "black");
	}
	if((strcmp(color_rec, "black_standart") == 0) && (strcmp(fill,"y") == 0)){
		puts("Вы не выбрали цвет из предложенной палитры, на данный момент цвет прямоугольника был установлен по умолчанию - ""black""");
		puts("Палитра:");
		puts("* red");
		puts("* green");
		puts("* blue");
		puts("* black");
		puts("* white");
		puts("* yellow");
		puts("* orange");
		puts("* brown");
		puts("* grey");
		puts("* pink");
		puts("* olive");
		strcpy(color_rec, "black");
	}
	check_color(color_line);
	check_color(color_rec);

	if(strcmp(fill,"y") == 0){
		for(int n = start_n; n < end_n; n++){
			for(int m = start_m; m < end_m; m ++){
				if((n <= start_n+line) || (m <= start_m+line) || (n >= end_n-line-1) || (m >= end_m-line-1)){
					color(&arr[n][m], color_line);
				}
				else{
					color(&arr[n][m], color_rec);
				}
				
			}
		}
	}
	else{	
		for(int n = start_n; n < end_n; n++){
			for(int m = start_m; m < end_m; m ++){
				if((n <= start_n+line) || (m <= start_m+line) || (n >= end_n-line-1) || (m >= end_m-line-1)){
					color(&arr[n][m], color_line);
				}
				
			}
		}

	}

	unsigned int w = width * sizeof(Rgb) + (3*width)%4;
	for(int k=0; k < height; k++){
		fwrite(arr[k],1, w, f_out);
	}
	
	fclose(f_out);
}

int rectangle(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex){
	char file_out[50];
	strcpy(file_out, argv[--argc]);
	char *optsRec = "l::r::t:c:f:C:?";
	struct option longRec[] = {
	{"left_up_corner", optional_argument, 0 , 'l' },
	{"right_down_corner", optional_argument, 0, 'r'},
	{"line_thickness", required_argument, 0, 't'},
	{"line_color", required_argument, 0, 'c'},
	{"fill", required_argument, 0, 'f'},
	{"color", required_argument, 0, 'C'},
	{ NULL, 0, NULL, 0}
	};
	opt = getopt_long(argc, argv, optsRec, longRec, &longIndex);

	int line = 1;
	char color[20];
	Point left_up_corner;
	Point right_down_corner;
	char fill[20]; 
	strcpy(fill,"n");
	char color_fill[20];

	left_up_corner.n = 0;
	left_up_corner.m = 0;
	right_down_corner.n = 0;
	right_down_corner.m = 0;
	
	strcpy(color_fill,"black_standart");
	strcpy(color,"black_standart");

	while(opt!=-1){
		switch (opt)
		{
		case 'l':
			left_up_corner.m = atoi(argv[optind]);
			left_up_corner.n = atoi(argv[optind + 1]);
			break;
		
		case 'r':
			right_down_corner.m = atoi(argv[optind]);
			right_down_corner.n = atoi(argv[optind + 1]);
			break;

		case 't':
			line = atoi(optarg);
			break;

		case 'c':
			strcpy(color, optarg);
			break;

		case 'f':
			strcpy(fill,optarg);
			break;

		case 'C':
			strcpy(color_fill, optarg);
			break;

		case '?':
			printHelp();
			exit(0);	
		}
		opt = getopt_long(argc, argv, optsRec, longRec, &longIndex);
	}
	if((left_up_corner.n ==0) && (left_up_corner.m == 0)&&(right_down_corner.n == 0)&&(right_down_corner.m == 0)){
		puts("Недостаточно аргументов."); 
		puts("Введите точки левого верхнего угла (--left_up_corner <value> <value>) и точки нижнего правого угла (--right_down_corner <value> <value>)");
		exit(0);
	}
	recBmp(bmfh, bmif, arr, left_up_corner, right_down_corner, line, color, fill, color_fill, file_out);
	

}








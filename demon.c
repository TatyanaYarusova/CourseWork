#include "info.h"

void width(Rgb** arr, int x, int y, int line, int h, int w, char* c){
	line = line/2;
	for(int n = x - line; n <= x+line; n++){
		for(int m = y- line; m <= y + line; m++){
			if((n >= 0) && (x < h) && (m >= 0)&& (m < w)&&(pow(x-n,2)+pow(y-m,2) <= pow(line,2)))
				color(&arr[n][m],c);
		}
	}
}

void drawLine(Rgb** arr,int x1, int y1, int x2, int y2, int line, int h, int w, char* c){
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    while((x1 != x2) || (y1 != y2)){
		width(arr, x1, y1, line, h, w, c);
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }

}

void drawStar(Rgb** arr, Point center, int r, int line, char* c, int h, int w){
	Point corner[5];
	for(int i = 0; i < 5; i++){
		corner[i].n = center.n + r*sin((72 * i + 90)*M_PI / 180.0);
		corner[i].m = center.m + r*cos((72 * i + 90)*M_PI / 180.0);

	}
	for(int i = 0; i < 5; i++){
		drawLine(arr, corner[i].n, corner[i].m, corner[(i+2)%5].n, corner[(i+2)%5].m, line, h, w, c);
	}
	
}

void drawCircle(Rgb** arr, Point center, int R, int line, int h, int w, char* c){
	
	int x = 0;
	int y = R;
	int delta = 1 - 2*R;
	int error = 0;
	while(y >= x ){
		width(arr, center.n+x, center.m+y, line, h, w, c);
		width(arr, center.n+x, center.m-y, line, h, w, c);
		width(arr, center.n-x, center.m+y, line, h, w, c);
		width(arr, center.n-x, center.m-y, line, h, w, c);
		width(arr, center.n+y, center.m+x, line, h, w, c);
		width(arr, center.n+y, center.m-x, line, h, w, c);
		width(arr, center.n-y, center.m+x, line, h, w, c);
		width(arr, center.n-y, center.m-x, line, h, w, c);	
		error = 2 *(delta + y) - 1;
		if((error <= 0) && (delta < 0)){
			x++;
			delta += 2 * x + 1;
			continue;
		}

		if(delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		--y;
		delta += 2 * (x - y);
		
	}

}

void starBmp(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, Point center, int Radius, int line, char* color, char* file_out){
	
	FILE* f_out = fopen(file_out, "wb");
	if(!f_out){
		puts("К сожалению, не удалось открыть файл.");
		return;
	}

	unsigned int height = bmif.height;
	unsigned int width = bmif.width ;
	
	fwrite(&bmfh, 1, sizeof(BitmapFileHeader),f_out);
	fwrite(&bmif, 1, sizeof(BitmapInfoHeader),f_out);
	
	int r = Radius - line+1;

    if(strcmp(color, "black_standart") == 0){
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
		strcpy(color, "black");
	}
    check_color(color);

	drawCircle(arr, center, Radius, line, bmif.height, bmif.width, color);
	drawStar(arr, center, r, line, color, bmif.height, bmif.width);
	

	unsigned int w = width * sizeof(Rgb) + (3*width)%4;
	for(int k=0; k < height; k++){
		fwrite(arr[k],1, w, f_out);
	}
	
	fclose(f_out);
}

int demon(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex){
	char filename[50];
	strcpy(filename, argv[--argc]);
	char *optsDem = "c::r:l:u::d::C:?";
	struct option longDem[] = {
	{"center", optional_argument, 0 , 'c' },
	{"radius", required_argument, 0, 'r'},
    {"left_up_corner", optional_argument, 0 , 'u' },
	{"right_down_corner", optional_argument, 0, 'd'},
	{"line", required_argument, 0, 'l'},
	{"color", required_argument, 0, 'C'},
	{ NULL, 0, NULL, 0}
	};
	opt = getopt_long(argc, argv, optsDem, longDem, &longIndex);

	int line = 1;
    int radius = 0;
	
    char color[20];
    strcpy(color,"black_standart");
	
    Point center;
    center.n = 0;
    center.m = 0;
    
    Point left_up;
    left_up.n = 0;
    left_up.m = 0;
    Point right_down;
    right_down.n = 0;
    right_down.m = 0;
    int flag = 0;
    int flag_center = 0;
    int flag_square = 0;

    int h = bmif.height;
    int w = bmif.width;
	
	while(opt!=-1){
		switch (opt)
		{
		case 'c':
			center.m = atoi(argv[optind]);
			center.n = atoi(argv[optind + 1]);
            flag++;
            flag_center++;
			break;
		
		case 'r':
			radius = atoi(optarg);
            flag++;
            flag_center++;
			break;

        case 'u':
			left_up.m = atoi(argv[optind]);
			left_up.n = atoi(argv[optind + 1]);
            flag++;
            flag_square++;
			break;

        case 'd':
			right_down.m = atoi(argv[optind]);
			right_down.n = atoi(argv[optind + 1]);
            flag++;
            flag_square++;
			break;

		case 'l':
			line = atoi(optarg);
			break;

		case 'C':
			strcpy(color, optarg);
			break;

		case '?':
			printHelp();
			exit(0);	
		}
		opt = getopt_long(argc, argv, optsDem, longDem, &longIndex);
	}
    if(flag > 2){
        puts("Введите ЛИБО координаты центра окружности и радиус, ЛИБО угол левого верхнего угла и правого нижнего угла");
        exit(0);;
    }
    if(flag < 2){
        puts("Вы ввели недостаточно аргументов.");
        exit(0);
    }
    if((flag_center != 0) && (flag_square != 0)){
        puts("Ошибка!");
        puts("Введите ЛИБО координаты центра окружности и радиус, ЛИБО угол левого верхнего угла и правого нижнего угла");
        exit(0);
    }

   

    if(flag_square == 2){
        if((right_down.m > left_up.m)&&(left_up.n > right_down.n)){
            radius = (right_down.m - left_up.m)/2;
            center.n = (left_up.n + right_down.n)/2;
            center.m = (right_down.m + left_up.m)/2;
        }
        else{
             if((right_down.m - left_up.m) == (left_up.n - right_down.n)){
                puts("Координаты не соответствуют условию.");
                exit(0);
            }
            else{
                puts("Вы ввели координаты прямоугольника, а не квадрата.");
                exit(0);
            }
        }
    }
    if((center.n > 0)&&(center.m > 0)&&(center.n < h)&&(center.m < w)&&(center.n + radius < h)&&(center.n - radius > 0)&&(center.m + radius < w)&&(center.m - radius > 0)){
        starBmp(bmfh, bmif, arr, center, radius, line, color, filename);
    }
    else{
        puts("Вы вышли за границы изображения.");
        printf("Высота: %d.\n", h);
        printf("Ширина: %d.", w);
        exit(0);
    }
	
}


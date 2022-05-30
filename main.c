#include "info.h"

int main(int argc, char **argv){
	
	char *opts = "crdRqh?"; 
	int opt;
	int longIndex;// индекс элемента в структуре longopts[]
	struct option longOpts[] = {
	{"collage", no_argument, 0, 'c'},
	{"reflection", no_argument, 0, 'r'},
	{"demon", no_argument, 0, 'd'},
	{"rectangle", no_argument, 0, 'R'},
	{"help", no_argument, 0, 'h'},
	{ NULL, 0, NULL, 0}
	};
	opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	
	if (opt == -1){
        printHelp();
        return 0;
    }

	if (!strcmp(argv[1],"--help") || !strcmp(argv[1],"-h")){	
		printHelp();
    	return 0;
    }

	if(argv[1][0] == '-'){
		puts("Вы не ввели имя файла, который хотите обработать.\nОзнакомьтесь с работой программы.\n");
		printHelp();
		return 0;
	}

	if(argv[argc -1][0] == '-'){
		puts("Вы не ввели имя файла, в который хотите записать результат рабо ты программы.\nОзнакомьтесь с работой программы.\n");
		printHelp();
		return 0;
	}

	char file[50];
	strcpy(file,argv[1]);

	FILE* image = fopen(file, "rb");
	if(!image){
		puts("К сожалению, не удается открыть файл.");
		return 0;
	}

	BitmapFileHeader bmfh;
	BitmapInfoHeader bmif;

	fread(&bmfh,1,sizeof(BitmapFileHeader),image);
	fread(&bmif, 1, sizeof(BitmapInfoHeader), image);

	if (bmfh.signature != 0x4d42){
        printf("Файл не соотвествует формату bmp. Пожалуйста, выберите другой файл.\n");
        return 0;
    }
    if (bmif.bitsPerPixel != 24){
        printf("Глубина цвета данного файла не 24 пикселя на бит. Пожалуйста, выберите другой файл.\n");
        return 0;
    }
    if (bmif.colorsInColorTable != 0){
        printf("Для данного файла используется таблица цветов. Пожалуйста,выберите другой файл.\n");
        return 0;
    }
    if (bmif.compression != 0){
        printf("Изображение сжатое. Пожалуйста, выберите другой файл.\n");
        return 0;
    }

	unsigned int height = bmif.height;
	unsigned int width = bmif.width ;

	Rgb** arr = malloc(height*sizeof(Rgb*)+ (3*height)%4);
	for(int i = 0; i < height; i++){
		arr[i] = malloc(width *sizeof(Rgb)+(3*width)%4);
		fread(arr[i],1 , width * sizeof(Rgb) + (3*width)%4, image);
	}

	while(opt!=-1){
		switch(opt){
			case 'c':
				opt = collage(bmfh, bmif, arr, argc, argv,opt,longIndex);
				break;

			case 'r':
				opt = reflection(bmfh, bmif, arr, argc, argv,opt,longIndex);
				break;

			case 'd':
				opt = demon(bmfh, bmif, arr, argc, argv,opt,longIndex);
				break;

			case 'R':
				opt = rectangle(bmfh, bmif, arr, argc, argv,opt,longIndex);                
				break;

			case 'h':
			case '?':
				printHelp();
				exit(0);
		}
		opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	}

	free_memory(arr, height);
	fclose(image);
	return 0;
    
}

#include "info.h"

void swap(Rgb *a, Rgb *b){
	Rgb t = *a;
	*a = *b;
	*b = t;
}

void refBmp(Rgb** arr, Point left_corner, Point right_corner, BitmapFileHeader bmfh, BitmapInfoHeader bmif, char* axis, char* file_out){
	FILE* f_out = fopen(file_out, "wb");

	unsigned int height = bmif.height;
	unsigned int width = bmif.width ;

	fwrite(&bmfh, 1, sizeof(BitmapFileHeader),f_out);
	fwrite(&bmif, 1, sizeof(BitmapInfoHeader),f_out);
	
	int start_n = left_corner.n , start_m = right_corner.m ;
	int end_n = right_corner.n, end_m = left_corner.m;
	int raz;
	

    if((start_n > end_n) || (start_m > end_m)){
        puts("Точки левого верхнего левого угла не могут лежать правее и ниже точек правого нижнего угла");
        return;
    }
    if((end_n > width) || (end_m > height) || (start_n > width) || (start_m > height)){
        printf("Вы вышли за границы изображения, повторите попытку.\nВысота:%d\nШирина: %d\n", height, width);
        return;
    }
    int k = 0;
    if(strcmp(axis, "x") == 0){
        raz = end_m - start_m;
	    raz = raz/2;
        raz = start_m + raz;
        for(int i = start_m ; i < raz; i++ ){// строки
		    for(int j = start_n; j < end_n; j++){ // столбцы
			    swap(&arr[i][j],&arr[end_m-k-1][j]);
		    }
            k++;
        }
	}
    else{
        if(strcmp(axis, "y") == 0){
            raz = end_n - start_n;
	        raz = raz/2;
            raz = start_n + raz;
			for(int i = start_m ; i < end_m; i++ ){
				k = 0;
		    	for(int j = start_n; j < raz; j++){
			    	swap(&arr[i][j],&arr[i][end_n-k-1]);
					k++;
		    	}
            	  

            }   
        }
        else{
            puts("Выберите корректную ось (х или у)");
            return;
        }
    }


	unsigned int w = width * sizeof(Rgb) + (3*width)%4;
	for(int k=0; k < height; k++){
		fwrite(arr[k],1, w, f_out);
	}
	fclose(f_out);
}

int reflection(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex){
	char file_out[50];
	strcpy(file_out, argv[--argc]);
	char *optsRef = "a:l::r::?";
	struct option longRef[] = {
	{"axis", required_argument, 0, 'a'},
	{"left_up_corner", optional_argument, 0 , 'l' },
	{"right_down_corner", optional_argument, 0, 'r'},
	{ NULL, 0, NULL, 0}
	};
	opt = getopt_long(argc, argv, optsRef, longRef, &longIndex);

	char* axis;
	Point left_up_corner;
	Point right_down_corner;

	while(opt!=-1){
		switch (opt)
		{
		case 'a':
			axis = optarg;
			break;
		
		case 'l':
			left_up_corner.n = atoi(argv[optind]);
			left_up_corner.m = atoi(argv[optind + 1]);
			break;

		case 'r':
			right_down_corner.n = atoi(argv[optind]);
			right_down_corner.m = atoi(argv[optind + 1]);
			break;
		
		case '?':
			printHelp();
			exit(0);
		}
		opt = getopt_long(argc, argv, optsRef, longRef, &longIndex);
	}
	refBmp(arr,left_up_corner, right_down_corner, bmfh, bmif, axis, file_out);
	return opt;

}

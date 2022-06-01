#include "info.h"

void colBmp(Rgb** arr, int M, int N, BitmapFileHeader bmfh, BitmapInfoHeader bmif, int flag, char* file_out){
	
	FILE* f_out = fopen(file_out, "wb");
	if(!f_out){
		puts("К сожалению, не удалось открыть файл.");
		return;
	}

	unsigned int height = bmif.height;
	unsigned int width = bmif.width;

	bmif.width = width * M;
    bmif.height = height * N;
	Rgb** out;
	out = malloc(height*N * sizeof(Rgb*));
	for(int i = 0; i < height*N; i++){
		out[i] = malloc(width*M* sizeof(Rgb));
	}
	
	fwrite(&bmfh, 1, sizeof(BitmapFileHeader),f_out);
	fwrite(&bmif, 1, sizeof(BitmapInfoHeader),f_out);
	
	for(int n = 0; n < height * N; n++){
		for(int m = 0; m < width * M; m++){
			out[n][m] = arr[n%height][m%width];
		}
	}
    
    unsigned int w = width * M * sizeof(Rgb) + (3*width*M)%4;
        for(int k=0; k < height*N; k++){
            fwrite(out[k], 1 , w, f_out);
        }
	if(flag){
		printFileHeader(bmfh);
		printInfoHeader(bmif);
	}
    
	free_memory(out, height*N);	
	fclose(f_out);
}

int collage(BitmapFileHeader bmfh, BitmapInfoHeader bmif, Rgb** arr, int argc, char **argv,int opt, int longIndex){
	char filename[50];
	strcpy(filename, argv[--argc]);
	char *optsC= "x:y:i?";
	struct option longC[] = {
	{"count_x", required_argument, 0, 'x'},
	{"count_y", required_argument, 0, 'y'},
	{"info", no_argument, 0, 'i'},
	{ NULL, 0, NULL, 0}
	};
	int N = 1;
	int M = 1;
	int flag = 0;
	opt = getopt_long(argc, argv, optsC, longC, &longIndex);
	while(opt!=-1){
		switch (opt)
		{
		case 'x':
			M = atoi(optarg);
			break;
		
		case 'y':
			N = atoi(optarg);
			break;
		
		case 'i':
			flag++;
			break;

		case '?':
			printHelp();
			exit(0);
		
		}
		opt = getopt_long(argc, argv, optsC, longC, &longIndex);
	}
	if((N > 10)||(M > 10)){
		puts("Вы превысили максимальные параметры коллажа.");
		esit(0);
	}
	colBmp(arr, M, N, bmfh, bmif, flag, filename);
	return opt;

}

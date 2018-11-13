#include "../rps.h"


void op(int t, struct DATA *p){
	int i, s;
	char name[100];
	FILE *file;

	for(s= 1; s<= NS; s++){
		sprintf(name, "dat/p-%d-%d.dat", s, t);
		file= fopen(name, "w");
		for(i= 0; i< N; i++){
			if(p[i].s == s){
				fprintf(file, "%e %e\n", p[i].x, p[i].y);
			}
		}
		fclose(file);
	}
}


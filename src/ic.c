#include "../rps.h"

void ic(const gsl_rng *w, struct DATA *p){
	int i, s;
//	double th;

	for(s= 1; s<= NS; s++){
		for(i= (s-1)*N/NS; i< s*N/NS; i++){
			p[i].s= s;
//			th= 2.0*M_PI*gsl_rng_uniform(w);
//			p[i].vx= cos(th);
//			p[i].vy= sin(th);
			p[i].x= gsl_rng_uniform(w)*L;
			p[i].y= gsl_rng_uniform(w)*L;
		}
	}
}


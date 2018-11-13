#include "../rps.h"

#define r (double)NG/NF
#define q pow(NG, 1.0/(NF-1))

void ic(const gsl_rng *w,        struct DATA *p);
void op(                  int t, struct DATA *p);
void  m(const gsl_rng *w, int n, struct DATA *p);

int main(int argc, char **argv){
	int i, j, n, t, o, who_died= 0, t_ext= 0;
	int l= 0;
	int *dst;
	double dx, dy, dm, act, n_m, n_p;
	struct DATA *p;
	PROBABILITY_OF_PREDATION
	FILE *file;

#if LS == 1
	double a0= 1.0;
#else
	double a0= r;
#endif

	p  = (struct DATA *) calloc(N,    sizeof(struct DATA));
	dst= (int *)         calloc(NS+1, sizeof(int)        );

	gsl_rng_default_seed= (argc == 2) ? atoi(argv[1]) : time(NULL);
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

	ic(w, p);
	op(0, p);

	file= fopen("dat/dst.dat", "a");
	for(i= 0; i< N; i++){
		dst[p[i].s]++;
	}
	for(i= 1; i<= NS; i++){
		fprintf(file, "%e ", (double)dst[i]/N);
	}
	fprintf(file, "\n");
	fclose(file);

	n_m= n_p= 0.0;
	for(t= 1; t<= NG; t++){
		i= 0;
		while(i < N){
			n= gsl_rng_uniform(w)*N;
			act= gsl_rng_uniform(w); 
			if(act < pm){
/* mobility  - begin */
				m(w, n, p);
				n_m++;
				i++;
/* mobility  - end   */
			}else{
/* predation - begin */
				dm= L; o= -1;
				for(j= 0; j< N; j++){
					if(mp[(p[n].s-1)*NS+p[j].s-1] == 1){
						dx= fabs(p[j].x-p[n].x);
						if(dx > 0.5*L){dx-= L;}
						dy= fabs(p[j].y-p[n].y);
						if(dy > 0.5*L){dy-= L;}
						if(sqrt(dx*dx+dy*dy) < l_p){
							if(dm > sqrt(dx*dx+dy*dy)){
								dm= sqrt(dx*dx+dy*dy);
								o= j;
							}
						}
					}
				}
				if(o != -1){
					dst[p[o].s]--;
					p[o].s= p[n].s;
//					p[o].vx= p[n].vx;
//					p[o].vy= p[n].vy;
					dst[p[o].s]++;
					n_p++;
					i++;
				}
/* predation - end   */
			}
		}
		file= fopen("dat/dst.dat", "a");
		for(i= 1; i<= NS; i++){
			fprintf(file, "%e ", (double)dst[i]/N);
			if(dst[i] == 0){
				who_died= i;
				t_ext= t;
				t= NG;
			}
		}
		fprintf(file, "\n");
		fclose(file);
		if(t >= round(a0)){
#if LS == 1
			a0*= q;
#else 
			a0+= r;
#endif
			op(++l, p);
			printf("%d %d/%d\n", l, t, NG);
		}
	}
	file= fopen("dat/sur.dat", "a");
	if(t_ext != 0){
		fprintf(file, "%d %d\n", who_died, t_ext);
	}else{
		fprintf(file, "%d %d\n", 0, NG);
	}
	fclose(file);

	file= fopen("dat/m_p.dat", "a");
	fprintf(file, "%e %e\n", n_m, n_p);
	fclose(file);

	gsl_rng_free(w);
	free(p);
	free(dst);
	return 0;
}

void m(const gsl_rng *w, int n, struct DATA *p){

/* random mobility - begin */
	double th;
	th= 2.0*M_PI*gsl_rng_uniform(w);
	p[n].x+= l_m*cos(th);
	if(p[n].x > L  ){p[n].x-= L;}
	if(p[n].x < 0.0){p[n].x+= L;}
	p[n].y+= l_m*sin(th);
	if(p[n].y > L  ){p[n].y-= L;}
	if(p[n].y < 0.0){p[n].y+= L;}
//	p[n].vx= cos(th);
//	p[n].vy= sin(th);
/* random mobility - end   */

//	int i, s, z= 0;
//	double dx, dy, th, vx, vy;
//	s= p[n].s;
//	vx= 0.0;
//	vy= 0.0;
//	for(i= 0; i< N; i++){
//		if(p[i].s == s){
//			dx= (p[i].x-p[n].x);
//			if(dx >  0.5*L){dx-= L;}
//			if(dx < -0.5*L){dx+= L;}
//			dy= (p[i].y-p[n].y);
//			if(dy >  0.5*L){dy-= L;}
//			if(dy < -0.5*L){dy+= L;}
//			if(sqrt(dx*dx+dy*dy) < l_m){
//				vx+= p[i].vx;
//				vy+= p[i].vy;
////				vx+= dx;
////				vy+= dy;
//				z++;
//			}
//		}
//	}
//	if(z == 0){
//		th= 2.0*M_PI*gsl_rng_uniform(w);
//	}else{
//		th= atan2(vy, vx) + eta*(gsl_rng_uniform(w)-0.5);
//	}
//	p[n].x+= l_m*cos(th);
//	if(p[n].x > L  ){p[n].x-= L;}
//	if(p[n].x < 0.0){p[n].x+= L;}
//	p[n].y+= l_m*sin(th);
//	if(p[n].y > L  ){p[n].y-= L;}
//	if(p[n].y < 0.0){p[n].y+= L;}
//	p[n].vx= cos(th);
//	p[n].vy= sin(th);
}

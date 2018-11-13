#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics.h>

#define N   1500   /* number of individuals          */
#define L   1.0    /* grid size                      */
#define l_m 0.02   /* radius of interections - mob.  */
#define l_p 0.02   /* radius of interections - pre.  */
#define NG  1000   /* number of generations          */
#define NF  1      /* number of output files         */
#define LS  0      /* 0-> nolog time || 1-> log time */
#define NS  3      /* number of types of species     */
#define eta 0.0    /* noise strength                 */
#define pm  0.5    /* probability of motion          */
#define PROBABILITY_OF_PREDATION \
const double mp[NS*NS]= {\
	0.0, 1.0, 0.0, \
	0.0, 0.0, 1.0, \
	1.0, 0.0, 0.0, \
};

struct DATA{
	int     s;
	double  x;
	double  y;
	double vx;
	double vy;
};

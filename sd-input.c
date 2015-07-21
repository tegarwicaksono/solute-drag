int ij, kl, mn;
int NSEGMENT  = 800000;
int NVELOC    = 100;
int NVARW     = 1;
int varw;

char   triagprof[] = "TRI";
char   gaussprof[] = "GAU";

double bulkConc = 0.01;

double intwidth = 2.0;

double alpha, beta;

double enerMax  = -2.0;
double enerBulk =  0.0;
double diffMax  =  1.0e-6;
double diffBulk =  1.0;

double coeffA = 0;
double coeffB = 0;
double coeffC = 4.0;

double factorveloc = 0.1;
double startX, finishX, segmentX;

double *dist, *diff, *ener;
double *concNew, *concLSM, *concJWC;
double *grad, *integral;

double *arrayPjwc, *arrayQjwc, *arrayRjwc;

double *veloc, velocity;

double PdJWC = 0.0;
int PREFIX1;

FILE *result;
clock_t	start;

void BuildArray(void) {

  setbuf(stdout, NULL);
  srand (time(NULL));
  PREFIX1 = rand()%100000;
	printf("Prefix = %d\n",PREFIX1);
  dist		= (double *)malloc(NSEGMENT*sizeof(double));
  diff		= (double *)malloc(NSEGMENT*sizeof(double));
  ener		= (double *)malloc(NSEGMENT*sizeof(double));
  grad		= (double *)malloc(NSEGMENT*sizeof(double));

  concJWC	= (double *)malloc(NSEGMENT*sizeof(double));

  integral	= (double *)malloc(NSEGMENT*sizeof(double));

  arrayPjwc	= (double *)malloc(NSEGMENT*sizeof(double));
  arrayQjwc	= (double *)malloc(NSEGMENT*sizeof(double));
  arrayRjwc	= (double *)malloc(NSEGMENT*sizeof(double));

  veloc 	= (double *)malloc(NVELOC  *sizeof(double));
}

void BuildInitial(void) {
  startX   = -1.0*5.0;
  finishX  = +1.0*5.0;
  segmentX = (finishX - startX)/(double)NSEGMENT;

  concJWC[0] = bulkConc;
  concJWC[1] = bulkConc;
  
  for (ij = 0; ij < 23; ij++)  veloc[ij] = (ij + 1)*0.1;
  veloc[23] = 2.5;
  veloc[24] = 2.7;
  veloc[25] = 2.9;

  for (ij = 26; ij < 50; ij++) veloc[ij] = (ij - 26)*0.5 + 3.0;
  for (ij = 50; ij < NVELOC; ij++) veloc[ij] = (ij - 50)*2.0 + 16.0;

	for (ij = 0; ij < NVELOC; ij++) veloc[ij] = veloc[ij]*factorveloc;
}

void BuildInput(void) {
  BuildArray();
  BuildInitial();
}

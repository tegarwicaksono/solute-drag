void StartRecordFile(void) {
  char resname[] = "./result/Pd_Veloc_ID%d-width=%.2lf-(Dmax,Dbulk)=(%.3e,%.3e)-(Emax,bulk)=(%.3e,%.3e).txt";
  char resfile[sizeof resname+400];

  sprintf(resfile,resname,PREFIX1,intwidth,diffMax,diffBulk,enerMax,enerBulk);
  result = fopen(resfile, "w");
 
  fprintf(result,"Velocity\t");
	fprintf(result,"DragPressure\t");
  fprintf(result,"\n");
}

void CloseRecordFile(void) {
  fclose(result);
}

void PrintProfile(void) {
  int index;
  char proname[] = "./profile/ConcProfile_ID%d-width=%.2lf-(Dmax,Dbulk)=(%.3e,%.3e)-(Emax,bulk)=(%.3e,%.3e).txt";
  char file[sizeof proname+400];
	double sum;
	int count;
  FILE *profile;
  sprintf(file,proname,PREFIX1,intwidth,diffMax,diffBulk,enerMax,enerBulk);
  profile = fopen(file, "w");

	sum = 0.0;

  for (index = 2, count = 0; index < NSEGMENT-1; index++) {
		if (( dist[index] >= -0.5*intwidth) && (dist[index] <= 0.5*intwidth)) {
			sum += (concJWC[index] - bulkConc);
			count++;
		}
	}

  fprintf(profile,"Dist\tDiffusivity\tBindingEnergy\tGradBindEner\t\tConc\tSum =\t%.8e\tCount\t%d\tAlpha =\t%.8E\t\tBeta =\t%.8E", sum, count,alpha, beta);
  fprintf(profile,"\n");

  for (index = 2; index < NSEGMENT-1; index++) {
    fprintf(profile,"%.8lf\t", dist[index]);
    fprintf(profile,"%.8lf\t", diff[index]);
    fprintf(profile,"%.8lf\t", ener[index]);
    fprintf(profile,"%.8lf\t", grad[index]);
    fprintf(profile,"\t");
    fprintf(profile,"%.8lf\t", concJWC[index] - bulkConc);
    fprintf(profile,"\t");
    fprintf(profile,"\t");
    fprintf(profile,"\t");
//    fprintf(profile,"%.8lf\t", arrayPjwc[index]);
//    fprintf(profile,"%.8lf\t", arrayQjwc[index]);
//    fprintf(profile,"%.8lf\t", arrayRjwc[index]);

    fprintf(profile,"\n");
  }
  fclose(profile);
}
void RecordVelocity(void){
  fprintf(result, "%.6lf\t", velocity);
}
void RecordResult(void){
  fprintf(result, "%.8lf\t", PdJWC);
}

void RecordEndLine(void) {
  fprintf(result, "\n");
}

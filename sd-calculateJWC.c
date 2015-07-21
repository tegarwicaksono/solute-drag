double PconstJWC(int id) {
  return (concJWC[id-1] - concJWC[id-2])*( (1.0 - diff[id-2]/diff[id-1]) + ener[id-1] - ener[id-2] + velocity*segmentX/diff[id-1] );
}

double QconstJWC(int id) {
  return concJWC[id-1]*( (1.0 - diff[id-2]/diff[id-1])*(ener[id-1] - ener[id-2]) + ener[id] + ener[id-2] - 2*ener[id-1]);
}

double RconstJWC(int id) {
  return 0.0;
} 

void BuildConcJWC(void) {
  for (kl = 2; kl < NSEGMENT; kl++) {
    arrayPjwc[kl] = PconstJWC(kl);
    arrayQjwc[kl] = QconstJWC(kl);
    arrayRjwc[kl] = RconstJWC(kl);
    concJWC[kl] = 2.0*concJWC[kl-1] - concJWC[kl-2] - (arrayPjwc[kl] + arrayQjwc[kl] + arrayRjwc[kl]);
  }
}

void IntegrateJWC(void) {
  double segmentintegral;
  PdJWC = 0.0;
  for (kl = 1; kl < NSEGMENT - 1; kl++)  {
    segmentintegral = grad[kl]*(concJWC[kl] - bulkConc);
    PdJWC += segmentintegral;
  }
  PdJWC = -1.0*PdJWC*segmentX;
}

void CalculateAlpha(void) {
	double segmentintegral;
	alpha = 0.0;

	for (kl = 1; kl < NSEGMENT - 1; kl++) {
		segmentintegral = (sinh(0.5*ener[kl]))*(sinh(0.5*ener[kl]))/diff[kl];
		alpha += segmentintegral;
	}
	alpha = 4.0*alpha*segmentX;
}

void CalculateBeta(void) {
	double segmentintegral;
	beta = 0.0;

	for (kl = 1; kl < NSEGMENT - 1; kl++) {
		segmentintegral = (grad[kl])*(grad[kl])*diff[kl];
		beta += segmentintegral;
	}
	beta = beta*segmentX;
	beta = sqrt(alpha / beta);
}
void CalcPdJWC(void) {
  BuildConcJWC();
  IntegrateJWC();
}

void CalcAlphaBeta(void) {
	CalculateAlpha();
	CalculateBeta();
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sd-input.c"
#include "sd-enerdiff.c"
#include "sd-printresult.c"
#include "sd-calculateJWC.c"


void PerformCalculation(void) {
  int count;
  for (count = 0; count < NVELOC; count++) {
    velocity = veloc[count];
    RecordVelocity();
    for (varw = 0; varw < NVARW; varw++) {
      BuildVarArray();
      CalcPdJWC();
      RecordResult();

//if (count == 5)       PrintProfile();
//if (count == 5)	printf("veloc = %.2e\tPdrag = %.4e\n", veloc[count], PdJWC);

    }
    RecordEndLine();
  }
}

int main(void) {
  BuildInput();
//  BuildVarArray();

  StartRecordFile();
  PerformCalculation();
			CalcAlphaBeta();
      PrintProfile();
  CloseRecordFile();
  return 0;
}

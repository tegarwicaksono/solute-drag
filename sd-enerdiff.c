double diffTriangle(int id) {
  if (dist[id] < -intwidth / 2.0) 
    return diffBulk;
  else if ( (dist[id] >= -intwidth / 2.0) && (dist[id] <= 0.0) )
    return diffMax + 2.0 * dist[id] * (diffMax - diffBulk) / intwidth;
  else if ( (dist[id] > 0.0) && (dist[id] <= intwidth / 2.0) )
    return diffMax - 2.0 * dist[id] * (diffMax - diffBulk) / intwidth;
  else
    return diffBulk;
}

double enerTriangle(int id) {
  if (dist[id] < -intwidth / 2.0) 
    return enerBulk;
  else if ( (dist[id] >= -intwidth / 2.0) && (dist[id] <= 0.0) )
    return enerMax + 2.0 * dist[id] * (enerMax - enerBulk) / intwidth;
  else if ( (dist[id] > 0.0) && (dist[id] <= intwidth / 2.0) )
    return enerMax - 2.0 * dist[id] * (enerMax - enerBulk) / intwidth;
  else
    return enerBulk;
}

void BuildDist(void) {
  for (kl = 0; kl < NSEGMENT; kl++) dist[kl] = startX + kl*segmentX;
}

void BuildDiff(void) {
  for (kl = 0; kl < NSEGMENT; kl++) diff[kl] = diffTriangle(kl);
}

void BuildEner(void) {
  for (kl = 0; kl < NSEGMENT; kl++) ener[kl] = enerTriangle(kl);
}

void BuildGrad(void) {
  double factor = 1.0;
  grad[0] = 0.0; 
  for (kl = 1; kl < NSEGMENT; kl++)  {
    grad[kl] = factor*((ener[kl] - ener[kl-1])/segmentX);
  }
}

void BuildVarArray(void) {
  BuildDist();
  BuildEner();
  BuildGrad();
  BuildDiff();
}

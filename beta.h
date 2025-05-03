#ifndef BETA_H
#define BETA_H

typedef struct {
    double alpha;
    double beta;
} BetaDist;

BetaDist create_beta(double alpha, double beta);
double sample_beta(BetaDist dist);
double expected_beta(BetaDist dist);
void update_beta(BetaDist *dist, int success);

#endif

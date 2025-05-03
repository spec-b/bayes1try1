#include "beta.h"
#include <stdlib.h>
#include <math.h>

double uniform_random() {
    return rand() / (double)RAND_MAX;
}

// Box-Muller transform for standard normal
double standard_normal() {
    double u = uniform_random();
    double v = uniform_random();
    return sqrt(-2 * log(u)) * cos(2 * M_PI * v);
}

// Gamma distribution sample (Marsaglia & Tsang method)
double sample_gamma(double shape) {
    if (shape < 1) shape += 1; // boost to >1
    double d = shape - 1.0 / 3.0;
    double c = 1.0 / sqrt(9.0 * d);
    while (1) {
        double x = standard_normal();
        double v = pow(1 + c * x, 3);
        if (v > 0 && uniform_random() < 1 - 0.331 * pow(x, 4)) {
            return d * v;
        }
    }
}

// Sample from Beta(α, β) by sampling two Gamma variables
double sample_beta(BetaDist dist) {
    double a = sample_gamma(dist.alpha);
    double b = sample_gamma(dist.beta);
    return a / (a + b);
}

double expected_beta(BetaDist dist) {
    return dist.alpha / (dist.alpha + dist.beta);
}

BetaDist create_beta(double alpha, double beta) {
    BetaDist dist = {alpha, beta};
    return dist;
}

void update_beta(BetaDist *dist, int success) {
    if (success)
        dist->alpha += 1;
    else
        dist->beta += 1;
}

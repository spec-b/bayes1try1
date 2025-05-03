#include "rules.h"
#include "beta.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

InferenceRule rule_set[NUM_RULES];

int rule1() { return rand() % 2; }  // 50% success
int rule2() { return rand() % 3 == 0; }  // ~33% success
int rule3() { return rand() % 4 == 0; }  // ~25% success

void init_rules() {
    srand(time(NULL));
    rule_set[0] = (InferenceRule){"Modus Ponens", create_beta(1, 1), rule1};
    rule_set[1] = (InferenceRule){"Necessitation", create_beta(1, 1), rule2};
    rule_set[2] = (InferenceRule){"Box Distribution", create_beta(1, 1), rule3};
}

InferenceRule *select_rule_thompson() {
    double best_sample = -1.0;
    int best_index = 0;
    for (int i = 0; i < NUM_RULES; i++) {
        double sample = sample_beta(rule_set[i].belief);
        if (sample > best_sample) {
            best_sample = sample;
            best_index = i;
        }
    }
    return &rule_set[best_index];
}

void update_rule(InferenceRule *rule, int success) {
    update_beta(&rule->belief, success);
}

void print_rule_stats() {
    for (int i = 0; i < NUM_RULES; i++) {
        double mean = expected_beta(rule_set[i].belief);
        printf("%s: alpha = %.2f, beta = %.2f, E[p] = %.2f\n",
               rule_set[i].name,
               rule_set[i].belief.alpha,
               rule_set[i].belief.beta,
               mean);
    }
}

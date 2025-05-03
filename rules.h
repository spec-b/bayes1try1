#ifndef RULES_H
#define RULES_H

#include "beta.h"

#define NUM_RULES 3

typedef struct {
    const char *name;
    BetaDist belief;
    int (*apply_rule)(void);  // returns 1 if success, 0 otherwise
} InferenceRule;

void init_rules();
InferenceRule *select_rule_thompson();
void update_rule(InferenceRule *rule, int success);
void print_rule_stats();

#endif

#include "rules.h"
#include <stdio.h>

int main() {
    init_rules();

    for (int round = 0; round < 100; round++) {
        InferenceRule *rule = select_rule_thompson();
        int success = rule->apply_rule();
        update_rule(rule, success);

        printf("[Round %d] Applied rule: %s → %s\n", round + 1, rule->name,
               success ? "SUCCESS" : "FAILURE");

        if ((round + 1) % 10 == 0) {
            printf("---- Rule Statistics ----\n");
            print_rule_stats();
            printf("-------------------------\n");
        }
    }

    return 0;
}

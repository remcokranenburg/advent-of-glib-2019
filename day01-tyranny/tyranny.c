#include <glib.h>

#include <stdio.h>
#include <string.h>

int calculate_fuel(int weight, gboolean include_fuel) {
    int additional_weight = MAX(weight / 3 - 2, 0);

    if(include_fuel && additional_weight > 0) {
        additional_weight += calculate_fuel(additional_weight, include_fuel);
    }

    return additional_weight;
}

int main(int argc, char *argv[]) {
    _Bool include_fuel = 0;

    for(int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "--include-fuel") == 0) {
            include_fuel = 1;
        }
    }

    int total_fuel_required = 0;

    for(;;) {
        int mass = 0;
        int tokens_scanned = scanf("%d", &mass);

        if(tokens_scanned <= 0) {
            break;
        }

        int fuel_required = calculate_fuel(mass, include_fuel);
        total_fuel_required += fuel_required;
    }

    printf("%d\n", total_fuel_required);
    return 0;
}

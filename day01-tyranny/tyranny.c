#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_recursive_fuel(int fuel) {
    int additional_fuel = fmax(fuel / 3 - 2, 0);

    if(additional_fuel > 0) {
        additional_fuel += calculate_recursive_fuel(additional_fuel);
    }

    return additional_fuel;
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
        int num_scanned = scanf("%d", &mass);

        if(num_scanned >= 0) {
            int fuel_required = fmax(mass / 3 - 2, 0);

            if(include_fuel) {
                fuel_required += calculate_recursive_fuel(fuel_required);
            }

            printf("%d\n", fuel_required);

            total_fuel_required += fuel_required;
        } else {
            break;
        }
    }

    printf("%d\n", total_fuel_required);
    return 0;
}

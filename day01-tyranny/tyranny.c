#include <glib.h>
#include <stdio.h>

gint calculate_fuel(gint weight, gboolean include_fuel) {
    gint additional_weight = MAX(weight / 3 - 2, 0);

    if(include_fuel && additional_weight > 0) {
        additional_weight += calculate_fuel(additional_weight, include_fuel);
    }

    return additional_weight;
}

gint main(gint argc, gchar *argv[]) {
    gboolean include_fuel = FALSE;

    g_autoptr(GString) include_fuel_argument = g_string_new("--include-fuel");

    for(gint i = 0; i < argc; i++) {
        g_autoptr(GString) argument = g_string_new(argv[i]);

        if(g_string_equal(argument, include_fuel_argument)) {
            include_fuel = TRUE;
        }
    }

    gint total_fuel_required = 0;

    for(;;) {
        gint mass = 0;
        gint tokens_scanned = scanf("%d", &mass);

        if(tokens_scanned <= 0) {
            break;
        }

        gint fuel_required = calculate_fuel(mass, include_fuel);
        total_fuel_required += fuel_required;
    }

    printf("%d\n", total_fuel_required);
    return 0;
}

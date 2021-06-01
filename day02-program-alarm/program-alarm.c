#include <glib.h>
#include <stdio.h>

gint main(gint argc, gchar *argv[]) {
    g_autoptr(GArray) numbers = g_array_new(FALSE, TRUE, sizeof(gint));

    for(;;) {
        gint number = 0;
        gint tokens_scanned = scanf("%d", &number);

        if(tokens_scanned <= 0) {
            break;
        }

        g_array_append_val(numbers, number);

        tokens_scanned = scanf(",");

        if(tokens_scanned < 0) {
            break;
        }
    }

    for(gint i = 0; i < numbers->len; i++) {
        printf("%d\n", g_array_index(numbers, gint, i));
    }

    return 0;
}

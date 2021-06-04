#include <glib.h>
#include <stdio.h>

void print_array(GArray *numbers) {
    if(numbers->len >= 1) {
        printf("%d", g_array_index(numbers, gint, 0));
    }

    for(gint i = 1; i < numbers->len; i++) {
        printf(", %d", g_array_index(numbers, gint, i));
    }

    printf("\n");
}

gint find_result(GArray *numbers_reference, gint noun, gint verb) {
    g_autoptr(GArray) numbers = g_array_copy(numbers_reference);

    g_array_index(numbers, gint, 1) = noun;
    g_array_index(numbers, gint, 2) = verb;

    // print_array(numbers);

    for(gint i = 0; i < numbers->len + 4; i += 4) {
        gint command = g_array_index(numbers, gint, i);

        if(command == 99) {
          break;
        }

        gint value1_index = g_array_index(numbers, gint, i + 1);
        gint value2_index = g_array_index(numbers, gint, i + 2);
        gint target_index = g_array_index(numbers, gint, i + 3);

        gint value1 = g_array_index(numbers, gint, value1_index);
        gint value2 = g_array_index(numbers, gint, value2_index);
        gint *target = &g_array_index(numbers, gint, target_index);

        if(command == 1) {
          // printf("target (idx=%d, value=%d), new value (%d + %d == %d)\n",
          //     target_index, *target, value1, value2, value1 + value2);
          *target = value1 + value2;
          // print_array(numbers);
        } else if(command == 2) {
          // printf("target (idx=%d, value=%d), new value (%d + %d == %d)\n",
          //     target_index, *target, value1, value2, value1 * value2);
          *target = value1 * value2;
          // print_array(numbers);
        } else {
          printf("Error: unknown command %d\n", command);
          exit(EXIT_FAILURE);
        }
    }

    return g_array_index(numbers, gint, 0);
}

gint main(gint argc, gchar *argv[]) {
    gint goal = -1;

    GOptionEntry entries [] = {
        { "goal", 'g', 0, G_OPTION_ARG_INT, &goal, "Desired end state", "G" },
        { NULL },
    };

    g_autoptr(GOptionContext) context = g_option_context_new("");
    g_option_context_add_main_entries(context, entries, NULL);

    g_autoptr(GError) error = NULL;

    if(!g_option_context_parse(context, &argc, &argv, &error)) {
        printf("Option parsing failed: %s", error->message);
        exit(EXIT_FAILURE);
    }

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

    if(goal == -1) {
      printf("%d\n", find_result(numbers, 12, 2));
      exit(EXIT_SUCCESS);
    } else {
        gint result = 0;

        for(gint limit = 0; result != goal; limit++) {
            for(gint x = limit, y = 0;
                result != goal && y <= limit && x >= 0;
                y++, x--
            ) {
                result = find_result(numbers, x, y);
                // printf("limit = %d, noun = %d, verb = %d, result=%d\n",
                //     limit, x, y, result);
                if(result == goal) {
                  printf("%d\n", x * 100 + y);
                  return EXIT_SUCCESS;
                }
            }
        }

        printf("Error: could not find result\n");
        return EXIT_FAILURE;
    }
}

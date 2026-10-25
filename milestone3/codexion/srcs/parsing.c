#include "../includes/parsing.h"

int argv_count_check(int argc)
{
    if (argc != 9)
    {
        printf("Invalid total number of arguments\n"
            "Example input:\n"
            "./codexion <number_of_coders> <time_to_burnout> <time_to_compile>"
            " <time_to_debug> <time_to_refactor> <number_of_compiles_required>"
            " <dongle_cooldown> <scheduler>");
        return (1);
    }
    else
        return (0);
}
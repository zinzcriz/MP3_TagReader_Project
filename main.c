#include "utils.h"

int main(int argc, char *argv[])
{
    MusicInfo mp3Info;
    if (argc < 3)
    {
        if (argv[1] == NULL)
        {
            printf("ERROR: Required Arguments are missing\n");
            printf("Type '--help' to get details\n");
        }
        else if (strcmp(argv[1], "--help") == 0)
        {
            call_help();
        }
        else if(argv[2]==NULL)
        {
            printf("ERROR: Required Arguments are missing\n");
            printf("Type '--help' to get details\n");
        }
    }
    else
    {
        if (check_operation_type(argv) == m_view)
        {
            if (read_and_validate_args(argv, &mp3Info) == m_success)
            {
            }
            else
            {
                printf("ERROR: Required Arguments are missing\n");
                printf("Type '--help' to get details\n");
            }
        }
    }
}

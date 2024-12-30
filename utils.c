#include "utils.h"

void call_help()
{
    printf("------------------HELP MENU------------------\n");
    printf("1. -v -> to view mp3 file contents\n");
    printf("2. -e -> to edit mp3 file contents\n");
    printf("\t2.1 -t -> to edit song title\n");
    printf("\t2.2 -a -> to edit artist name\n");
    printf("\t2.3 -A -> to edit album name\n");
    printf("\t2.4 -y -> to edit year\n");
    printf("\t2.5 -m -> to edit content\n");
    printf("\t2.6 -m -> to edit comment\n");
    printf("eg: ./a.out -v sample.mp3\n");
    printf("    ./a.out -e -t sample.mp3\n");
}

OperationType check_operation_type(char *argv[])
{
    if (strcmp(argv[1], "-v") == 0)
    {
        return m_view;
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        return m_edit;
    }
    else
    {
        return m_unsupported;
    }
}

Status read_and_validate_args(char *argv[], MusicInfo *mp3Info)
{
    if (strcmp(argv[1], "-v") == 0)
    {   
        if (strstr(argv[2], ".mp3") != NULL)
        {   
            mp3Info->mp3_file_name = argv[2];
            return m_success;
        }
        else
        {
            return m_failure;
        }
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        if (strcmp(argv[2], "-t") == 0 || strcmp(argv[2], "-a") == 0 || strcmp(argv[2], "-A") == 0 || strcmp(argv[2], "-m") == 0 || strcmp(argv[2], "-y") == 0 || strcmp(argv[2], "-c") == 0)
        {
            if (strstr(argv[3], ".mp3") != NULL)
            {
                mp3Info->mp3_file_name = argv[2];
            }
            else
            {
                return m_failure;
            }
        }
        else{
            return m_failure;
        }
    }
}

Status open_file(MusicInfo *mp3Info)
{
    mp3Info->fptr_mp3_file=fopen(mp3Info->mp3_file_name,"r+");
    if(mp3Info->fptr_mp3_file==NULL)
    {
        printf("Could not open %s file\n",mp3Info->mp3_file_name);
        return m_failure;
    }
    return m_success;
}
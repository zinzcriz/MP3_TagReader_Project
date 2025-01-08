#include "utils.h"

//Function to print help
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
    printf("\t2.6 -c -> to edit comment\n");
    printf("eg: ./a.out -v sample.mp3\n");
    printf("    ./a.out -e -t <changing text> sample.mp3\n");
}

//Function to check opertaion type(view/edit)
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

//Function to read and validate Arguments
/*Checks whether '-v' or '-e' is passed with arguments.If '-e' we check for what type of edit.Then we collect arguments
till secondlast argument as changing text and store it in a char array named temp*/

Status read_and_validate_args(int argc,char *argv[], MusicInfo *mp3Info)
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
            int i=3;
            while(strstr(argv[i], ".mp3") == NULL)
            {
               if(i==3)
               {
                strcpy(mp3Info->temp,argv[i]);
               }
               else{
               strcat(mp3Info->temp," ");
               strcat(mp3Info->temp,argv[i]);
               }
               i++;
               if(i==argc)
               {
                return m_failure;
               }
            }
            if(strstr(argv[3], ".mp3") != NULL)
            {
                return m_failure;
            }
            if (strstr(argv[i], ".mp3") != NULL)
            {
                mp3Info->mp3_file_name = argv[i];
                return m_success;
            }
            else
            {
                return m_failure;
            }
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

//Function to open files for viewing 
Status open_file_view(MusicInfo *mp3Info)
{
    mp3Info->fptr_mp3_file = fopen(mp3Info->mp3_file_name, "r");
    if (mp3Info->fptr_mp3_file == NULL)
    {
        printf("Could not open %s file\n", mp3Info->mp3_file_name);
        return m_failure;
    }
    return m_success;
}

//Function to check whether an mp3 file is ID3
//Its encoded in the first 3 bytes of mp3
//we also check for its version which is 3 encoded in subsequent two bytes
Status check_ID3(MusicInfo *mp3Info)
{
    char buffer[3];
    fread(buffer, 1, 3, mp3Info->fptr_mp3_file);
    if (strcmp(buffer, "ID3") == 0)
    {
        // printf("The version is ID3\n");
        int ver;
        fread(&ver, 1, 4, mp3Info->fptr_mp3_file);
        if (ver == 3)
        {
            // printf("The version is 03\n");
            fseek(mp3Info->fptr_mp3_file,0,SEEK_SET);
            return m_success;
        }
    }
    return m_failure;
}

/*In this function, we search for a tag which is passed as string argument.This function read mp3 file
char by char and compare it with the first letter of string.If it is true enters into a nested if
condition and checks remaining charactrs.If a tag is found in file it moves forward 3 bytes of file 
from current position.*/

Status find_tag(const char *data, FILE *fp)
{
    char alb;
    const char *d = data;
    int count = 1;
    int i=0;
    while (count!=0)
    {
        //fread(&alb,1,1,fp);
        alb=fgetc(fp);
        i++;
        if (alb == d[0])
        {
            //fread(&alb,1,1,fp);
            alb=fgetc(fp);
            if (alb == d[1])
            {
                //fread(&alb,1,1,fp);
                alb=fgetc(fp);
                if (alb == d[2])
                {

                    //fread(&alb,1,1,fp);
                    alb=fgetc(fp);
                    if (alb == d[3])
                    {
                        fseek(fp,ftell(fp)+3,SEEK_SET);
                        count = 0;
                    }
                }
            }
        }
        else if(alb == EOF && i>250)
        {
            count = 0;
            printf("%s not found\n",data);
            return m_failure;
        }
    }
    return m_success;
}

//Function for printing info

Status print_info(MusicInfo *mp3Info)
{
    printf("----------------------------------------------------------------------\n");
    printf("              MP3 TAG READER AND EDITOR FOR ID3v2        \n");
    printf("----------------------------------------------------------------------\n");
    printf("TITLE             :\t%s\n",mp3Info->mp3_file_title);
    printf("ARTIST            :\t%s\n",mp3Info->mp3_file_artist);
    printf("ALBUM             :\t%s\n",mp3Info->mp3_file_alb);
    printf("YEAR              :\t%s\n",mp3Info->mp3_file_year);
    printf("MUSIC             :\t%s\n",mp3Info->mp3_file_con);
    printf("COMMENT           :\t%s\n",mp3Info->mp3_file_comm);
    printf("----------------------------------------------------------------------\n");
}

//Function to open files for editing

Status open_file_edit(MusicInfo *mp3Info)
{
    mp3Info->fptr_mp3_file = fopen(mp3Info->mp3_file_name, "r+");
    if (mp3Info->fptr_mp3_file == NULL)
    {
        printf("Could not open %s file\n", mp3Info->mp3_file_name);
        return m_failure;
    }
    return m_success;
}
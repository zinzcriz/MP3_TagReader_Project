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
        else
        {
            return m_failure;
        }
    }
}

Status open_file(MusicInfo *mp3Info)
{
    mp3Info->fptr_mp3_file = fopen(mp3Info->mp3_file_name, "r+");
    if (mp3Info->fptr_mp3_file == NULL)
    {
        printf("Could not open %s file\n", mp3Info->mp3_file_name);
        return m_failure;
    }
    return m_success;
}

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

Status find_tag(const char *data, FILE *fp)
{
    // char alb[1];
    //printf("Hai3\n");
    char alb;
    const char *d = data;
    int count = 1;
    while (count!=0)
    {
        fread(&alb,1,1,fp);
        if (alb == d[0])
        {
            fread(&alb,1,1,fp);
            if (alb == d[1])
            {
                fread(&alb,1,1,fp);
                if (alb == d[2])
                {

                    fread(&alb,1,1,fp);
                    if (alb == d[3])
                    {

                        //fseek(fp,ftell(fp)-4,SEEK_SET);
                        /*char buff[4];
                        fread(buff,1,4,fp);
                        printf("%s\n",buff);*/
                        fseek(fp,ftell(fp)+3,SEEK_SET);
                        count = 0;
                    }
                }
            }
        }
        else if (alb == EOF)
        {
            count = 0;
            printf("Item not found\n");
            return m_failure;
        }
    }
    return m_success;
}

Status find_title(MusicInfo *mp3Info)
{
    if(find_tag("TIT2",mp3Info->fptr_mp3_file)==m_success)
    {
        int size;
        fread(&size,1,4,mp3Info->fptr_mp3_file);
        size=size-1;
        //printf("%d\n",size);
        char buffer[size];
        fread(buffer,1,size,mp3Info->fptr_mp3_file);
        buffer[size]='\0';
        //printf("%s\n",buffer);
        strcpy(mp3Info->mp3_file_title,buffer);
        fseek(mp3Info->fptr_mp3_file,0,SEEK_SET);
        return m_success;
    }
    else{
        strcpy(mp3Info->mp3_file_title,"Not found");
        //printf("Some error\n");
    }
}

Status find_artist(MusicInfo *mp3Info)
{
    if(find_tag("TPE1",mp3Info->fptr_mp3_file)==m_success)
    {
        int size;
        fread(&size,1,4,mp3Info->fptr_mp3_file);
        size=size-1;
        //printf("%d\n",size);
        char buffer[size];
        fread(buffer,1,size,mp3Info->fptr_mp3_file);
        buffer[size]='\0';
        //printf("%s\n",buffer);
        strcpy(mp3Info->mp3_file_artist,buffer);
        fseek(mp3Info->fptr_mp3_file,0,SEEK_SET);
        return m_success;
    }
    else
    {
        strcpy(mp3Info->mp3_file_artist,"Not found");
    }
}

Status find_alb(MusicInfo *mp3Info)
{
    if(find_tag("TALB",mp3Info->fptr_mp3_file)==m_success)
    {
        int size;
        fread(&size,1,4,mp3Info->fptr_mp3_file);
        size=size-1;
        //printf("%d\n",size);
        char buffer[size];
        fread(buffer,1,size,mp3Info->fptr_mp3_file);
        buffer[size]='\0';
        //printf("%s\n",buffer);
        strcpy(mp3Info->mp3_file_alb,buffer);
        fseek(mp3Info->fptr_mp3_file,0,SEEK_SET);
        return m_success;
    }
    else
    {
        strcpy(mp3Info->mp3_file_alb,"Not found");
    }
}

Status find_year(MusicInfo *mp3Info)
{
    if(find_tag("TYER",mp3Info->fptr_mp3_file)==m_success)
    {
        int size;
        fread(&size,1,4,mp3Info->fptr_mp3_file);
        size=size-1;
        //printf("%d\n",size);
        char buffer[size];
        fread(buffer,1,size,mp3Info->fptr_mp3_file);
        buffer[size]='\0';
        //printf("%s\n",buffer);
        strcpy(mp3Info->mp3_file_year,buffer);
        //printf("%s\n",mp3Info->mp3_file_year);
        fseek(mp3Info->fptr_mp3_file,0,SEEK_SET);
        return m_success;
    }
    else
    {
        strcpy(mp3Info->mp3_file_year,"NULL");
    }
}

Status find_con(MusicInfo *mp3Info)
{
    if(find_tag("TCON",mp3Info->fptr_mp3_file)==m_success)
    {
        int size;
        fread(&size,1,4,mp3Info->fptr_mp3_file);
        size=size-1;
        //printf("%d\n",size);
        char buffer[size];
        fread(buffer,1,size,mp3Info->fptr_mp3_file);
        buffer[size]='\0';
        //printf("%s\n",buffer);
        strcpy(mp3Info->mp3_file_con,buffer);
        fseek(mp3Info->fptr_mp3_file,0,SEEK_SET);
        return m_success;
    }
    else
    {
        strcpy(mp3Info->mp3_file_con,"Not found");
    }
}

Status find_comm(MusicInfo *mp3Info)
{
    if(find_tag("COMM",mp3Info->fptr_mp3_file)==m_success)
    {
        int size;
        fread(&size,1,4,mp3Info->fptr_mp3_file);
        size=size-1;
        //printf("%d\n",size);
        char buffer[size];
        fread(buffer,1,size,mp3Info->fptr_mp3_file);
        buffer[size]='\0';
        //printf("%s\n",buffer);
        strcpy(mp3Info->mp3_file_comm,buffer);
        fseek(mp3Info->fptr_mp3_file,0,SEEK_SET);
        return m_success;
    }
    else
    {
        strcpy(mp3Info->mp3_file_comm,"Not found");
    }
}

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
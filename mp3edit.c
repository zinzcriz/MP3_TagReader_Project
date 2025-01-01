#include "utils.h"
int flag = 0;
Status call_mp3edit(char *argv[], MusicInfo *mp3Info)
{
    if (open_file_edit(mp3Info) == m_success)
    {
        if (check_ID3(mp3Info) == m_success)
        {
            if (strcmp(argv[2], "-t") == 0)
            {
                if(edit_title(mp3Info)==m_success)
                {
                    //print_info(mp3Info);
                    flag=1;
                }
            }
            else if(strcmp(argv[2], "-a") == 0)
            {
                if(edit_artist(mp3Info)==m_success)
                {
                    flag=1;
                }
            }
        }
    }
}

Status edit_artist(MusicInfo *mp3Info)
{
    if (find_tag("TPE1", mp3Info->fptr_mp3_file) == m_success)
    {
        int size;
        fread(&size, 1, 4, mp3Info->fptr_mp3_file);
        size = size - 1;
        int new_size = strlen(mp3Info->temp);
        if (new_size > size)
        {
            printf("Changing text size is greater than available space\n");
            return m_failure;
        }
        else
        {
            // printf("%d\n",size);
            char buffer[size];
            strcpy(buffer, mp3Info->temp);
            //buffer[size] = '\0';
            if(fwrite(buffer, 1, size, mp3Info->fptr_mp3_file)==0)
            {
                printf("Error in changing Artist Name\n");
                return m_failure;
            }
            strcpy(mp3Info->mp3_file_artist,buffer);
            // printf("%s\n",buffer);
            fseek(mp3Info->fptr_mp3_file, 0, SEEK_SET);
            printf("-------------------------------------SELECTED EDIT DETAILS-------------------------------------\n");
            printf("\n");
            printf("-----------SELECTED EDIT OPTION-----------\n");
            printf("----------CHANGE THE ARTIST NAME-----------\n");
            printf("ARTIST    : %s\n",mp3Info->mp3_file_artist);
            printf("-----------ARTIST NAME CHANGED SUCCESSFULLY------\n");

            return m_success;
        }
    }
    else
    {
        //strcpy(mp3Info->mp3_file_title, "Not found");
        return m_failure;
        // printf("Some error\n");
    }
}

Status edit_title(MusicInfo *mp3Info)
{
    if (find_tag("TIT2", mp3Info->fptr_mp3_file) == m_success)
    {
        int size;
        fread(&size, 1, 4, mp3Info->fptr_mp3_file);
        size = size - 1;
        int new_size = strlen(mp3Info->temp);
        if (new_size > size)
        {
            printf("Changing text size is greater than available space\n");
            return m_failure;
        }
        else
        {
            // printf("%d\n",size);
            char buffer[size];
            strcpy(buffer, mp3Info->temp);
            //buffer[size] = '\0';
            if(fwrite(buffer, 1, size, mp3Info->fptr_mp3_file)==0)
            {
                printf("Error in changing Title\n");
                return m_failure;
            }
            strcpy(mp3Info->mp3_file_title,buffer);
            // printf("%s\n",buffer);
            fseek(mp3Info->fptr_mp3_file, 0, SEEK_SET);
            printf("-------------------------------------SELECTED EDIT DETAILS-------------------------------------\n");
            printf("\n");
            printf("-----------SELECTED EDIT OPTION-----------\n");
            printf("-----------CHANGE THE TITLE-----------\n");
            printf("TITLE    : %s\n",mp3Info->mp3_file_title);
            printf("-----------TITLE CHANGED SUCCESSFULLY------\n");

            return m_success;
        }
    }
    else
    {
        //strcpy(mp3Info->mp3_file_title, "Not found");
        return m_failure;
        // printf("Some error\n");
    }
}


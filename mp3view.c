#include "utils.h"

Status call_MP3view(MusicInfo *mp3Info)
{
    if(open_file_view(mp3Info)==m_success)
    {
        if(check_ID3(mp3Info)==m_success)
        {   
            //printf("Hai1\n");
            find_title(mp3Info);
            //printf("%s\n",mp3Info->mp3_file_title);
            find_artist(mp3Info);
            find_alb(mp3Info);
            find_year(mp3Info);
            find_con(mp3Info);
            find_comm(mp3Info);
            fclose(mp3Info->fptr_mp3_file);
            return m_success;
        }
    }
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
        //printf("Size:%d\n",size);
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



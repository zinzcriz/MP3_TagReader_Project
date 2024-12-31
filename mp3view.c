#include "utils.h"

Status call_MP3view(MusicInfo *mp3Info)
{
    if(open_file(mp3Info)==m_success)
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
            return m_success;
        }
    }
}
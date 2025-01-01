#ifndef UTILS_H
#define UTILS_H
#include "types.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct _MusicInfo
{  
    char *mp3_file_name;
    FILE *fptr_mp3_file;
    
    char temp[100];
    char mp3_file_title[50];
    char mp3_file_artist[50];
    char mp3_file_alb[50];
    char mp3_file_comm[50];
    char mp3_file_con[50];
    char mp3_file_year[4];
    
}MusicInfo;

void call_help();
OperationType check_operation_type(char *argv[]);
Status read_and_validate_args(int argc,char *argv[], MusicInfo *mp3Info);
Status call_MP3view(MusicInfo *mp3Info);
Status open_file_view(MusicInfo *mp3Info);
Status check_ID3(MusicInfo *mp3Info);
Status find_tag(const char *data, FILE *fp);
Status find_title(MusicInfo *mp3Info);
Status find_artist(MusicInfo *mp3Info);
Status find_alb(MusicInfo *mp3Info);
Status find_year(MusicInfo *mp3Info);
Status find_con(MusicInfo *mp3Info);
Status find_comm(MusicInfo *mp3Info);
Status print_info(MusicInfo *mp3Info);


Status call_mp3edit(char *argv[], MusicInfo *mp3Info);
Status open_file_edit(MusicInfo *mp3Info);
Status edit_title(MusicInfo *mp3Info);
Status edit_artist(MusicInfo *mp3Info);


#endif
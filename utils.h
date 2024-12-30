#ifndef UTILS_H
#define UTILS_H
#include "types.h"
#include<stdio.h>
#include<string.h>

typedef struct _MusicInfo
{
    char *mp3_file_name;
}MusicInfo;

void call_help();
OperationType check_operation_type(char *argv[]);
Status read_and_validate_args(char *argv[],MusicInfo *mp3Info);


#endif
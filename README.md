# MP3_TagReader_Project

C program to read information tags in an MP3 file.This program is only compatible to read the tag information of mp3 files of standard ID3V2.3.

# How to use:

- clone this repo

```
git clone https://github.com/zinzcriz/MP3_TagReader_Project.git
```
- Copy and paste the mp3 file from 'Music Files' folder. Then run following codes:

     1. To view tag information in an mp3 file

     ```
     ./output -v <MP3FileName>
     ```
     2. To edit title tag information
     ```
     ./output -e -t <MP3FileName>
     ```
     3. To edit artist name
     ```
     ./output -e -a <MP3FileName>
     ```
     4. To edit album name
     ```
     ./output -e -a <MP3FileName>
     ```
     5. To edit year
     ```
     ./output -e -y <MP3FileName>
     ```
     6. To edit music type
     ```
     ./output -e -m <MP3FileName>
     ```
     7. To edit comment
     ```
     ./output -e -c <MP3FileName>
     ```

This program only works with mp3 files with version ID3V3.2.


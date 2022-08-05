#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <stdint.h>
#include <assert.h>

#define ERROR_LOG(msg) fprintf(stderr, msg, strerror(errno));

#define HEADER_SIZE 8

void usage(int, const char*);
void open_file(FILE**, const char*);
void show_bytes(uint8_t*, size_t);
void is_valid_png_file(uint8_t*, size_t);

void read_header(FILE*, uint8_t*, size_t);

void read_chunk(FILE*);


int main(int argc, char const *argv[])
{
    
    usage(argc, argv[0]);

    FILE *f = NULL;
    open_file(&f, argv[1]);
    
    
    
    uint8_t buff[HEADER_SIZE];
    
    read_header(f, buff, sizeof(buff));
    printf("Header section:\n\n");
    show_bytes(buff, HEADER_SIZE);
    
    read_chunk(f);

    fclose(f);
    
    //~~~~~~~~~END~~~~~~~~~~~~~~~~~
    printf("\nEnter any key...");
    getchar();
    return 0;
}

void usage(int count, const char* prog_name){
    if(count < 2){
        fprintf(stderr, "Usage: %s <input.png>\n", prog_name);
        exit(EXIT_FAILURE);
    }
}

void open_file(FILE** f, const char* path){
    *f = fopen(path, "rb");
    if(*f == NULL){
        ERROR_LOG("ERROR: Cannot open file. Reason: %s")
        exit(EXIT_FAILURE);
    }
}

void show_bytes(uint8_t* buff, size_t len){
    for (size_t i = 0; i < len; i++)
    {
       printf("%x ", buff[i]);
    }
    
}

void is_valid_png_file(uint8_t* buff, size_t len){
    const uint8_t png_sig[HEADER_SIZE] = {137, 80, 78, 71, 13, 10, 26, 10};
    
    if(memcmp(buff, png_sig, len) != 0){
            fprintf(stderr, "ERROR: Unsupported type of file");
            exit(EXIT_FAILURE);
    }
    
    
}

void read_header(FILE *f, uint8_t *buffer, size_t len){

    fread(buffer, len, 1, f);

    if(ferror(f)){
        ERROR_LOG("ERROR: Some error caused: %s")
        exit(EXIT_FAILURE);
    }else if (feof(f)){
        ERROR_LOG("ERROR: Invalid header of png file: %s")
        exit(EXIT_FAILURE);
    }
    is_valid_png_file(buffer, len);
    
}

void read_chunk(FILE*f){
    uint8_t chunck_length[4];
    fread(chunck_length, 4, 1, f);
    int buff = (int) chunck_length;
    printf("\n\nLenght of chunk:\n\n%d\n", buff);
    //TODO: read of chunks

}

#include "../include/fileutil.h"

void bytebuffer_write_to_file(const char * fp, bytebuffer * buf) {
    FILE * f = fopen(fp, "wb+");

    if(f == NULL) {
        printf("Cannot open file %s\n", fp);
        exit(1);
    }

    fwrite(buf->data, sizeof(uint8_t), buf->ptr, f);

    fclose(f);
}

char * readfile(const char * fp) {
    FILE * f = fopen(fp, "rb");
    if(f == NULL) {
        printf("Cannot open file %s\n", fp);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char * buf = (char*)malloc(len+1);

    fread(buf, 1, len, f);
    fclose(f);
    
    buf[len] = 0;
    return buf;
}

bytebuffer * readbuf_from_file(const char * fp) {
    FILE * f = fopen(fp, "rb+");

    if(f == NULL) {
        printf("Cannot open file %s\n", fp);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    bytebuffer * buf = bytebuffer_create(ftell(f));
    fseek(f, 0, SEEK_SET);

    for(int i = 0; i < buf->size; i++) {
        bytebuffer_push(buf, fgetc(f));
    }
    fclose(f);

    return buf;
}
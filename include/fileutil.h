#ifndef VAPOR_VM_FILEUTIL_H
#define VAPOR_VM_FILEUTIL_H

#include "bytebuffer.h"
#include "stdio.h"

void bytebuffer_write_to_file(const char * fp, bytebuffer * buf);

char * readfile(const char * fp);

bytebuffer * readbuf_from_file(const char * fp);

#endif // VAPOR_VM_FILEUTIL_H
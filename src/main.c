#include "../include/lexer.h"
#include "../include/compiler.h"
#include "../include/fileutil.h"
#include "../include/runtime.h"

int main(int argc, char ** argv) {
    if(argc < 2) {
        printf("Correct use: %s (compile/run) (file path)\n", argv[0]);
        return 0;
    }
    if(strcmp(argv[1], "compile") == 0) {
        const char * src = readfile(argv[2]);
        lexer * lex = lexer_create(src);
        lexer_tokenize(lex);

        bytebuffer * buf = compile(lex->toklist);
        
        if(argc > 3) {
            bytebuffer_write_to_file(argv[3], buf);
        } else {
            char * default_path = "./a.out";
            bytebuffer_write_to_file(default_path, buf);
        }
        return 0;
    } else if(strcmp(argv[1], "run") == 0) {
        bytebuffer * buf = readbuf_from_file(argv[2]);
        
        vmstate * state = vmstate_create(0xffff); // may be variable

        load(state, buf, 0);
        
        execute(state);

        runtime_print_stack(state, 32); // may be variable on debug
        return 0;
    }
}
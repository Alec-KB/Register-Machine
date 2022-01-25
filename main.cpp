#include "RegisterMachine.h"

int main(int argc, char* argv[]){
    if (argc != 3)
    {
        printf("Format is RegisterMachine <program file> <register file>");
    }
    

    RegisterMachine* r = new RegisterMachine();
    Program* p = new Program();

    p->parseProgram(argv[1]);
    r->setRegisters(argv[2]);
    r->inputProgram(p);
    r->execute();
    printf("Result is %d", r->returnResult());
    return 0;
}
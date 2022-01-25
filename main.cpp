#include "RegisterMachine.h"

int main(){
    RegisterMachine* r = new RegisterMachine();
    Program* p = new Program();
    p->addInstruction("0", new Instruction(1,false,"1","2"));
    p->addInstruction("1", new Instruction(0,true,"0"));
    p->addInstruction("2", new Instruction(2,false,"3","4"));
    p->addInstruction("3", new Instruction(0,true,"2"));
    p->addInstruction("4", new Instruction(-1,true,"0"));
    p->setStartLabel("0");
    r->inputProgram(p);
    r->setRegister(1,1);
    r->setRegister(2,2);
    r->execute();
    printf("%d", r->returnResult());
    return 0;
}
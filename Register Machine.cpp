#include <Register Machine.h>

int RegisterMachine::returnResult(){
    return registers[0];
}

void RegisterMachine::printConfiguration(){
    printf("(%s ", program->getLabel());
    for(int reg : registers){
        printf(",%d ", reg);
    }
    printf(")\n");
}

void RegisterMachine::inputProgram(Program* inputProgram){
    program = inputProgram;
}

void RegisterMachine::resetRegisters(){
    for(int i = 0; i< regLen; i++){
        registers[i] = 0;
    }
}

void RegisterMachine::setRegister(unsigned int R, unsigned int val){
    registers[R] = val;
}

int RegisterMachine::execute(){
    int a;
    while(!(a = program->executeInstruction(registers))){
        if(a==1){
            perror("Execution Failed!");
        }
    }
    return 0;

}
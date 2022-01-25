#include <Register Machine.h>
#include <stdexcept>

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


std::string Program::getLabel(){
    return currentInstruction;
}

int Program::addInstruction(std::string label, Instruction* instruction){
    if(instructions.count(label) == 0){
        instructions[label] = instruction;
        return 0;
    } else{
        printf("Instruction %s already exists!", label);
        return 1;
    }
}

void Program::setStartLabel(std::string label){
    currentInstruction = label;
}

int Program::executeInstruction(unsigned int* registers){
    if(currentInstruction.empty()){
        perror("No starting instruction set!");
        return 1;
    } else{
        try{
            currentInstruction = instructions.at(currentInstruction)->execute(registers);
        } catch(std::out_of_range){
            printf("Instruction %s does not exist", currentInstruction);
            return 2;
        }
    }
    return 0;
}
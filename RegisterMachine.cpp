#include "RegisterMachine.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <ctype.h>


// REGISTER MACHINE

int RegisterMachine::returnResult(){
    return registers[0];
}

void RegisterMachine::printConfiguration(){
    printf("('%s'", program->getLabel().c_str());
    for(int reg : registers){
        printf(", %d", reg);
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

int RegisterMachine::setRegisters(std::string filename){
    std::fstream file(filename);

    if(!file.is_open()){
        printf("Couldn't find register file %s", filename.c_str());
        return 1;
    } 

    std::string token;
    char c;
    int i = 0;
    // split input by whitespace and commas
    while(!file.eof()){
        file.get(c);
        if(isspace(c) || c == ',' || file.eof()){// if c is a whitespace or comma, we've got a full "word" in token, so push to output
            if(!token.empty()){
                if(i>= regLen){
                    printf("Too many states in Register File");
                    return 2;
                }
                registers[i++] = stoi(token);
                token.clear();
            }
        } else{
            token.push_back(c);
        }
    }

    if(!token.empty()){
        if(i>= regLen){
            printf("Too many states in Register File");
            return 2;
        }
        registers[i++] = stoi(token);
        token.clear();
    }   
    return 0;
    
}

int RegisterMachine::execute(){
    int a;
    printConfiguration();
    while(!(a = program->executeInstruction(registers))){
        if(a==1){
            printf("Execution Failed!");
            return 1;
        }
        printConfiguration();

    }
    return 0;
}

RegisterMachine::RegisterMachine(){
    
}

// PROGRAM
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
        } catch(...){
            if(currentInstruction == "Halt"){
                return 3;
            } else{
                printf("Instruction %s does not exist", currentInstruction.c_str());
                return 2;
            }
        }
    }
    return 0;
}

Program::Program(){

}

int Program::parseProgram(std::string filename){
    std::list<std::string> tokens;

    if(tokenise(filename, &tokens)){
        return 1;
    }

    std::string label;
    int R;
    bool add;
    std::string label1;
    std::string label2;

    // iterate over tokens
    std::string cToken;
    while(!tokens.empty()){
        cToken = tokens.front();
        tokens.pop_front();
        if(cToken.front() == 'L'){
            label = cToken;
            if(currentInstruction.empty()){
                setStartLabel(cToken);
            }
        } else{
            printf("Incorrect Label Format"); // Line number?
            return 2;
        }

        cToken = tokens.front();
        tokens.pop_front();
        if(cToken != ":"){
            printf("Incorrect Format, Missing ':' ");
            return 2;
        }

        cToken = tokens.front();
        tokens.pop_front();
        if(cToken.front() == 'R' && (cToken.back() != '+' || cToken.back() != '-')){
            R = stoi(cToken.substr(1,cToken.length()-2));
            add = cToken.back() == '+' ? true : false;
        } else if(cToken.front() == 'H'){
                instructions[label] = new Instruction(-1 , true, "Halt");
                continue;
        }else{
            printf("Incorrect Register Format");
            return 2;
        }

        cToken = tokens.front();
        tokens.pop_front();
        if(cToken != "->"){
            printf("Incorrect Format, Missing '->' ");
            return 2;
        }

        cToken = tokens.front();
        tokens.pop_front();
        if(cToken.front()=='L'){
            label1 = cToken;
        } else{
            printf("Incorrect Jump Label 1");
            return 2;
        }

        if(add){
            instructions[label] = new Instruction(R,add,label1);
            continue;
        }

        cToken = tokens.front();
        tokens.pop_front();

        if(cToken != ","){
            printf("Incorrect Format, missing ','");
            return 2;
        }

        cToken = tokens.front();
        tokens.pop_front();
        if(cToken.front()=='L'){
            label2 = cToken;
        } else{
            printf("Incorrect Jump Label 2");
            return 2;
        }

        instructions[label] = new Instruction(R,add,label1,label2);
    }

    return 0;
}

const int Program::tokenise(std::string filename, std::list<std::string>* output){
    std::ifstream file(filename);
    if(!file.is_open()){
        printf("Couldn't open file '%s'", filename);
        return 1;
    }
    std::string token;
    char c;
    // split input by whitespace
    while(!file.eof()){
        file.get(c);
        if(isspace(c) || file.eof()){// if c is whitespace, we've got a full "word" in token, so push to output
            if(!token.empty()){
                output->push_back(token);
                token.clear();
            }
        } else{
            token.push_back(c);
        }

    }
    return 0;
}


// INSTRUCTION
Instruction::Instruction(unsigned int iR, bool iadd, std::string ilabel1){
    R = iR;
    add = iadd;
    label1 = ilabel1;
}

Instruction::Instruction(unsigned int iR, bool iadd, std::string ilabel1, std::string ilabel2){
    R = iR;
    add = iadd;
    label1 = ilabel1;
    label2 = ilabel2;
}

std::string Instruction::execute(unsigned int* registers){
    if(R<0){
        return "Halt"; // This cannot be a label name since the parser only accepts labels starting with 'L'
                       // Therefore this will terminate the execution
    }
    if(add){
        registers[R]++;
        return label1;
    } else{
        if(registers[R] == 0){
            return label2;
        } else{
            registers[R]--;
            return label1;
        }
    }
}
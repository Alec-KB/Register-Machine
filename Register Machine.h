#include <string>
#include <map>
#define regLen 10

class RegisterMachine{
    Program* program;

    unsigned int registers[regLen] = {};

    public:
    void inputProgram(Program* inputProgram);
    void resetRegisters();
    void setRegister(unsigned int R, unsigned int val);
    int execute();
    int returnResult();
    void printConfiguration();
    RegisterMachine();
};

class Program{
    std::map<std::string, Instruction*> instructions = {};
    std::string currentInstruction;

    public:
    std::string getLabel();
    int addInstruction(std::string Label, Instruction* instruction);
    void setStartLabel(std::string);
    int executeInstruction(unsigned int* registers);
    Program();

};

class Instruction{
    std::string label; 
    int R; // if <0, a halt instruction
    bool add; // if true add instruction, if false subtract

    public:
    Instruction(unsigned int R, bool add, std::string label1); // redundancy in add?
    Instruction(unsigned int R, bool add, std::string label1, std::string label2); // redundancy in add?
    std::string execute(unsigned int* registers); // acts on the registers then returns label of next instruction
};
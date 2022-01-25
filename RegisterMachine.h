#include <string>
#include <map>
#include <list>
#define regLen 10

class Instruction{
    std::string label; 
    int R; // if <0, a halt instruction
    bool add; // if true add instruction, if false subtract
    std::string label1;
    std::string label2;

    public:
    Instruction(unsigned int R, bool add, std::string label1); // redundancy in add?
    Instruction(unsigned int R, bool add, std::string label1, std::string label2); // redundancy in add?
    std::string execute(unsigned int* registers); // acts on the registers then returns label of next instruction
};

class Program{
    std::map<std::string, Instruction*> instructions = {};
    std::string currentInstruction;
    static const int tokenise(std::string filename, std::list<std::string>* output);

    public:
    std::string getLabel();
    int addInstruction(std::string Label, Instruction* instruction);
    void setStartLabel(std::string);
    int executeInstruction(unsigned int* registers);
    int parseProgram(std::string filename);

    Program();

};

class RegisterMachine{
    Program* program;

    unsigned int registers[regLen] = {};

    public:
    void inputProgram(Program* inputProgram);
    void resetRegisters();
    int setRegisters(std::string filename);
    int execute();
    int returnResult();
    void printConfiguration();
    RegisterMachine();
};



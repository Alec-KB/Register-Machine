# Register-Machine

A Register Machine implementation I coded for my Computation Theory course

# Program
The machine requires a program (obviously!), which can be read in from a file.
To produce a file that can be read in, create a plaintext file containing lines of the form:

Li : Rc- -> Lj , Lk (Subtraction instruction)\n
Li : Rc+ -> Lj      (Addition instruction)
Li : H              (Halting Instruction)

where: 
i, j, and k, are labels of some form (can be alphanumeric, just no whitespace)
c is an integer

Note that the first line will be the first instruction executed, after that it is up to your program flow

For Subtraction, if Rc is 0 nothing happens, and machine jumps to instruction Lk, otherwise Rc is decremented and machine jumps to instruction Lj
For Addition, Rc is incremented and machine jumps to instruction Lj
For Halt, machine terminates.

Example:

L0 : R1- -> L1 , L2
L1 : R0+ -> L0
L2 : R2- -> L3 , L4
L3 : R0+ -> L2
L4 : H

This program will add the contents of R1 and R2, leaving them in R0
(By convention R0 is the "output" register)

# Registers
The machine also requires an initial state for the registers, this can be given in the form of another file.
This file should contain a series of 10 non-negative integers, separated by commas and/or spaces
The first should really be 0, since this is the output register. However this is not a requirement if you want to get funky.

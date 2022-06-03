The program successfully scans and parses kitty code.
There is a weeder that gives warnings for dead code and mismatching function id's.
It successfully type checks the code.
There is a pretty printer that can print back the code from an abstract syntax tree.
There is code generation that generates assembly code with temporaries instead of allocated registers. 
The register allocation has not been implemented so the code generation was not as thoroughly tested has we would have wanted.
There is a parser that parses the assembly code and liveness analysis that can not handle all assembly generations as it is.
The code generation was tested for creating records and assigning values, 
which could be succesfully written. 
It was also tested for calling a function and writing it's return values.

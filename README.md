# Brainfuck Interpreter

Brainfuck is an esoteric programming language containing only 8 simple commands, each of them being one single character:

< > + - \[ \] . ,

As well as a data array with a movable pointer, and instruction pointer.

This is why it's a good choice for amateur interpreter or compiler programmers to try as a challenge, and the reason why I decided to give it a try.

## Compiling

In order to compile the program just run `make` in root directory.

Compiled file will be located at `build/main`

## Running program

In order to run the program, just run `build/main <source.bf>`, where `source.bf` is any Brainfuck sourcecode file (extension is irrelevant). 

If no file is provided, the program will run the default `bf_src/helloworld.bf` included in this repository.

### DISCLAIMER:

I do not own the files `fib.bf`, `helloworld.bf`, `life.bf` and `mandelbrot.bf`. They are just brainfuck sample source codes I found on the internet for testing purposes. If the creator of any of these source codes wants me to credit them or remove these files, please contact me.

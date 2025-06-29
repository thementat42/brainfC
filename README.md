# === Brainf**C Interpreter ===

A small brainf*** interpreter written in C.

## === BrainF*** syntax ===

Brainf*** gives the programmer an array of thirty thousand (30 000) 8-bit unsigned integers (the "tape"), and a pointer indicating which cell in the tape is currently selected.

Brainf*** has 6 operations:

- `>`: Moves the cell pointer right by one cell
- `<`: Moves the cell pointer left by one cell
- `+`: Increments the current cell
- `-`: Decrements the current cell
- `.`: Prints the value in current cell to stdout (as an ASCII character)
- `,`:  Reads in an ASCII character from stdin and places it in the current cell (as an 8-bit unsigned integer)

The `>` and `<` operators will wrap around the ends of the tape.

The `+` and `-` will wrap around the unsigned 8-bit int range (0-255)

### === Brainf*** Loops ===

Loops in Brainf*** are sequences of statements enclosed by square brackets (`[]`):

- A loop begins with an opening square bracket (`[`) and ends with a closing square bracket (`]`)
- When the program encounters a `[`, it checks the value in the current cell. If it is 0, it skips ahead to the corresponding closing bracket. Otherwise, the loop runs again. The same happens when it encounters a `]`, with the program jumping back to the corresponding `[` if the current cell is nonzero

Loops can also contain loops

Any other character besides the 8 mentioned above are ignored and can act as comments

## === Files ===

- [`stack.h`](/stack.h): Defines a `stack` struct, used to handle loops
- [`stack.c`](/stack.c): Implements methods for the `stack` struct
- [`brainf.c`](/brainf.c): The main interpreter file

## === Building ===

This project uses CMake as its build system. To build it, run:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

This will produce a `brainfC` executable in the `build/bin` directory.

## === Using the interpreter ===

After [building](#-building-) the interpreter, you can run it using

```bash
./brainfC [code]
```

If a command line argument ends in `.bf`, `.b` or `.brainfuck`, it will be treated as a file. Otherwise, it will be treated as raw code.

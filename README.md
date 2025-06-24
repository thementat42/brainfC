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

### === Brainf*** Loops ===

Loops in Brainf*** are sequences in statements enclosed by square brackets (`[]`):

- A loop begins with an opening square bracket (`[`) and ends with a closing square bracket (`]`)
- When the program encounters a `[`, it checks the value in the current cell. If it is 0, it skips ahead to the corresponding closing bracket. Otherwise, the loop runs again. The same happens when it encounters a `]`, with the program jumping back to the corresponding `[` if the current cell is nonzero

Any other character besides the 8 mentioned above are ignored.

## === Files ===

- [`stack.h`](/stack.h): Defines a `stack` struct, used to handle loops
- [`stack.c`](/stack.c): Implements methods for the `stack` struct
- [`brainfuck.c`](/brainfuck.c): The main interpreter file

## === Building ===

This project uses CMake as its build system. To build it, run:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

This will produce a `brainfuck` executable in the `build/bin` directory.

## === Using the interpreter ===

After [building](#-building-) the interpreter, you can run it using

```bash
./brainfuck [code]
```

Each command line argument will be treated as a separate piece of brainfuck code.

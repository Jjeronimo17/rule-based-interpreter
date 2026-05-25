# Rule-Based Language with Execution and Analysis

An interpreter for a rule-based language, built from scratch in C++ for the
Formal Languages and Compilers course. The system performs the full pipeline of
a compiler/interpreter: lexical analysis, syntactic analysis (LL(1) recursive
descent), Abstract Syntax Tree (AST) construction, execution by fixed-point
evaluation, and a static analysis module.

## Authors

- <Jeronimo_Jaramillo_Agudelo>
- <Sebastian_Rodriguez_Bayona>

## Environment

- **Operating system:** <Windows 11>
- **Language:** C++ (standard C++17)
- **Compiler:** <g++ 13.2>
- **IDE / build tool:** <CLion with CMake 3.x>

## Project Structure

The project follows a modular design, with each stage of the pipeline in its
own component:

- `Lexer.h` — lexical analysis: turns the source text into tokens.
- `Parser.h` — LL(1) recursive-descent parser: validates syntax and builds the AST.
- `Condicion.h`, `Hecho.h`, `Comparacion.h`, `And.h` — AST condition nodes (polymorphic hierarchy).
- `NodoRule.h`, `Programa.h` — structural AST nodes (rule and program root).
- `Interprete.h` — fixed-point interpreter that executes the program.
- `Entrada.h` — input handling: separates rules from the initial state and loads it.
- `Analisis.h` — static analysis: detects conflicts, redundancies and inactive rules.
- `main.cpp` — connects the full pipeline.

## Grammar

The grammar from the assignment is **not LL(1)** as given, due to left recursion
in `Cond` and a common prefix in `Atom`. It was transformed before implementing
the parser.

**Original grammar:**
Program  -> RuleList
RuleList -> Rule RuleList | e
Rule     -> rule id : if Cond then Action
Cond     -> Cond AND Cond | Atom
Atom     -> id RelOp value | id
RelOp    -> > | < | =
Action   -> id

**LL(1) grammar (implemented):**
Program  -> RuleList
RuleList -> Rule RuleList | e
Rule     -> rule id : if Cond then Action
Cond     -> Atom Cond'
Cond'    -> AND Atom Cond' | e        (left-recursion elimination)
Atom     -> id Atom'
Atom'    -> RelOp value | e           (left factoring)
RelOp    -> > | < | =
Action   -> id
( `e` = epsilon / empty string )

Each non-terminal corresponds to a `parseX()` method in the parser.

## Input Format

The input contains the rules and, optionally, an initial state separated by a
line containing `State:`.

rule r1:
if temp > 30 then alert
State:
temp = 35

- Rules follow the grammar above.
- The initial state has variable assignments (`id = integer`) and active facts (`id`).
- Extra whitespace and blank lines are ignored.

## Build and Run

### Using g++ (terminal)

```bash
g++ -std=c++17 main.cpp -o programa
./programa < caso1.txt
```

Or type the input manually and end with `Ctrl+D` (Linux/Mac) or `Ctrl+Z` then
Enter (Windows).

### Using CLion

Open the project, build it, and run. To feed an input file, set
**Run > Edit Configurations > Redirect input from** to your test file.

## Output

- The activated facts, one per line, sorted alphabetically.
- If no facts are activated, the output is exactly `(no output)`.
- Static analysis messages (conflicts, redundancies, inactive rules) are printed
  after the execution output.

## Notes on Static Analysis

The "potentially inactive rule" detection considers a rule inactive when its
condition can never become true: a comparison that is false in the initial state
(since rules never modify variables), or a fact that is neither in the initial
state nor produced by any rule. The assignment does not fully specify this
criterion, so this interpretation was chosen and is consistent across all rules.

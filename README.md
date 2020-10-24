# Sudoku solver

Just a simple project to dive into (modern) C++..

- Simple backtracking algorithm
- Uses bitwise encoding of the rows and columns
- Solves the [world's hardest sudoku](https://www.telegraph.co.uk/news/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html) in 0.0005s and the [hardest known for bruce force algorithms](https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#/media/File:Sudoku_puzzle_hard_for_brute_force.svg) in 1.32s on my machine.
- **Caution** There's no input checking at the moment.  

## How does the bitwise encoding work?

```
binrows[k] = (0 0 0 ... 0 1 0 ... 0)_2 if the number i is already set in row k
bincols[k] = (0 0 0 ... 0 1 0 ... 0)_2 if the number i is already set in column k
binboxs[k] = (0 0 0 ... 0 1 0 ... 0)_2 if the number i is already set in box k
binindx[k] = (0 0 0 ... 0 1 0 ... 0)_2 if the cell (k, i) is set, i.e. not empty
                          i            
```
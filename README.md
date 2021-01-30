# Sudoku solver

Just a simple project to dive into (modern) C++..

- Simple backtracking algorithm
- Uses bitwise encoding of the rows and columns
- Solves the [world's hardest sudoku](https://www.telegraph.co.uk/news/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html) in 0.0005s and the [hardest known for bruce force algorithms](https://en.wikipedia.org/wiki/Sudoku_solving_algorithms#/media/File:Sudoku_puzzle_hard_for_brute_force.svg) in 1.32s on my machine.
- **Caution** There's no input checking at the moment.  

To do:

- Tests
- Support for 16x16 and 25x25 sudokus
- Use `std::array` instead of `std::vector`

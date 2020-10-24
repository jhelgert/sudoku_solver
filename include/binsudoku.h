#ifndef BINSUDOKU_H
#define BINSUDOKU_H

#include <vector>
#include <chrono>
#include <string>

class Sudoku {
    int gridsize;
    std::vector<std::uint32_t> puzzle;
    std::vector<std::uint32_t> binrows;
    std::vector<std::uint32_t> bincols;
    std::vector<std::uint32_t> binboxes;
    std::vector<std::uint32_t> binindx;
    std::chrono::duration<double> runtime;

  public:
    // Constructors
    Sudoku(std::vector<uint32_t> S);
    Sudoku(std::string str);

    // Destructor
    ~Sudoku() = default;

    // Member functions
    bool numValid(size_t num, size_t row, size_t col);

    void setNum(size_t num, size_t row, size_t col);

    void delNum(size_t num, size_t row, size_t col);

    bool solve(bool timing=false);

    bool solver();

    void print();

    double getRuntime();

  private:
    std::pair<int, int> findEmptyCell();
    void encodeToBinary();
};

#endif /* BINSUDOKU_H */
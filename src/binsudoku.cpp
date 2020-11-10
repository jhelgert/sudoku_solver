#include "binsudoku.h"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

/*
Use a very fast specific machine instruction inside find_empty_cell()
*/ 
#if defined(__GNUC__) || defined(__clang__)
    inline int32_t bit_scan_forward(int x){
        return __builtin_ffs(x) - 1;
    }
#elif defined(_MSC_VER)
    #include <intrin.h>
    inline int32_t bit_scan_forward(int x){
        unsigned long z;
        _BitScanForward(&z, x);
        return z;
    }
#else
    #error "Only gcc, clang and mvsc compiler are supported."
#endif

/* Constructor */
Sudoku::Sudoku(std::vector<uint32_t> S)
    : gridsize(std::sqrt(S.size())), puzzle(S), binrows(gridsize, 0),
      bincols(gridsize, 0), binboxes(gridsize, 0), binindx(gridsize, 0) {
    encodeToBinary();
};

Sudoku::Sudoku(std::string str)
    : gridsize(std::sqrt(str.length())), puzzle(str.length(), 0),
      binrows(gridsize, 0), bincols(gridsize, 0), binboxes(gridsize, 0),
      binindx(gridsize, 0) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '.') {
            puzzle[i] = 0;
        }
        if (str[i] >= '1' && str[i] <= '9') {
            puzzle[i] = str[i] - '0';
        }
    }
    encodeToBinary();
};

// Member functions
inline bool Sudoku::numValid(size_t num, size_t row, size_t col) const {
    std::uint32_t shift = 1U << num;
    return !(((binrows[row] & shift) || (bincols[col] & shift)) ||
             (binboxes[3 * (row / 3) + (col / 3)] & shift));
}

inline void Sudoku::setNum(size_t num, size_t row, size_t col) {
    uint32_t shift = 1U << num;
    binrows[row] |= shift;
    bincols[col] |= shift;
    binboxes[3 * (row / 3) + (col / 3)] |= shift;
    binindx[row] |= (1U << col);
    puzzle[(row)*gridsize + col] = num;
}

inline void Sudoku::delNum(size_t num, size_t row, size_t col) {
    uint32_t nshift = ~(1U << num);
    binrows[row] &= nshift;
    bincols[col] &= nshift;
    binboxes[3 * (row / 3) + (col / 3)] &= nshift;
    binindx[row] &= ~(1U << col);
    puzzle[(row)*gridsize + col] = 0U;
}

inline bool Sudoku::solver() {
    std::pair<int, int> pos = findEmptyCell();
    if (pos.first == -1 || pos.second == -1) {
        return true;
    }

    for (size_t num = 1; num <= 9; ++num) {
        if (numValid(num, pos.first, pos.second)) {
            setNum(num, pos.first, pos.second);
            if (solver()) {
                return true;
            }
            // Backtracking
            delNum(num, pos.first, pos.second);
        }
    }

    // Backtracking / Abbruch
    return false;
}

bool Sudoku::solve(bool timing) {
    bool status = true;
    if (timing) {
        auto t_start = std::chrono::high_resolution_clock::now();
        status       = solver();
        auto t_end   = std::chrono::high_resolution_clock::now();
        runtime      = t_end - t_start;
    } else {
        status = solver();
    }
    return status;
}

void Sudoku::print() const {
    printf("\n");
    int N = gridsize;
    // printf("Gridsize: %zu\n", gridsize);
    char q     = (char)std::sqrt(N);
    char *cstr = (char *)calloc(N * 3 + (std::sqrt(N) - 1) * 3, sizeof(char));
    memset(cstr, '-', N * 3 + (std::sqrt(N) - 1) * 3);
    for (char i = 0; i < N; ++i) {
        if (i % q == 0 && i > 0) {
            printf("%s\n", cstr);
        }
        for (char j = 0; j < N; ++j) {
            if (((j + 1) % q == 0) && j + 1 != N) {
                printf("%2d  | ", puzzle[i * gridsize + j]);
            } else if (j + 1 == N) {
                printf("%2d\n", puzzle[i * gridsize + j]);
            } else {
                printf("%2d ", puzzle[i * gridsize + j]);
            }
        }
    }
    free(cstr);
    printf("\n");
}

double Sudoku::getRuntime() const {
    return runtime.count();
}

inline std::pair<int, int> Sudoku::findEmptyCell() const {
    std::pair<int, int> t{-1, -1};
    for (size_t i = 0; i < 9; ++i) {
        int32_t col = bit_scan_forward(~(binindx[i]));
        if (col != -1 && col != 9) {
            t.first  = i;
            t.second = col;
            return t;
        }
    }
    return t;
}

void Sudoku::encodeToBinary() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (puzzle[i * gridsize + j] > 0U) {
                int k = 3 * (i / 3) + (j / 3);
                binindx[i] |= (1U << j);
                binrows[i] |= (1U << puzzle[i * gridsize + j]);
                bincols[j] |= (1U << puzzle[i * gridsize + j]);
                binboxes[k] |= (1U << puzzle[i * gridsize + j]);
            }
        }
    }
}

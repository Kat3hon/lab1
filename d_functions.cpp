#include "d_functions.h"

using namespace sparseMatrix;

int dialog(const char* msgs[], int N) {
    int rc;
    do {
        for (int i = 0; i < N; i++)
            std::cout << msgs[i] << std::endl;
        std::cout << std::endl;
        try {
            getInt(rc);
        }
        catch(int num) {
            std::cout << sparseMatrix::errList(num-1) << std::endl;
            return 0;
        }

        if (rc < 0 || rc >= N)
            std::cout << sparseMatrix::errList(5) << std::endl;
    } while (rc < 0 || rc >= N);
    return rc;
}

int D_Operation(Matrix **matr) {
    if (isEmpty(*matr)) {
        std::cout << sparseMatrix::errList(4) << std::endl;
        return 0;
    }
    Matrix* sideMatr = nullptr;
    try {
        sideMatr = createMatr((*matr)->lines, (*matr)->columns);
    }
    catch(std::bad_alloc) {
        std::cout << sparseMatrix::errList(6) << std::endl;
        eraseMatr(*matr);
        eraseMatr(sideMatr);
        return 1;
    }

    search(*matr, sideMatr);
    D_Show(&sideMatr);
    eraseMatr(sideMatr);
    return 0;
}

int D_Show(Matrix **matr) {
    if (isEmpty(*matr)) {
        std::cout << sparseMatrix::errList(4) << std::endl;
        return 0;
    }
    std::cout << "Matrix:" << std::endl;
    int currLine = 0;
    for (List *ptrMainHead = (*matr)->head; ptrMainHead != nullptr; ptrMainHead = ptrMainHead->ptrNext) {
        //show zero elements before those, which exist
        showPrepare(ptrMainHead->line, currLine, (*matr)->lines, (*matr)->columns);
        //show all columns in that line
        showColumns((*matr)->columns, ptrMainHead);
        ++currLine;
        std::cout << std::endl;
    }
    //show all other elements (which is zeros)
    topUpMatrix(currLine, (*matr)->lines, (*matr)->columns);
    return 0;
}

int D_Add(Matrix **matr) {
    //if (!isEmpty)
    if (isEmpty(*matr)) {
        try {
            *matr = createMatr();
        }
        catch(std::bad_alloc) {
            std::cout << sparseMatrix::errList(6) << std::endl;
            eraseMatr(*matr);
            return 1;
        }
    }
    std::cout << std::endl << "Let's fill Matrix with value!" << std::endl << std::endl;
    int i;
    do {
        std::cout << "Enter the i-coordinate:" << std::endl;
        try {
            getInt(i);
        }
        catch(int num) {
            std::cout << sparseMatrix::errList(num-1) << std::endl;
            return 1;
        }
        if (i < 0 || i >= (*matr)->lines)
            std::cout << sparseMatrix::errList(2) << std::endl;
    } while (i < 0 || i >= (*matr)->lines);

    int j;
    do {
        std::cout << "Enter the j-coordinate:" << std::endl;
        try {
            getInt(j);
        }
        catch(int num) {
            std::cout << sparseMatrix::errList(num-1) << std::endl;
            return 1;
        }
        if (j < 0 || j >= (*matr)->columns)
            std::cout << sparseMatrix::errList(2) << std::endl;
    } while (j < 0 || j >= (*matr)->columns);

    int value;
    do {
        std::cout << "Enter the value:" << std::endl;
        try {
            getInt(value);
        }
        catch(int num) {
            std::cout << sparseMatrix::errList(num-1) << std::endl;
            return 1;
        }
        if (value == 0)
            std::cout << sparseMatrix::errList(2) << std::endl;
    } while (value == 0);
    if(insert(*matr, value, i, j, false))
        return 1;
    return 0;
}

int D_Random(Matrix **matr) {
    if (!isEmpty(*matr)) {
        eraseMatr(*matr);
    }
    try {
        *matr = createMatr();
    }
    catch(std::bad_alloc) {
        std::cout << sparseMatrix::errList(6) << std::endl;
        eraseMatr(*matr);
        return 1;
    }

    std::cout << std::endl << "Let's fill Matrix with values!" << std::endl << std::endl;

    int amount;
    do {
        std::cout << "Enter an amount of elements (they will be random):" << std::endl;
        try {
            getInt(amount);
        }
        catch(int num) {
            std::cout << sparseMatrix::errList(num-1) << std::endl;
            return 1;
        }
        if (amount < 0 || amount >= ((*matr)->lines)*((*matr)->columns))
            std::cout << sparseMatrix::errList(2) << std::endl;
    } while (amount <= 0 || amount > ((*matr)->lines)*((*matr)->columns));

    srand(time(NULL));
    while (amount > 0) {
        int i = rand()%((*matr)->lines - 1);
        int j = rand()%((*matr)->columns - 1);
        int value = rand()%298 + -99; //equal distribution: -99..99 - 198 numbers, 100..298 - 198 numbers
        int n = insert(*matr, value, i, j, true);
        if (n == 1)
            return 1;
        if (n == -1) {
	    std::cout << "here" << std::endl;
            amount++;
	}
        amount--;
    }
    return 0;
}

#include <iostream>
#include <limits>

namespace sparseMatrix {
    typedef struct Node {
        struct Node* ptrNext; //pointer to next elem in List
        int value;
        int column;
    }Node;

    typedef struct List {
        int line;
        double avgD; //average number of digits in list at the moment;
        int count; //number of elemens in List at the moment;
        struct Node* head; //pointer to the first elem in list;
        struct List* ptrNext; //pointer to next list
    }List;

    typedef struct Matrix {
        int lines;
        int columns;
        struct List *head; //pointer to the first list
    }Matrix;

    char* errList(int num);

    int getInt(int &x);

    int init(int& value, const char* msg);

    int numD(int value);

    bool isEmpty(const Matrix *matr);

    Matrix *createMatr(int i, int j);

    Matrix *createMatr();

    List *createList(int i);

    Node *createNode(int value, int i, int j);

    void ordering (List *ptrMainHead, Node* newNode);

    void ordering(Matrix *matr, List* newList);

    bool isExist(Node* head, int j);

    int insert(Matrix *matr, int value, int i, int j, bool isR);

    int eraseMatr(Matrix *matr);

    void search(Matrix *matr, Matrix *sideMatr);

    void showColumns(int colsNum, List* list);

    void showBeforeVal(int start, int colsNum, int end, int& count);

    void topUpMatrix(int start, int lines, int columns);

    void showPrepare(int line, int& currline, int numLines, int numCols);
}

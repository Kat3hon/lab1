#include "matrix_functions.h"

using namespace sparseMatrix;

char* sparseMatrix::errList(int num) {
    char* err[] = {"Error! Wrong value! Breaking...", "End of file! Breaking...", "Incorrect value! Try again!",
                   "There is already that element in matrix! Try again!", "Matrix is already empty. Try again!",
                   "Error! Repeat...", "Error! Bad alloc! Breaking..."};
    return err[num];
}

int sparseMatrix::getInt(int &x){
    std::cin >> x;
    if (std::cin.fail())
            throw 1;
    if (std::cin.eof())
            throw 2;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 0;
}

int sparseMatrix::init(int& value, const char* msg) {
    do {
        std::cout << msg << std::endl;
        try {
            getInt(value);
        }
        catch (int num) {
            std::cout << sparseMatrix::errList(num-1) << std::endl;
            return 1;
        }
        if (value <= 0)
            std::cout << sparseMatrix::errList(2) << std::endl;
    } while (value <= 0);
    return 0;
}

int sparseMatrix::numD(int value) {
    if (value < 0)
        value = -value;
    if (value == 0)
        return 1;
    int count = 0;
    while (value > 0) {
        ++count;
        value /= 10;
    }
    return count;
}

bool sparseMatrix::isEmpty(const Matrix *matr) {
    if (matr == nullptr)
        return true;
    return false;
}

Matrix * sparseMatrix::createMatr(int i, int j) {
    Matrix *matr = new Matrix();
    matr->lines = i;
    matr->columns = j;
    return matr;
}

Matrix * sparseMatrix::createMatr() {
    Matrix *matr = new Matrix();
    if(init(matr->lines, "Enter an amount of lines:"))
        return nullptr;
    if(init(matr->columns,"Enter an amount of columns:"))
        return nullptr;
    return matr;
}

List * sparseMatrix::createList(int i) {
    List *ptr = new List();
    ptr->count = 0;
    ptr->line = i;
    ptr->avgD = 0;
    ptr->head = nullptr;
    ptr->ptrNext = nullptr;
    return ptr;
}

Node * sparseMatrix::createNode(int value, int i, int j) {
    Node *ptr = new Node();
    ptr->ptrNext = nullptr;
    ptr->value = value;
    ptr->column = j;
    return ptr;
}

void sparseMatrix::ordering (List *ptrMainHead, Node *newNode) {
    Node* ptrNode = ptrMainHead->head;
    Node* prevNode = nullptr;
    while (ptrNode != nullptr && ptrNode->column < newNode->column) {
        prevNode = ptrNode;
        ptrNode = ptrNode->ptrNext;
    }
    if (prevNode == nullptr) { //push forward
        newNode->ptrNext = ptrMainHead->head;
        ptrMainHead->head = newNode;
        return;
    }
    if (ptrNode == nullptr) {//push back
        newNode->ptrNext = prevNode->ptrNext;
        prevNode->ptrNext = newNode;
        return;
    }
    //push smwhere else
    newNode->ptrNext = prevNode->ptrNext;
    prevNode->ptrNext = newNode;
    return;
}

void sparseMatrix::ordering(Matrix *matr, List *newList) {
    List *ptrMainHead = matr->head;
    List *prevMainHead = nullptr;
    while (ptrMainHead != nullptr && ptrMainHead->line < newList->line) {
        prevMainHead = ptrMainHead;
        ptrMainHead = ptrMainHead->ptrNext;
    }
    if (prevMainHead == nullptr) { //push forward
        newList->ptrNext = matr->head;
        matr->head = newList;
        return;
    }
    if (ptrMainHead == nullptr) { //push back
        newList->ptrNext = prevMainHead->ptrNext;
        prevMainHead->ptrNext = newList;
        return;
    }
    //push smwhere else
    newList->ptrNext = prevMainHead->ptrNext;
    prevMainHead->ptrNext = newList;
}

bool sparseMatrix::isExist(Node* head, int j) {
    Node* ptrNode = head;
    while (ptrNode != nullptr) {
        if (ptrNode->column == j)
            return true;
        ptrNode = ptrNode->ptrNext;
    }
    return false;
}

int sparseMatrix::insert(Matrix *matr, int value, int i, int j, bool isR) {
    if (isEmpty(matr)) { //create the first list
        try {
            matr->head = createList(i);
        }
        catch(std::bad_alloc) {
            std::cout << sparseMatrix::errList(6) << std::endl;
            eraseMatr(matr);
            return 1;
        }

        try {
            matr->head->head = createNode(value,i,j);
        }
        catch(std::bad_alloc) {
            std::cout << sparseMatrix::errList(6) << std::endl;
            eraseMatr(matr);
            return 1;
        }

        (matr->head->count)++;
        matr->head->avgD = double(((matr->head->avgD)*(matr->head->count - 1)+numD(matr->head->head->value))/(matr->head->count));
        return 0;
    }
    else {
        for (sparseMatrix::List* ptrMainHead = matr->head; ptrMainHead != nullptr; ptrMainHead = ptrMainHead->ptrNext)
            if (ptrMainHead->line == i) { //go to the line #i
                if (isExist(ptrMainHead->head, j)) {
                    if (!isR) {
                        std::cout << sparseMatrix::errList(3) << std::endl;
                    	return 0;
	            }
		    return 2;
                }
                Node* ptrNode = nullptr;
                try {
                    ptrNode = createNode(value,i,j);
                }
                catch(std::bad_alloc) {
                    std::cout << sparseMatrix::errList(6) << std::endl;
                    eraseMatr(matr);
                    return 1;
                }
                ordering(ptrMainHead, ptrNode);
                (ptrMainHead->count)++;
                ptrMainHead->avgD = double(((ptrMainHead->avgD)*(ptrMainHead->count - 1)+numD(ptrNode->value))/(ptrMainHead->count));
                return 0;
            }

        //line was not found
        List* newList = nullptr;
        try {
            newList = createList(i);
        }
        catch(std::bad_alloc) {
            std::cout << sparseMatrix::errList(6) << std::endl;
            eraseMatr(matr);
            return 1;
        }
        ordering(matr, newList);
        Node* newNode = nullptr;
        try {
            newNode = createNode(value,i,j);
        }
        catch(std::bad_alloc) {
            std::cout << sparseMatrix::errList(6) << std::endl;
            eraseMatr(matr);
            return 1;
        }
        newList->head = newNode;
        (newList->count)++;
        newList->avgD = double(((newList->avgD)*(newList->count - 1)+numD(newNode->value))/(newList->count));
        return 0;
    }
}

int sparseMatrix::eraseMatr(sparseMatrix::Matrix *matr) {
    if (isEmpty(matr)) {
        std::cout << sparseMatrix::errList(4) << std::endl;
        return 0;
    }
    List *ptrMainHead = matr->head;
    List *tmpMainHead = nullptr;
    while (ptrMainHead != nullptr) {
        sparseMatrix::Node *ptrNode = ptrMainHead->head;
        sparseMatrix::Node *tmpNode = nullptr;
        while (ptrNode != nullptr) {
            tmpNode = ptrNode->ptrNext;
            delete ptrNode;
            ptrNode = tmpNode;
        }
        tmpMainHead = ptrMainHead->ptrNext;
        delete ptrMainHead;
        ptrMainHead = tmpMainHead;
    }
    delete matr;
    return 0;
}

void sparseMatrix::search(Matrix *matr, Matrix *sideMatr) {
    for (List *ptrMainHead = matr->head; ptrMainHead != nullptr; ptrMainHead = ptrMainHead->ptrNext)
        for (Node* ptrNode = ptrMainHead->head; ptrNode != nullptr; ptrNode = ptrNode->ptrNext)
            if (numD(ptrNode->value) > ptrMainHead->avgD)
                insert(sideMatr, ptrNode->value, ptrMainHead->line, ptrNode->column, false);
}

void sparseMatrix::showBeforeVal(int start, int colsNum, int end, int& count) {
    for (int i = start; i < end && count < colsNum; ++i, ++count)
        std::cout << ".\t";
}


void sparseMatrix::showColumns(int colsNum, List* list) {
    Node *prevNode = nullptr;
    int columnCount = 0;
    for (Node *ptrNode = list->head; ptrNode != nullptr; ptrNode = ptrNode->ptrNext) {
        if (prevNode == nullptr)
            showBeforeVal(0, colsNum, ptrNode->column, columnCount);
        else showBeforeVal(prevNode->column + 1, colsNum, ptrNode->column, columnCount);

        std::cout << ptrNode->value << "\t";
        ++columnCount;
        prevNode = ptrNode;
    }
    //show after all values
    for (int i = columnCount; i < colsNum; ++i)
        std::cout << ".\t";
}

void sparseMatrix::topUpMatrix(int start, int lines, int columns) {
    for (int i = start; i < lines; ++i) {
        for (int j = 0; j < columns; ++j)
            std::cout << ".\t";
        std::cout << std::endl;
    }
}

void sparseMatrix::showPrepare(int line, int& currLine, int numLines, int numCols) {
    while (line != currLine && currLine < numLines && currLine < line) {
        for (int i = 0; i < numCols; ++i)
            std::cout << ".\t";
        ++currLine;
        std::cout << std::endl;
    }
}

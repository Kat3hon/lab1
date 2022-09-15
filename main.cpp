#include "d_functions.h"


/* Вариант 29
Из входного потока вводится прямоугольная сильно разреженная матрица целых чисел [aij], i = 1, …, m, j
= 1, …, n. Значения m и n заранее не известны и вводятся из входного потока.
Сформировать новую матрицу, поместив в ее i-ую строку те элементы из i-ой строки исходной матрицы,
количество цифр в записи которых превышает среднее количество цифр в записи всех элементов данной
строки матрицы.
Исходную и полученную матрицы вывести в выходной поток с необходимыми комментариями.
*/

//namespace sparseMatrix {
//    typedef struct Node {
//        struct Node* ptrNext; //pointer to next elem in List
//        int value;
//        int column;
//    }Node;
//
//    typedef struct List {
//        int line;
//        double avgD; //average number of digits in list at the moment;
//        int count; //number of elemens in List at the moment;
//        struct Node* head; //pointer to the first elem in list;
//        struct List* ptrNext; //pointer to next list
//    }List;
//
//    typedef struct Matrix {
//        int lines;
//        int columns;
//        struct List *head; //pointer to the first list
//    }Matrix;
//
//    //OPERATIONS WITH SIDE LIST
//}
//
//int getInt(){
//    int x;
//    std::cin >> x;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//    return x;
//}
//
//
//int init(const char* msg) {
//    int value;
//    do {
//        std::cout << msg << std::endl;
//        value = getInt();
//        if (value <= 0)
//            std::cout << "Incorrect value! Try again!" << std::endl;
//    } while (value <= 0);
//    return value;
//}
//
//bool isEmpty(const sparseMatrix::Matrix *matr) {
//    if (matr == nullptr)
//        return true;
//    return false;
//}
//
//sparseMatrix::Matrix *createMatr(int i, int j) {
//    sparseMatrix::Matrix *matr = new sparseMatrix::Matrix();
//    matr->lines = i;
//    matr->columns = j;
//    return matr;
//}
//
//sparseMatrix::Matrix *createMatr() {
//    sparseMatrix::Matrix *matr = new sparseMatrix::Matrix();
//    matr->lines = init("Enter an amount of lines:");
//    matr->columns = init("Enter an amount of columns:");
//    return matr;
//}
//
//sparseMatrix::List *createList(int i) {
//    sparseMatrix::List *ptr = new sparseMatrix::List(); //try catch
//    ptr->count = 0;
//    ptr->line = i;
//    ptr->avgD = 0;
//    ptr->head = nullptr;
//    ptr->ptrNext = nullptr;
//    return ptr;
//}
//
//sparseMatrix::Node *createNode(int value, int i, int j) {
//    sparseMatrix::Node *ptr = new sparseMatrix::Node(); //try catch
//    ptr->ptrNext = nullptr;
//    ptr->value = value;
//    ptr->column = j;
//    return ptr;
//}
//
//void ordering (sparseMatrix::List *ptrMainHead, sparseMatrix::Node* newNode) {
//    sparseMatrix::Node* ptrNode = ptrMainHead->head;
//    sparseMatrix::Node* prevNode = nullptr;
//    while (ptrNode != nullptr && ptrNode->column < newNode->column) {
//        prevNode = ptrNode;
//        ptrNode = ptrNode->ptrNext;
//    }
//    if (prevNode == nullptr) { //push forward
//        newNode->ptrNext = ptrMainHead->head;
//        ptrMainHead->head = newNode;
//        return;
//    }
//    if (ptrNode == nullptr) {//push back
//        newNode->ptrNext = prevNode->ptrNext;
//        prevNode->ptrNext = newNode;
//        return;
//    }
//    //push smwhere else
//    newNode->ptrNext = prevNode->ptrNext;
//    prevNode->ptrNext = newNode;
//    return;
//}
//
//void ordering(sparseMatrix::Matrix *matr, sparseMatrix::List* newList) {
//    sparseMatrix::List *ptrMainHead = matr->head;
//    sparseMatrix::List *prevMainHead = nullptr;
//    while (ptrMainHead != nullptr && ptrMainHead->line < newList->line) {
//        prevMainHead = ptrMainHead;
//        ptrMainHead = ptrMainHead->ptrNext;
//    }
//    if (prevMainHead == nullptr) { //push forward
//        newList->ptrNext = matr->head;
//        matr->head = newList;
//        return;
//    }
//    if (ptrMainHead == nullptr) { //push back
//        newList->ptrNext = prevMainHead->ptrNext;
//        prevMainHead->ptrNext = newList;
//        return;
//    }
//    //push smwhere else
//    newList->ptrNext = prevMainHead->ptrNext;
//    prevMainHead->ptrNext = newList;
//    return;
//}
//
//int numD(int value) {
//    if (value < 0)
//        value = -value;
//    if (value == 0)
//        return 1;
//    int count = 0;
//    while (value > 0) {
//        ++count;
//        value /= 10;
//    }
//    return count;
//}
//
//bool isExist(sparseMatrix::Node* head, int j) {
//    sparseMatrix::Node* ptrNode = head;
//    while (ptrNode != nullptr) {
//        if (ptrNode->column == j)
//            return true;
//        ptrNode = ptrNode->ptrNext;
//    }
//    return false;
//}
//
//void insert(sparseMatrix::Matrix *matr, int value, int i, int j) {
//    if (isEmpty(matr)) { //create the first list
//        matr->head = createList(i);
//        matr->head->head = createNode(value,i,j);
//        (matr->head->count)++;
//        matr->head->avgD = double(((matr->head->avgD)*(matr->head->count - 1)+numD(matr->head->head->value))/(matr->head->count));
//    }
//    else {
//        for (sparseMatrix::List* ptrMainHead = matr->head; ptrMainHead != nullptr; ptrMainHead = ptrMainHead->ptrNext)
//            if (ptrMainHead->line == i) { //go to the line #i
//                if (isExist(ptrMainHead->head, j)) {
//                    std::cout << "There is already that element in matrix! Try again." << std::endl;
//                    return;
//                }
//                sparseMatrix::Node *ptrNode = createNode(value, i, j);
//                ordering(ptrMainHead, ptrNode);
//                (ptrMainHead->count)++;
//                ptrMainHead->avgD = double(((ptrMainHead->avgD)*(ptrMainHead->count - 1)+numD(ptrNode->value))/(ptrMainHead->count));
//                return;
//            }
//
//        //line was not found
//        sparseMatrix::List* newList = createList(i);
//        ordering(matr, newList);
//        sparseMatrix::Node* newNode = createNode(value, i, j);
//        newList->head = newNode;
//        (newList->count)++;
//        newList->avgD = double(((newList->avgD)*(newList->count - 1)+numD(newNode->value))/(newList->count));
//        return;
//    }
//}
//
//int eraseMatr(sparseMatrix::Matrix *matr) {
//    if (isEmpty(matr)) {
//        std::cout << "Matrix is already empty. Try again." << std::endl;
//        return 0;
//    }
//    sparseMatrix::List *ptrMainHead = matr->head;
//    sparseMatrix::List *tmpMainHead = nullptr;
//    while (ptrMainHead != nullptr) {
//        sparseMatrix::Node *ptrNode = ptrMainHead->head;
//        sparseMatrix::Node *tmpNode = nullptr;
//        while (ptrNode != nullptr) {
//            tmpNode = ptrNode->ptrNext;
//            delete ptrNode;
//            ptrNode = tmpNode;
//        }
//        tmpMainHead = ptrMainHead->ptrNext;
//        delete ptrMainHead;
//        ptrMainHead = tmpMainHead;
//    }
//    delete matr;
//    return 0;
//}
//
//int D_Random(sparseMatrix::Matrix **matr) {
//    if (!isEmpty(*matr)) {
//        eraseMatr(*matr);
//        *matr = createMatr();
//    }
//    std::cout << std::endl << "Let's fill Matrix with values!" << std::endl << std::endl;
//    int amount;
//    char* errmsg = "";
//    do {
//        std::cout << errmsg << std::endl;
//        errmsg = "Incorrect value! Try again.\n";
//        std::cout << "Enter an amount of elements (they will be random):" << std::endl;
//        amount = getInt();
//    } while (amount <= 0 || amount > ((*matr)->lines)*((*matr)->columns));
//    srand(time(NULL));
//    while (amount > 0) {
//        int i = rand()%((*matr)->lines - 1);
//        int j = rand()%((*matr)->columns - 1);
//        int value = rand()%MAX + MIN;
//        insert(*matr, value, i, j);
//        amount--;
//    }
//    return 0;
//}
//
//int D_Add(sparseMatrix::Matrix **matr) {
//    if (isEmpty(*matr))
//        *matr = createMatr();
//    std::cout << std::endl << "Let's fill Matrix with value!" << std::endl << std::endl;
//    char* errmsg = "";
//    int i;
//    do {
//        std::cout << errmsg << std::endl;
//        errmsg = "Incorrect value! Try again.\n";
//        std::cout << "Enter the i-coordinate:" << std::endl;
//        i = getInt();
//    } while (i < 0 || i >= (*matr)->lines);
//
//    int j;
//    errmsg = "";
//    do {
//        std::cout << errmsg << std::endl;
//        errmsg = "Incorrect value! Try again.\n";
//        std::cout << "Enter the j-coordinate:" << std::endl;
//        j = getInt();
//    } while (j < 0 || j >= (*matr)->columns);
//
//    int value;
//    errmsg = "";
//    do {
//        std::cout << errmsg << std::endl;
//        errmsg = "Incorrect value! Try again.\n";
//        std::cout << "Enter the value:" << std::endl;
//        value = getInt();
//    } while (value == 0);
//    insert(*matr, value, i, j);
//    return 0;
//}

int main() {
    sparseMatrix::Matrix *mainMatr = nullptr;
    const char* msgs[] = {"\n0.Quit", "1.Add", "2.Operation","3.Show", "4.Random generation"};
    const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
    int (*fptr[])(sparseMatrix::Matrix**) = {nullptr, D_Add, D_Operation, D_Show, D_Random};
    int rc;
    while (rc = dialog(msgs, NMsgs))
        if (fptr[rc](&mainMatr))
            break;
    std::cout << "That is all! End..." << std::endl;
    eraseMatr(mainMatr);
    return 0;
}

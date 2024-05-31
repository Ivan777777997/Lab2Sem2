#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
using namespace std;
struct list {
    int data;
    list* prev;
    list* next;
};

list* createNode(int data) {
    list* newNode = new list;
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

void showList(list* beg)
{
    if (beg == nullptr)
    {
        cout << "The list is empty." << endl;
        return;
    }

    list* current = beg;
    while (current != nullptr)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void createRandomList(list* &beg, int N) {
    int seed = time(NULL);
    srand(seed);
    list* tail = nullptr;
    
    for (int i = 0; i < N; ++i) {
        int randomData = rand() % 100;
        list* newNode = createNode(randomData);
        
        if (beg == nullptr) {
            beg = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    list* current = beg;
    cout << "List elements: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
void createInputList(list* &beg) {
    list* tail = nullptr;
    int N = 0;
    int input = 0;

    cout << "Enter list elements:" << endl;
    while(cin >> input) {;
        
        list* newlist = createNode(input);
        
        if (beg == nullptr) {
            beg = newlist;
            tail = newlist;
        } else {
            tail->next = newlist;
            newlist->prev = tail;
            tail = newlist;
        }

        N++;
        if(cin.peek() == '\n') {
            break;
        }
    }
    list* current = beg;
    cout << "List elements: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void appendNodeToList(list*& beg, int newData) {
    list* newNode = new list;
    newNode->data = newData;
    newNode->next = nullptr;

    if (beg == nullptr) {
        beg = newNode;
    } 
    else {
        list* current = beg;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

void deleteNodeByIndex(list*& beg, int index) {
    if (beg == nullptr) {
        cout << "The list is empty" << endl;
        return;
    }

    list* temp = beg;
    if (index == 0) {
        beg = temp->next;
        delete temp;
        return;
    }

    for (int i = 0; temp != nullptr && i < index - 1; i++) {
        temp = temp->next;
    }

    if (temp == nullptr || temp->next == nullptr) {
        cout << "Element not found in the list." << endl;
        return;
    }

    list* nextlist = temp->next->next;
    delete temp->next;
    temp->next = nextlist;
    if (nextlist != nullptr) {
        nextlist->prev = temp;
    }
}

void deleteNodeByValue(list*& beg, int value) {
    list* temp = beg;

    if (temp != nullptr && temp->data == value) {
        beg = temp->next;
        beg->prev = nullptr;
        delete temp;
        return;
    }

    while (temp != nullptr && temp->data != value) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Element not found in the list." << endl;
        return;
    }

    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }

    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }

    delete temp;
}

void swapNodes(list* beg, int pos1, int pos2) {
    if (beg == nullptr) {
        cout << "The list is empty" << endl;
        return;
    }
    
    list* temp1 = beg;
    list* temp2 = beg;
    int count = 1;
    bool found1 = false;
    bool found2 = false;
    
    while (temp1 != nullptr && count != pos1) {
        temp1 = temp1->next;
        count++;
    }
    if (temp1 != nullptr) {
        found1 = true;
    }
    
    count = 1;
    
    while (temp2 != nullptr && count != pos2) {
        temp2 = temp2->next;
        count++;
    }
    if (temp2 != nullptr) {
        found2 = true;
    }
    
    if (!found1 || !found2) {
        cout << "List item not found." << endl;
    } else {
        int tempData = temp1->data;
        temp1->data = temp2->data;
        temp2->data = tempData;
        list* current = beg;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
}

void getNodeByIndex(list* beg, int index) {
    list* currNode = beg;
    int currentIndex = 0;

    while (currNode != nullptr && currentIndex < index) {
        currNode = currNode->next;
        currentIndex++;
    }

    if (currNode == nullptr) {
        cout << "Error: element with index " << index << " not found\n";
    } else {
        cout << "Element with index " << index << endl << " data: " << currNode->data << endl <<
        "prev: " << currNode->prev << endl << "next: " << currNode->next << endl;
    }
}

void getNodeByValue(list* beg, int value) {
    list* current = beg;
     bool found = false;
    
    while (current != nullptr) {
        if (current->data == value) {
            cout << "Element with value " << value << endl << " data: " << current->data << endl <<
            "prev: " << current->prev << endl << "next: " << current->next << endl << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found){
    cout << "Element not found." << endl;
    }
}

int main() {
    list* beg = nullptr;
    cout << "Choose variant of list creation (1 or 2): " << endl;
    int item;
    cin >> item;
    switch (item){
        case 1: int N;
        cout << "Enter number of list elements: ";
        cin >> N;
        {
        auto start = chrono::high_resolution_clock::now();
        createRandomList(beg, N);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "List creation time: " << duration.count() << " seconds." << endl;
        }
        break;

        case 2: {
        auto start = chrono::high_resolution_clock::now();
        createInputList(beg);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "List creation time: " << duration.count() << " seconds." << endl;
        }
        break;

        default: {
            cout << "Error!";
        }
    }
    int item1 = 1;
    while (item1 != 0) {

    cout << "Choose an item: " << endl <<
    "1. Add new element" << endl <<
    "2. Delete element by index" << endl <<
    "3. Delete element by value" << endl <<
    "4. Swap elements" << endl <<
    "5. Get element by index" << endl <<
    "6. Get element by value" << endl <<
    "0. End of program" << endl;

    cin >> item1;
    switch (item1) {
        case 1: {
        int data;
        cout << "Enter element value: " << endl;
        cin >> data;
        
        auto start = chrono::high_resolution_clock::now();
        appendNodeToList(beg, data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Add element time: " << duration.count() << " seconds." << endl;

        showList(beg);
        cout << endl;
        }
        break;

        case 2: {
        int data;
        cout << "Enter element index: " << endl;
        cin >> data;
        
        auto start = chrono::high_resolution_clock::now();
        deleteNodeByIndex(beg, data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Delete element time: " << duration.count() << " seconds." << endl;

        showList(beg);
        cout << endl;
        }
        break;

        case 3: {
        int data;
        cout << "Enter element value: " << endl;
        cin >> data;
        
        auto start = chrono::high_resolution_clock::now();
        deleteNodeByValue(beg, data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Delete element by value time: " << duration.count() << " seconds." << endl;

        showList(beg);
        cout << endl;
        }
        break;

        case 4: {
        int data1, data2;
        cout << "Enter element numbers: " << endl;
        cin >> data1 >> data2;
        
        auto start = chrono::high_resolution_clock::now();
        swapNodes(beg, data1, data2);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Swap elements time: " << duration.count() << " seconds." << endl;

        showList(beg);
        cout << endl;
        }
        break;

        case 5: {
        int data;
        cout << "Enter element index: " << endl;
        cin >> data;
        
        auto start = chrono::high_resolution_clock::now();
        getNodeByIndex(beg, data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Get element by index time: " << duration.count() << " seconds." << endl;

        showList(beg);
        cout << endl;
        }
        break;

        case 6: {
        int data;
        cout << "Enter element value: " << endl;
        cin >> data;
        
        auto start = chrono::high_resolution_clock::now();
        getNodeByValue(beg, data);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;
        cout << "Get element by value time: " << duration.count() << " seconds." << endl;

        showList(beg);
        cout << endl;
        }
        break;

        case 0: 
        break;

        default:
        cout << "Error! Try again" << endl;
    }
    }
    list* current = beg;
    while (current != nullptr)
    {
        list* temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}
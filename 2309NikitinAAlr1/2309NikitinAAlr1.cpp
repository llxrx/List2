#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // 1)Add to the end of the list
    void addToEnd(int val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        size++;
    }

    // 2)Add to the beginning of the list
    void addToBeginning(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    // 3)Remove the last element
    void removeLast() {
        if (tail == nullptr) {
            cout << "List is empty.\n";
        }
        else if (head == tail) {
            delete tail;
            head = tail = nullptr;
            size--;
        }
        else {
            Node* prevTail = tail->prev;
            delete tail;
            prevTail->next = nullptr;
            tail = prevTail;
            size--;
        }
    }

    // 4)Remove the first element
    void removeFirst() {
        if (head == nullptr) {
            cout << "List is empty.\n";
        }
        else if (head == tail) {
            delete head;
            head = tail = nullptr;
            size--;
        }
        else {
            Node* nextHead = head->next;
            delete head;
            nextHead->prev = nullptr;
            head = nextHead;
            size--;
        }
    }

    // 5)Add an element by index
    void insertAtIndex(int val, int index) {
        if (index < 0 || index > size) {
            cout << "Invalid index.\n";
            return;
        }
        if (index == 0) {
            addToBeginning(val);
        }
        else if (index == size) {
            addToEnd(val);
        }
        else {
            Node* newNode = new Node(val);
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
            size++;
        }
    }

    // 6)Get an element by index
    int getAtIndex(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index.\n";
            return -1;
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // 7)Remove an element by index
    void removeAtIndex(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index.\n";
            return;
        }
        if (index == 0) {
            removeFirst();
        }
        else if (index == size - 1) {
            removeLast();
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            size--;
        }
    }

    // 8)Get list size
    int getSize() {
        return size;
    }

    // 9)Delete all list elements
    void clear() {
        while (head != nullptr) {
            removeFirst();
        }
    }

    // 10)Replacing an element by index with the element being transferred
    void replaceAtIndex(int index, int newValue) {
        if (index < 0 || index >= size) {
            cout << "Invalid index.\n";
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        current->data = newValue;
        cout << "Element at index " << index << " replaced with " << newValue << ".\n\n";
    }

    // 11)Check for empty list
    bool isEmpty() {
        return head == nullptr;
    }

    // 12)Reverses the order of elements in the list
    void reverse() {
        if (isEmpty() || head == tail) {
            return;
        }

        Node* current = head;
        Node* temp = nullptr;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;


            current = current->prev;
        }

        temp = head;
        head = tail;
        tail = temp;
    }

    // 13)Insert another list into a list, starting from index
    void insertListAtIndex(DoublyLinkedList& listToInsert, int index) {
        if (index < 0 || index > size) {
            cout << "Invalid index." << endl;
            return;
        }

        if (listToInsert.isEmpty()) {
            return;
        }

        if (index == 0) {
            insertListAtBeginning(listToInsert);
            return;
        }

        if (index == size) {
            insertListAtEnd(listToInsert);
            return;
        }

        Node* currentPtr = getNodeAtIndex(index);
        Node* prevPtr = currentPtr->prev;

        prevPtr->next = listToInsert.head;
        listToInsert.head->prev = prevPtr;
        currentPtr->prev = listToInsert.tail;
        listToInsert.tail->next = currentPtr;

        size += listToInsert.size;
    }

    // 14)Inserting another list at the end
    void insertListAtEnd(DoublyLinkedList& listToInsert) {
        if (listToInsert.isEmpty()) {
            return;
        }

        if (isEmpty()) {
            *this = listToInsert;
        }
        else {
            tail->next = listToInsert.head;
            listToInsert.head->prev = tail;
            tail = listToInsert.tail;
            size += listToInsert.size;
        }
    }

    // 15)Inserting another list at the beginning
    void insertListAtBeginning(DoublyLinkedList& listToInsert) {
        if (listToInsert.isEmpty()) {
            return;
        }
        if (isEmpty()) {
            *this = listToInsert;
        }
        else {
            if (listToInsert.head == nullptr) {
                return;
            }

            listToInsert.tail->next = head;
            head->prev = listToInsert.tail;
            head = listToInsert.head;
            size += listToInsert.size;
        }
    }

    // 16)Checking for the content of another list in a list, you can do it with an integer type
    bool containsList(DoublyLinkedList& listToCheck) {
        if (listToCheck.isEmpty()) {
            return true;
        }

        Node* currentListPtr = head;
        Node* sublistPtr = listToCheck.head;

        while (currentListPtr != nullptr && sublistPtr != nullptr) {
            if (currentListPtr->data == sublistPtr->data) {
                sublistPtr = sublistPtr->next;
            }
            currentListPtr = currentListPtr->next;
        }

        return sublistPtr == nullptr;
    }

    // 17)Finding the first occurrence of another list in a list
    int indexOfList(DoublyLinkedList& listToFind) {
        if (listToFind.isEmpty()) {
            return 0;
        }

        Node* currentListPtr = head;
        Node* sublistPtr = listToFind.head;
        int index = 0;

        while (currentListPtr != nullptr) {
            if (currentListPtr->data == sublistPtr->data) {
                sublistPtr = sublistPtr->next;

                if (sublistPtr == nullptr) {
                    return index - listToFind.size + 1;
                }
            }
            else {
                sublistPtr = listToFind.head;
            }
            currentListPtr = currentListPtr->next;
            index++;
        }

        return -1;
    }

    // 18)Finding the last occurrence of another list in a list
    int lastIndexOfList(DoublyLinkedList& listToFind) {
        if (listToFind.isEmpty()) {
            return size - 1;
        }

        Node* currentListPtr = tail;
        Node* sublistPtr = listToFind.tail;
        int index = size - 1;
        int sublistSize = listToFind.size;

        while (currentListPtr != nullptr) {
            if (currentListPtr->data == sublistPtr->data) {
                sublistPtr = sublistPtr->prev;

                if (sublistPtr == nullptr) {
                    return index + 1 - sublistSize;
                }
            }
            else {
                sublistPtr = listToFind.tail;
            }

            currentListPtr = currentListPtr->prev;
            index--;
        }
        return -1;
    }

    // 19)Exchange of two list elements by indexes
    void exchangeElementsByIndex(int index1, int index2) {
        if (index1 < 0 || index2 < 0 || index1 >= size || index2 >= size) {
            cout << "Invalid indexes." << endl;
            return;
        }

        if (index1 == index2) {
            return;
        }
        Node* node1 = getNodeAtIndex(index1);
        Node* node2 = getNodeAtIndex(index2);

        int temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }

    Node* getNodeAtIndex(int index) const {
        if (index < 0 || index >= size) {
            return nullptr;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current;
    }

    // Display the contents of the list
    void display() {
        Node* current = head;
        if (current == nullptr) cout << "List is empty";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
    }

};



int main() {
    int numLists;
    cout << "Enter the number of lists to create: ";
    cin >> numLists;

    DoublyLinkedList* lists = new DoublyLinkedList[numLists];

    int choice;
    int listIndex = 1;
    int value;
    int index;

    for (int i = 0; i < numLists; i++) {
        clock_t start = clock();
        cout << "Enter value to add to end List" << listIndex << ": ";
        cin >> value;
        listIndex++;
        for (int j = 0; j < value; j++)
        {
            lists[i].addToEnd(j);
        }
        clock_t end = clock();
        //double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
        //cout << "Time taken: " << timeSpent << " seconds.\n\n";
    }
    cout << "\n";

    while (true) {
        cout << "Select an operation:\n";
        cout << "1. adding to the end of the list\n";
        cout << "2. adding to the beginning of the list\n";
        cout << "3. removing the last element\n";
        cout << "4. removing the first element\n";
        cout << "5. adding an element by index\n";
        cout << "6. getting an element by index\n";
        cout << "7. removing an element by index\n";
        cout << "8. getting list size\n";
        cout << "9. deleting all list elements\n";
        cout << "10. replacing an element by index with the element being transferred\n";
        cout << "11. check for empty list\n";
        cout << "12. reverses the order of elements in the list\n";
        cout << "13. inserting another list into a list, starting at index\n";
        cout << "14. inserting another list at the end\n";
        cout << "15. inserting another list at the beginning\n";
        cout << "16. checking for the content of another list in a list, you can do it with an integer type\n";
        cout << "17. finding the first occurrence of another list in a list\n";
        cout << "18. Finding the last occurrence of another list in a list\n";
        cout << "19. exchange of two list elements by indexes\n";

        cout << "20. Display list\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1: {
            clock_t start = clock();
            cout << "Enter the list index (1 to " << numLists << "): ";
            cin >> listIndex;
            cout << "Enter value to add to end: ";
            cin >> value;
            listIndex--;
            lists[listIndex].addToEnd(value);
            clock_t end = clock();
            double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
            cout << "Time taken: " << timeSpent << " seconds.\n\n";
            break;
        }
        case 2: {
            int list1;
            cout << "Enter List: ";
            cin >> list1;
            list1--;
            cout << "Enter value to add to beginning: ";
            cin >> value;

            for (int i = 0; i < value; i++)
            {
                lists[list1].addToEnd(i);
            }

            break;
        }
        case 3: {
            for (int i = 0; i < numLists; i++) {
                int j = i + 1;
                clock_t start = clock();
                lists[i].removeLast();
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "List " << " " << j << " " << "cleared\n" << "Time taken : " << timeSpent << " seconds.\n";
            }
            cout << "\n\n";
            break;
        }
        case 4: {
            for (int i = 0; i < numLists; i++) {
                int j = i + 1;
                clock_t start = clock();
                lists[i].removeFirst();
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "List " << " " << j << " " << "cleared\n" << "Time taken : " << timeSpent << " seconds.\n";
            }
            cout << "\n\n";
            break;
        }
        case 5: {
            for (int i = 0; i < numLists; i++)
            {
                cout << "Enter index for insertion: ";
                cin >> index;
                cout << "Enter value to insert: ";
                cin >> value;
                clock_t start = clock();
                lists[i].insertAtIndex(value, index);
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Inserted at index " << index << ". Time taken: " << timeSpent << " seconds.\n\n";
            }

            break;
        }
        case 6: {
            for (int i = 0; i < numLists; i++)
            {
                cout << "Enter index to get: ";
                cin >> index;
                clock_t start = clock();
                cout << "Value at index " << index << ": " << lists[i].getAtIndex(index) << "\n";
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Get at index " << index << ". Time taken: " << timeSpent << " seconds.\n\n";
            }
            break;
        }
        case 7: {
            for (int i = 0; i < numLists; i++)
            {
                cout << "Enter index to remove: ";
                cin >> index;
                clock_t start = clock();
                lists[i].removeAtIndex(index);
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Removed element at index " << index << ". Time taken: " << timeSpent << " seconds.\n\n";
            }
            break;
        }
        case 8: {
            for (int i = 0; i < numLists; i++)
            {
                cout << "Size of list: " << lists[i].getSize() << "\n\n";
            }
        }
              break;
        case 9: {
            for (int i = 0; i < numLists; i++) {
                int j = i + 1;
                clock_t start = clock();
                lists[i].clear();
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Cleared List" << i << "." << "\nTime taken : " << timeSpent << " seconds.\n\n";
            }
            cout << "\n\n";
            break;
        }
        case 10: {
            for (int i = 0; i < numLists; i++)
            {
                int indexToReplace, newValue;
                cout << "Enter the index to replace: ";
                cin >> indexToReplace;
                cout << "Enter the new value: ";
                cin >> newValue;
                clock_t start = clock();
                lists[i].replaceAtIndex(indexToReplace, newValue);
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "Replaced at index " << indexToReplace << ". Time taken: " << timeSpent << " seconds.\n\n";
            }

            break;
        }
        case 11:
            if (lists[listIndex].isEmpty() == true) cout << "List is empty";
            else cout << "List isn't empty\n\n";
            break;
        case 12: {
            int index = 1;
            for (int i = 0; i < numLists; i++)
            {
                clock_t start = clock();
                lists[i].reverse();
                cout << "List " << index << " reversed\n";
                index++;
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "\nTime taken : " << timeSpent << " seconds.\n\n";
            }

            break;
        }
        case 13: {
            for (int i = 0; i < numLists; i++)
            {
                int list1, list2;
                cout << "Enter List: ";
                cin >> list1;
                list1--;
                cout << "Enter another List: ";
                cin >> list2;
                list2--;
                int index;
                cout << "Enter the index where you want to insert the list: ";
                cin >> index;
                clock_t start = clock();
                lists[list1].insertListAtIndex(lists[list2], index);
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "List " << list1 << "insert to List " << list2 << "at Index " << index << "\nTime taken : " << timeSpent << " seconds.\n\n";
            }
            break;
        }
        case 14: {
            int list1, list2;
            cout << "Enter List: ";
            cin >> list1;
            list1--;
            cout << "Enter another List: ";
            cin >> list2;
            list2--;
            lists[list2].insertListAtEnd(lists[list1]);
            cout << "List inserted at the end." << endl;
            break;
        }
        case 15: {
            int list1, list2;
            cout << "Enter List: ";
            cin >> list1;
            list1--;
            cout << "Enter another List: ";
            cin >> list2;
            list2--;
            lists[list1].insertListAtBeginning(lists[list2]);
            cout << "List inserted at the beginning." << endl;
            break;
        }
        case 16: {
            for (int i = 0; i < numLists; i++)
            {
                int list1, list2;
                cout << "Enter List: ";
                cin >> list1;
                list1--;
                cout << "Enter another List: ";
                cin >> list2;
                list2--;
                clock_t start = clock();
                if (lists[list1].containsList(lists[list2])) {
                    list1++, list2++;
                    cout << "List" << list1 << " " << "contains " << " " << "List" << list2 << ".\n\n";
                }
                else {
                    list1++, list2++;
                    cout << "List" << list1 << " " << "doesn't contains " << " " << "List" << list2 << ".\n\n";
                }
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "\nTime taken : " << timeSpent << " seconds.\n\n";
            }
            break;
        }
        case 17: {
            int list1, list2;
            cout << "Enter List: ";
            cin >> list1;
            list1--;
            cout << "Enter another List: ";
            cin >> list2;
            list2--;
            int index = lists[list1].indexOfList(lists[list2]);
            if (index != -1) {
                list1++, list2++;
                cout << "Last occurrence of List" << " " << list2 << " " << "found in List" << " " << list1 << " " << "at index : " << index << "\n\n";
            }
            else {
                list1++, list2++;
                cout << "Last occurrence of List" << " " << list2 << " " << "not found List" << " " << list1 << "\n\n";
            }
            break;
        }
        case 18: {
            int list1, list2;
            cout << "Enter List: ";
            cin >> list1;
            list1--;
            cout << "Enter another List: ";
            cin >> list2;
            list2--;
            int index = lists[list1].indexOfList(lists[list2]);
            if (index != -1) {
                list1++, list2++;
                cout << "Last occurrence of List" << " " << list2 << " " << "found in List" << " " << list1 << " " << "at index : " << index << "\n\n";
            }
            else {
                list1++, list2++;
                cout << "Last occurrence of List" << " " << list2 << " " << "not found List" << " " << list1 << "\n\n";
            }
            break;
        }
        case 19: {
            for (int i = 0; i < numLists; i++)
            {
                int list1, list2;
                cout << "Enter List: ";
                cin >> list1;
                list1--;
                int index1, index2;

                cout << "Enter the indexes of elements to exchange: ";
                cin >> index1;
                index1--;
                cout << "Enter the indexes of elements to exchange: ";
                cin >> index2;
                index2--;
                clock_t start = clock();
                lists[list1].exchangeElementsByIndex(index1, index2);
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "\nTime taken : " << timeSpent << " seconds.\n\n";
            }

            break;
        }
        case 20: {
            for (int i = 0; i < numLists; i++) {
                int j = i + 1;
                clock_t start = clock();
                lists[i].display();
                clock_t end = clock();
                double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
                cout << "\nList " << " " << j << " " << "Time taken : " << timeSpent << " seconds.\n";
            }
            cout << "\n";
            break;
        }
        case 0:
            exit(0);
        default:
            cout << "Invalid choice.\n\n";
            break;
        }
    }

    delete[] lists;
    return 0;
}
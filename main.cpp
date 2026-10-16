
#include <iostream>
#include <string>
using namespace std;

// Student Information
// Name: Sheikh Muhammad Ansar
// ID: 16902

// Doubly Linked List Node
struct Node
{
    string item;
    Node* next;
    Node* previous;
};

// Doubly Linked List
struct ItemList
{
    Node* head;
    Node* tail;

    ItemList()
    {
        head = NULL;
        tail = NULL;
    }

    void addItem(string name)
    {
        Node* newNode = new Node;

        newNode->item = name;
        newNode->next = NULL;
        newNode->previous = tail;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void displayItems()
    {
        Node* current = head;

        while (current != NULL)
        {
            cout << current->item;

            if (current->next != NULL)
                cout << ", ";

            current = current->next;
        }

        cout << endl;
    }
};

// Order Package
struct OrderPackage
{
    string customer;
    string address;
    unsigned long long distance;
    string unit;
    ItemList items;
};

// Stack for Bag
struct BagStack
{
    OrderPackage* packages[3];
    int top;

    BagStack()
    {
        top = -1;
    }

    bool push(OrderPackage* package)
    {
        if (top == 2)
        {
            cout << "Bag is full!" << endl;
            return false;
        }

        top++;
        packages[top] = package;
        return true;
    }

    OrderPackage* pop()
    {
        if (top == -1)
            return NULL;

        OrderPackage* package = packages[top];
        top--;

        return package;
    }

    bool isEmpty()
    {
        return top == -1;
    }
};

// Queue for Conveyor Belt
struct ConveyorQueue
{
    BagStack bags[3];
    int front;
    int rear;
    int count;

    ConveyorQueue()
    {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool enqueue(BagStack bag)
    {
        if (count == 3)
        {
            cout << "Conveyor queue is full!" << endl;
            return false;
        }

        rear = (rear + 1) % 3;
        bags[rear] = bag;
        count++;

        return true;
    }

    BagStack dequeue()
    {
        BagStack emptyBag;

        if (count == 0)
            return emptyBag;

        BagStack bag = bags[front];
        front = (front + 1) % 3;
        count--;

        return bag;
    }

    bool isEmpty()
    {
        return count == 0;
    }
};

int main()
{
    cout << "========================================" << endl;
    cout << "       RED DEAD REDEMPTION 2" << endl;
    cout << "       WILD WEST DELIVERY SYSTEM" << endl;
    cout << "========================================" << endl;

    cout << "Student: Sheikh Muhammad Ansar" << endl;
    cout << "Student ID: 16902" << endl;

    // Create three order packages
    OrderPackage orders[3];

    // Order Package 1: Arthur Morgan
    orders[0].customer = "Arthur Morgan";
    orders[0].address = "Valentine, New Hanover";
    orders[0].distance = 900;
    orders[0].unit = "meters";

    orders[0].items.addItem("Repeater Ammo");
    orders[0].items.addItem("Health Tonic");
    orders[0].items.addItem("Horse Brush");

    // Order Package 2: Sheikh Muhammad Ansar
    orders[1].customer = "Sheikh Muhammad Ansar";
    orders[1].address = "Camp at Horseshoe Overlook";
    orders[1].distance = 700;
    orders[1].unit = "meters";

    orders[1].items.addItem("Legendary Pelt");
    orders[1].items.addItem("Fishing Rod");
    orders[1].items.addItem("Coffee");

    // Order Package 3: A mysterious stranger
    orders[2].customer = "Mysterious Stranger";
    orders[2].address = "Beyond the Observable Universe";
    orders[2].distance = 18446744073709551615ULL;
    orders[2].unit = "light-years";

    orders[2].items.addItem("Dinosaur Bone");
    orders[2].items.addItem("Rare Revolver");
    orders[2].items.addItem("Gold Bar");

    // Display original orders
    cout << "\n========== ORIGINAL ORDERS ==========" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "\nOrder Package " << i + 1 << endl;
        cout << "Customer: " << orders[i].customer << endl;
        cout << "Address: " << orders[i].address << endl;
        cout << "Distance: " << orders[i].distance
             << " " << orders[i].unit << endl;

        cout << "Items: ";
        orders[i].items.displayItems();
    }

    // Sort packages by descending distance
    // Bubble Sort
    OrderPackage* sorted[3];

    for (int i = 0; i < 3; i++)
    {
        sorted[i] = &orders[i];
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2 - i; j++)
        {
            if (sorted[j]->distance < sorted[j + 1]->distance)
            {
                OrderPackage* temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    cout << "\n========== SORTED PACKAGES ==========" << endl;
    cout << "(Descending distance)" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "Order Package ";

        if (sorted[i] == &orders[0])
            cout << 1;
        else if (sorted[i] == &orders[1])
            cout << 2;
        else
            cout << 3;

        cout << " - " << sorted[i]->customer;
        cout << " - " << sorted[i]->distance;
        cout << " " << sorted[i]->unit << endl;
    }

    // Push sorted packages into a bag stack
    BagStack bag1;

    for (int i = 0; i < 3; i++)
    {
        bag1.push(sorted[i]);
    }

    cout << "\n========== BAG STACK ==========" << endl;
    cout << "All three packages added to Bag 1." << endl;
    cout << "Stack capacity: 3 packages" << endl;

    // Add the bag to the conveyor queue
    ConveyorQueue conveyor;

    conveyor.enqueue(bag1);

    cout << "\n========== CONVEYOR BELT ==========" << endl;
    cout << "Bag 1 added to the conveyor queue." << endl;

    // Dequeue the bag and deliver packages using LIFO
    cout << "\n========== DELIVERY PROCESS ==========" << endl;

    int deliveryNumber = 1;

    while (!conveyor.isEmpty())
    {
        BagStack currentBag = conveyor.dequeue();

        cout << "\nDriver collected a bag from the queue." << endl;

        while (!currentBag.isEmpty())
        {
            OrderPackage* package = currentBag.pop();

            cout << "\nDelivery " << deliveryNumber << endl;
            cout << "Customer: " << package->customer << endl;
            cout << "Address: " << package->address << endl;
            cout << "Distance: " << package->distance
                 << " " << package->unit << endl;

            cout << "Items delivered: ";
            package->items.displayItems();

            cout << "Status: Delivered successfully!" << endl;

            deliveryNumber++;
        }
    }

    cout << "\n========================================" << endl;
    cout << "All deliveries completed!" << endl;
    cout << "Good work, partner!" << endl;
    cout << "========================================" << endl;

    return 0;
}

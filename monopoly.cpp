#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Node {
string propertyName;
int cost;
// propertyOwner: 0 - No owner, 1 - P1, 2 - P2
int propertyOwner;
Node* next;

};
/*the nodeCount position allows me to make it a global variable to prevent applying 
the same argument for the append and remove functions*/
int nodeCount = 12;
int playerTurn = 0;



void append(Node* &head, Node* &tail, string propertyName, int cost, int propertyOwner){
    tail->next = new Node{propertyName, cost, propertyOwner, nullptr};
    tail = tail->next;
    tail->next = head;
    ++nodeCount;
}
void remove(Node* &head, Node* &tail){
    Node* current = head;
    for(int i = 0; i < nodeCount; ++i){
        if(current->next == tail){
            --nodeCount;
            current->next = nullptr;
            delete tail;
            tail = current;
            tail->next = head;
            break;
        }
        current = current->next;
    }

}
Node* search(Node* head, string propertyName){
    Node* current = head;
    for(int i = 0; i < nodeCount; ++i){
        if(current->propertyName == propertyName){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void traverse(Node* &current, int diceRoll){
    for(int j = 0; j < diceRoll; ++j){
        current = current->next;
    }
}

void print(Node* current, int diceRoll){
    // Depending on the property owner number, we describe the player's action 
    cout << "Player " << playerTurn + 1 << "'s turn, " << "Dice Roll: " << diceRoll << "\n" ;
    if(current->propertyOwner == 0){
        cout << "Player " << playerTurn + 1 << " has bought " << current->propertyName << " for $" << current->cost << "!\n\n";
        current->propertyOwner = playerTurn + 1;
    }
    else if(current->propertyName == "GO"){
        cout << "Player " << playerTurn + 1 << " landed on Go!\n\n"; 
    }
    else{
        cout << "Player " << current->propertyOwner << " owns " << current->propertyName << "!\n\n";
    }


}

int main(){
    srand(time(0));

    Node* head = new Node{"GO", 0, -1, nullptr};
    Node* prop1 = new Node{"Oriental Avenue", 100, 0, nullptr};
    Node* prop2 = new Node{"Mediterranean Avenue", 60, 0, nullptr};
    Node* prop3 = new Node{"Virginia Avenue", 160, 0, nullptr};
    Node* prop4 = new Node{"Tennessee Avenue", 180, 0, nullptr};
    Node* prop5 = new Node{"Illinois Avenue", 240, 0, nullptr};
    Node* prop6 = new Node{"Ventnor Avenue", 260, 0, nullptr};
    Node* prop7 = new Node{"Pacific Avenue", 300, 0, nullptr};
    Node* prop8 = new Node{"Boardwalk", 400, 0, nullptr};
    Node* prop9 = new Node{"B. & O. Railroad", 200, 0, nullptr};
    Node* prop10 = new Node{"Short Line Railroad", 200, 0, nullptr};
    Node* tail = new Node{"Water Works", 150, 0, nullptr};

    head->next = prop1;
    prop1->next = prop2;
    prop2->next = prop3;
    prop3->next = prop4;
    prop4->next = prop5;
    prop5->next = prop6;
    prop6->next = prop7;
    prop7->next = prop8;
    prop8->next = prop9;
    prop9->next = prop10;
    prop10->next = tail;

    // Completes the circular link back to GO
    tail->next = head;

    /*Allows to search property by name to attain other data such 
    as the next pointer, cost, and property owner*/ 

    Node* targetNode = search(head, "Water Works");
    append(head, tail, "Indiana Avenue", 220, 0);
    append(head, tail, "St. James Place", 180, 0);
    append(head, tail, "Atlantic Avenue", 260, 0);
    append(head, tail, "Marvin Gardens", 280, 0);
    
    remove(head, tail);
    remove(head, tail);
    
    //Handles the total turn number and the player's specific turn
    int totalTurns = 20;
    int diceRoll = 0;
    //Different pointers allow us to traverse with each player without collision
    Node* current_p1 = head;
    Node* current_p2 = head;
    for(int i = 0 ; i < totalTurns; ++i){
        diceRoll = rand() % 6 + 1;
        playerTurn = playerTurn % 2;

        if(playerTurn == 0){
             traverse(current_p1, diceRoll);
             print(current_p1, diceRoll);
        }
        else{
            traverse(current_p2, diceRoll);
            print(current_p2, diceRoll);
        }
       ++playerTurn;
    }
   
    return 0;
    

}
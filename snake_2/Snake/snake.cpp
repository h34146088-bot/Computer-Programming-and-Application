#include "snake.h"
#include <stdlib.h>

Snake::Snake(Console &consoleRef, int x, int y, Direction direction, int bodyCharValue) : console(consoleRef), bodyChar(bodyCharValue) {
    // Create snake's head at the specified position (clamp to non-negative)
    head = new Node;
    head->x = x;
    head->y = y;
    if(head->x < 0)
        head->x = 0;
    if(head->y < 0)
        head->y = 0;
    head->prevNode = NULL;
    tail = head;

    dir = direction;

    maxX = 0;
    maxY = 0;
    console.MvAddCh(y, x, bodyChar);
}

void Snake::DeleteSnake() {
    Node *current = head;

    while(current != NULL) {
        Node *temp = current;
        current = current->prevNode;
        delete temp;
    }

    head = tail = NULL;
}

void Snake::SetDir(Direction newDir) {
    dir = newDir;
}

void Snake::RemoveAtTail() {
    if(head == tail) {
        delete tail;
        head = tail = NULL;
        return;
    }

    Node *current = head;
    while(current->prevNode != tail) {
        current = current->prevNode;
    }

    delete tail;
    tail = current;
    tail->prevNode = NULL;
}

void Snake::InsertAtHead(Node *newHead) {
    newHead->prevNode = head;
    head = newHead;
}

bool Snake::MoveSnake() {
    Node *newHead = new Node;

    newHead->x = head->x;
    newHead->y = head->y;
    newHead->prevNode = NULL;

    // Compute position of the new head
    switch(dir) {
    case UP:
        newHead->y--;
        break;
    case DOWN:
        newHead->y++;
        break;
    case LEFT:
        newHead->x--;
        break;
    case RIGHT:
        newHead->x++;
        break;
    }

    // Check if we've hit the wall
    if(newHead->x < 0 || newHead->x >= maxX || newHead->y < 0 || newHead->y >= maxY) {
        delete newHead;
        return false;
    }

    // Draw the new head
    InsertAtHead(newHead);
    console.MvAddCh(newHead->y, newHead->x, bodyChar);

    // Always remove the tail (food is handled separately in Game class)
    console.MvAddCh(tail->y, tail->x, ' ');
    RemoveAtTail();

    return true;
}

void Snake::SetMapSize(int x, int y) {
    maxX = x;
    maxY = y;
}

bool Snake::AtTarget(int targetX, int targetY) {
    return head->x == targetX && head->y == targetY;
}

bool Snake::IsOutOfBounds() {
    return head->x < 0 || head->x >= maxX || head->y < 0 || head->y >= maxY;
}

void Snake::Grow() {
    // The head is already added in MoveSnake(), we just need to not remove the tail
    // But MoveSnake() already removes the tail, so we need to add it back
    // This is handled by calling InsertAtHead with a new node for the tail
    Node *newTail = new Node;
    newTail->x = tail->x;
    newTail->y = tail->y;
    newTail->prevNode = NULL;

    Node *current = head;
    while(current->prevNode != NULL) {
        current = current->prevNode;
    }
    current->prevNode = newTail;
    tail = newTail;

    console.MvAddCh(tail->y, tail->x, bodyChar);
}

bool Snake::HitBody(int x, int y) {

    if(head == NULL)
        return false;

    Node *current = head->prevNode;

    while(current != NULL) {
        if(current->x == x && current->y == y) {
            return true;
        }

        current = current->prevNode;
    }

    return false;
}

int Snake::GetHeadX() {
    return head->x;
}

int Snake::GetHeadY() {
    return head->y;
}

Snake::~Snake() {
    DeleteSnake();
}

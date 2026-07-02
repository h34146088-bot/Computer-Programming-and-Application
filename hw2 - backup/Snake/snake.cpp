#include "snake.h"
#include "simple_console.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
int Snake::targetX = 0;
int Snake::targetY = 0;
Snake::Snake(int x, int y, Direction direction) {
    // Create snake's head at the specified position
    head = new Node;
    head->x = x;
    head->y = y;
    head->prevNode = NULL;
    tail = head;

    dir = direction;

    maxX = 0;
    maxY = 0;
    mvaddch(y, x, '*');
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
    if(newHead->x < 0 || newHead->x >= maxX || newHead->y < 0 || newHead->y >= maxY)
        return false;

    // Draw the new head
    InsertAtHead(newHead);
    mvaddch(newHead->y, newHead->x, '*');

    // Clear the tail if we haven't reached the target
    if(targetX != newHead->x || targetY != newHead->y) {
        mvaddch(tail->y, tail->x, ' ');
        RemoveAtTail();
    } else {
        GenerateNewTarget();
    }

    return true;
}

void Snake::GenerateNewTarget() {
    targetX = rand() % maxX;
    targetY = rand() % maxY;

    // Should check to make sure the new target does not overlap with the snake body
    mvaddch(targetY, targetX, '$');
}

void Snake::SetMapSize(int x, int y) {
    maxX = x;
    maxY = y;
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

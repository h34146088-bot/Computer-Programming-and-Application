#ifndef SNAKE_H
#define SNAKE_H

#include "simple_console.h"

class Snake {
  public:
    enum Direction {
        // UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    Snake(Console &console, int, int, Direction, int bodyChar);
    ~Snake();
    void SetDir(Direction newDir);
    bool MoveSnake();
    void SetMapSize(int x, int y);
    bool HitBody(int x, int y);
    bool AtTarget(int targetX, int targetY);
    bool IsOutOfBounds();
    void Grow();
    int GetHeadX();
    int GetHeadY();

  private:
    struct Node {
        int x;
        int y;
        Node *prevNode;
    };

    Console &console;
    int bodyChar;
    int maxX;
    int maxY;
    Node *head;
    Node *tail;
    Direction dir;

    void DeleteSnake();
    void RemoveAtTail();
    void InsertAtHead(Node *newHead);
};

#endif
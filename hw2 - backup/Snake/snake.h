#ifndef SNAKE_H
#define SNAKE_H

class Snake {
  public:
    enum Direction {
        // UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    struct Node {
        int x;
        int y;
        Node *prevNode;
    };
    Snake(int, int, Direction);
    void DeleteSnake();
    void RemoveAtTail();
    void InsertAtHead(Node *newHead);
    void GenerateNewTarget();
    void SetDir(Direction newDir);
    void DrawSnake();
    bool MoveSnake();
    void SetMapSize(int x, int y);
    bool HitBody(int x, int y);
    int GetHeadX();
    int GetHeadY();
    ~Snake();

  private:
    static int targetX;
    static int targetY;
    int maxX;
    int maxY;
    Node *head;
    Node *tail;
    Direction dir;
};

#endif
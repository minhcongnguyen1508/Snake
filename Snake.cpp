#include "Snake.h"
#include "Game.h"
#include <iostream>

Snake::Snake(Game& _game, Position start)
    : head(new SnakeNode(start)), tail(head), game(_game), cherry(0)
{
    // Using Game.snakeMoveTo method to move Snake to start position;
    game.snakeMoveTo(start);    
}

// DO NOT CHANGE METHOD
Snake::~Snake()
{
    for (SnakeNode* p = tail; p != nullptr; ) {
        SnakeNode* nextNode = p->next;
        delete p;
        p = nextNode;
    }
}

// DO NOT CHANGE METHOD
vector<Position> Snake::getPositions() const
{
    vector<Position> res;
    for (SnakeNode* p = tail; p != nullptr; p = p->next)
        res.push_back(p->position);
    return res;
}

void Snake::growAtFront(Position newPosition)
{
    // head of snake grow at new position
    // head->next = ...
    // head = head->next;
	head->next = new SnakeNode(newPosition);
	head = head->next;
}

void Snake::slideTo(Position newPosition)
{
	if (tail->next == nullptr) { // snake has only one node
        // position is assigned by new position.
		tail->position = newPosition;
	}
	else {
		SnakeNode *oldTailNode = tail;
		//cut the old tail off the snake
		tail = tail->next;
		oldTailNode->next = nullptr;
		
		// move it to the head of the snake
		oldTailNode->position = newPosition;
		head->next = oldTailNode;

		head = oldTailNode;
	}
}

void Snake::eatCherry()
{
    // if snake eat cherry, number of cherries will increase one
	cherry++;
}

void Snake::move(Direction direction)
{
    Position newPosition = head->position.move(direction);

    // Using snakeMoveTo method to update game with newPosition
    game.snakeMoveTo(newPosition);
    
    // If gameOver, return ; 
    if (game.isGameOver()) return;

    // If cherry > 0, cherry descrease one and growAtFront() with newPosition
    if (cherry > 0) {
        cherry--;
        growAtFront(newPosition);
    } else {
    	game.snakeLeave(tail->position);
        // SlideTo() newPosition
        slideTo(newPosition);        
    }
}

// DO NOT CHANGE METHOD
int Snake::getNumCherry(){
    return cherry;
}

// DO NOT CHANGE METHOD
SnakeNode* Snake::getHead(){
    return head;
}

// DO NOT CHANGE METHOD
SnakeNode* Snake::getTail(){
    return tail;
}
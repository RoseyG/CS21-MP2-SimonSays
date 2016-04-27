#include"move.h"
#include<iostream>

/**
This constructs a move object.
**/
Move::Move(){
	value = 0;
	next = NULL;
}
/**
This sets the value for a move. The value indicates the button the moves corresponds to. 1 is for the green button, 2 is for the red button, 3 is for the yellow button and 4 is for the blue button.
**/
void Move::setValue(int x){
	value = x;
}
/**
This sets the next move.
**/
void Move::setNext(Move* n_move){
	next = n_move;
}
/**
This returns the value of the move.
**/
int Move::getValue(){
	return value;
}
/**
This returns the next move.
**/
Move* Move::getNext(){
	return next;
}
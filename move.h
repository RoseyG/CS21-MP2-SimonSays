#ifndef __move__
#define __move__

class Move{
	private:
	int value;
	Move *next;
	public:
	Move();
	void setValue(int);
	void setNext(Move*);
	int getValue();
	Move *getNext();
};

#endif
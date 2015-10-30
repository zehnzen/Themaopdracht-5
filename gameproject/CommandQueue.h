//File CommandQueue.h

#ifndef _COMMANDQUEUE_H
#define _COMMANDQUEUE_H

#include <queue>
#include "Command.h"

class CommandQueue {
public:
	void push(const Command& command);
	Command pop();
	bool isEmpty() const;

private:
	std::queue<Command> cQueue;
};



#endif
//File CommandQueue.cpp

#include "CommandQueue.h"

void CommandQueue::push(const Command & command) {
	cQueue.push(command);
}

Command CommandQueue::pop() {
	Command command = cQueue.back();
	cQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const {
	return (cQueue.empty() ? true : false);
}
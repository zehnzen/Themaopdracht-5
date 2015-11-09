//File CommandQueue.cpp

#include "CommandQueue.h"

/**********************************************************************************************//**
 * @fn	void CommandQueue::push(const Command & command)
 *
 * @brief	Pushes an object onto this stack.
 *
 * @param	command	The command to push.
 **************************************************************************************************/

void CommandQueue::push(const Command & command) {
	cQueue.push(command);
}

/**********************************************************************************************//**
 * @fn	Command CommandQueue::pop()
 *
 * @brief	Removes and returns the top-of-stack object.
 *
 * @return	The previous top-of-stack object.
 **************************************************************************************************/

Command CommandQueue::pop() {
	Command command = cQueue.back();
	cQueue.pop();
	return command;
}

/**********************************************************************************************//**
 * @fn	bool CommandQueue::isEmpty() const
 *
 * @brief	Query if this object is empty.
 *
 * @return	true if empty, false if not.
 **************************************************************************************************/

bool CommandQueue::isEmpty() const {
	return (cQueue.empty() ? true : false);
}
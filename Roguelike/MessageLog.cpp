#include "MessageLog.h"


MessageLog::MessageLog()
{
	turnCounter = 0;
}


MessageLog::~MessageLog()
{
}

void MessageLog::addToLog(std::string inMessage, int inTurn, int inColor)
{
	log.push_back(Message(inMessage, inTurn, inColor));
}

std::vector<Message>& MessageLog::getLog()
{
	return log;
}

int MessageLog::getTurnCounter()
{
	return turnCounter;
}

void MessageLog::incTurnCounter(int amt)
{
	turnCounter += amt;
}
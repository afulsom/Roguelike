#include "stdafx.h"
#include "Message.h"

class MessageLog
{
private:
	std::vector<Message> log;
	int turnCounter;
public:
	MessageLog();
	~MessageLog();
	void addToLog(std::string, int, int);
	std::vector<Message>& getLog();
	int getTurnCounter();
	void incTurnCounter(int);
};


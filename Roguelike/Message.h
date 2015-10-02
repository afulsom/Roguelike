#include "stdafx.h"


class Message
{
private:
	std::string text;
	int turn;
	int color;
public:
	Message();
	Message(std::string, int, int);
	~Message();
	std::string getText();
	int getTurn();
	int getColor();
};


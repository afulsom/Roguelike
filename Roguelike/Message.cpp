#include "Message.h"


Message::Message()
{
}

Message::Message(std::string inText, int inTurn, int inColor)
{
	text = inText;
	turn = inTurn;
	color = inColor;
}

Message::~Message()
{
}


std::string Message::getText()
{
	return text;
}

int Message::getTurn()
{
	return turn;
}

int Message::getColor()
{
	return color;
}
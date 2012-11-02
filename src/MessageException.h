#ifndef MESSAGEEXCEPTION_H
#define MESSAGEEXCEPTION_H

#include <string>

enum MessageExceptionType
{
	INFO,
	WARNING,
	ERROR
};

class MessageException : public std::exception
{
private:
	std::string m_message;
	MessageExceptionType m_type;
public:
	MessageException(std::string message, MessageExceptionType type);
	~MessageException() throw();
	MessageExceptionType getType() const;
	const std::string& getMessage() const;
};

#endif // MESSAGEEXCEPTION_H

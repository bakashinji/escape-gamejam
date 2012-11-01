#include "MessageException.h"

MessageException::MessageException(std::string message, MessageExceptionType type) :
	m_message(message)
{
}

MessageException::~MessageException() throw()
{
}

MessageExceptionType MessageException::getType() const
{
	return m_type;
}

const std::string & MessageException::getMessage() const
{
	return m_message;
}

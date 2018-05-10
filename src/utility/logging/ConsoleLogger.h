#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "Logger.h"
#include "LogMessage.h"

class ConsoleLogger: public Logger
{
public:
	ConsoleLogger();
	~ConsoleLogger();

private:
	virtual void logInfo(const LogMessage& message);
	virtual void logWarning(const LogMessage& message);
	virtual void logError(const LogMessage& message);

	void logMessage(const std::string& type, const LogMessage& message);
};

#endif // CONSOLE_LOGGER_H

//
// LogStream.h
//
// Library: Foundation
// Package: Logging
// Module:  LogStream
//
// Definition of the LogStream class.
//
// Copyright (c) 2006-2007, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_LogStream_INCLUDED
#define Foundation_LogStream_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Logger.h"
#include "Poco/UnbufferedStreamBuf.h"
#include <istream>


namespace Poco {


class Foundation_API LogStreamBuf: public UnbufferedStreamBuf
	/// This class implements a streambuf interface
	/// to a Logger.
	///
	/// The streambuf appends all characters written to it
	/// to a string. As soon as a CR or LF (std::endl) is written,
	/// the string is sent to the Logger, with the set
	/// priority.
{
public:
	LogStreamBuf(Logger& logger, Message::Priority priority, std::size_t bufferCapacity = 0);
		/// Creates the LogStream.

	~LogStreamBuf() override;
	/// Destroys the LogStream.

	void setPriority(Message::Priority priority);
		/// Sets the priority for log messages.

	Message::Priority getPriority() const;
		/// Returns the priority for log messages.

	Logger& logger() const;
		/// Returns a reference to the Logger.

	std::size_t capacity() const;
		/// Returns the internal message buffer capacity.

	void reserve(std::size_t capacity);
		/// Sets the capacity of the internal message buffer to the given size.

private:
	int writeToDevice(char c) override;

private:
	Logger&           _logger;
	Message::Priority _priority;
	std::string       _message;
};


class Foundation_API LogIOS: public virtual std::ios
	/// The base class for LogStream.
	///
	/// This class is needed to ensure the correct initialization
	/// order of the stream buffer and base classes.
{
public:
	LogIOS(Logger& logger, Message::Priority priority, std::size_t bufferCapacity = 0);
	~LogIOS() override;
	LogStreamBuf* rdbuf();

protected:
	LogStreamBuf _buf;
};


class Foundation_API LogStream: public LogIOS, public std::ostream
	/// This class implements an ostream interface
	/// to a Logger.
	///
	/// The stream's buffer appends all characters written to it
	/// to a string. As soon as a CR or LF (std::endl) is written,
	/// the string is sent to the Logger, with the current
	/// priority.
	///
	/// Usage example:
	///     LogStream ls(someLogger);
	///     ls << "Some informational message" << std::endl;
	///     ls.error() << "Some error message" << std::endl;
{
public:
	static const std::size_t DEFAULT_BUFFER_CAPACITY = 255;

	LogStream(Logger& logger, Message::Priority priority = Message::PRIO_INFORMATION, std::size_t bufferCapacity = DEFAULT_BUFFER_CAPACITY);
		/// Creates the LogStream, using the given logger and priority.

	LogStream(const std::string& loggerName, Message::Priority priority = Message::PRIO_INFORMATION, std::size_t bufferCapacity = DEFAULT_BUFFER_CAPACITY);
		/// Creates the LogStream, using the logger identified
		/// by loggerName, and sets the priority.

	~LogStream() override;
	/// Destroys the LogStream.

	LogStream& fatal();
		/// Sets the priority for log messages to Message::PRIO_FATAL.

	LogStream& fatal(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_FATAL
		/// and writes the given message.

	LogStream& critical();
		/// Sets the priority for log messages to Message::PRIO_CRITICAL.

	LogStream& critical(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_CRITICAL
		/// and writes the given message.

	LogStream& error();
		/// Sets the priority for log messages to Message::PRIO_ERROR.

	LogStream& error(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_ERROR
		/// and writes the given message.

	LogStream& warning();
		/// Sets the priority for log messages to Message::PRIO_WARNING.

	LogStream& warning(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_WARNING
		/// and writes the given message.

	LogStream& notice();
		/// Sets the priority for log messages to Message::PRIO_NOTICE.

	LogStream& notice(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_NOTICE
		/// and writes the given message.

	LogStream& information();
		/// Sets the priority for log messages to Message::PRIO_INFORMATION.

	LogStream& information(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_INFORMATION
		/// and writes the given message.

	LogStream& debug();
		/// Sets the priority for log messages to Message::PRIO_DEBUG.

	LogStream& debug(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_DEBUG
		/// and writes the given message.

	LogStream& trace();
		/// Sets the priority for log messages to Message::PRIO_TRACE.

	LogStream& trace(const std::string& message);
		/// Sets the priority for log messages to Message::PRIO_TRACE
		/// and writes the given message.

	LogStream& priority(Message::Priority priority);
		/// Sets the priority for log messages.
};


//
// inlines
//
inline std::size_t LogStreamBuf::capacity() const
{
	return _message.capacity();
}


inline Message::Priority LogStreamBuf::getPriority() const
{
	return _priority;
}


inline Logger& LogStreamBuf::logger() const
{
	return _logger;
}


} // namespace Poco


#endif // Foundation_LogStream_INCLUDED

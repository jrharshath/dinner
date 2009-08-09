#ifndef ERROR_H
#define ERROR_H

#include <QString>
#include "Error.h"
#include "ErrorCode.h"

class Error
{
public:
	Error(ErrorCode code, QString desc);
	ErrorCode getCode() const;
	QString getDescription() const;
protected:
	ErrorCode code;
	QString description;
};

#endif // ERROR_H

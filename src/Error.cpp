#include "Error.h"

Error::Error(ErrorCode code, QString desc) : code(code), description(desc) {
}

ErrorCode Error::getCode() const {
	return code;
}

QString Error::getDescription() const {
	return description;
}

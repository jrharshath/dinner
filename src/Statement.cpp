#include "Statement.h"

Statement::Statement(StatementType t, QList<void*>* a) : type(t), args(a) {
}

StatementType Statement::getType() {
	return type;
}

QList<void*>* Statement::getArgs() {
	return args;
}


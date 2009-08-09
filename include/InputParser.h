#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <QTextStream>
#include "Statement.h"
#include "Error.h"

class InputParser
{
public:
	InputParser(QTextStream &in);
	QList<Statement*>* parse() throw(Error);
private:
	QTextStream &in;
};

#endif // INPUTPARSER_H

#ifndef STATEMENTPARSER_H
#define STATEMENTPARSER_H

#include <QObject>
#include <QString>
#include "Statement.h"
#include "Error.h"

class StatementParser : public QObject {
public:
	StatementParser();
	Statement* parse(QString* str) throw(Error);
protected:
};

#endif

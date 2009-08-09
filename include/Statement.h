#ifndef STATEMENT_H
#define STATEMENT_H

#include <QString>
#include <QList>

enum StatementType {
	PERSON,
	EXPENSE,
	PAID,
	UNKNOWN
};

class Statement
{
public:
    Statement(StatementType type, QList<void*>* args);
	StatementType getType();
	QList<void*>* getArgs();
protected:
	StatementType   type;
	QList<void*>* args;
};

#endif // STATEMENT_H

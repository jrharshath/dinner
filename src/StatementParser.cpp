#include "StatementParser.h"
#include <QTextStream>
#include <QList>
#include <QStringList>
#include <QRegExp>

StatementParser::StatementParser() {}

Statement* StatementParser::parse(QString* str) throw(Error) {
	if( str->isEmpty() ) return 0;
	QTextStream input(str);
	QString token;

	QList<void*>* args = new QList<void*>();

	input >> token;
	if( token=="Person" ) {
		StatementType type = PERSON;
		QString* name = new QString();
		input >> *name;
		(*args) << name;
		return new Statement(type, args);
	} else if( token=="Expense" ) {
		StatementType type = EXPENSE;
		QString restOfLine = input.readAll();
		QStringList list = restOfLine.split(QRegExp("[,\\[\\]\\ ]"), QString::SkipEmptyParts);
		QStringListIterator iter(list);
		while(iter.hasNext())
			(*args) << new QString(iter.next());
		return new Statement(type, args);

	} else if( token=="Paid" ) {
		StatementType type = PAID;
		QString *name = new QString();
		QString* amount = new QString();

		input >> (*name) >> (*amount);
		(*args) << name << amount;

		return new Statement(type,args);
	} else if( token=="#" ) {
		return 0;
	} else {
		throw Error(SYNTAX, "\'"+token+"\'" + tr(" is not a recognized statement!"));
		return 0;
	}
	return 0;
}


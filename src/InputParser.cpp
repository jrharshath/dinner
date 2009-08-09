#include "InputParser.h"
#include "StatementParser.h"

InputParser::InputParser(QTextStream &input) : in(input) {
}

QList<Statement*>* InputParser::parse() throw(Error) {
	QList<Statement*>* statements = new QList<Statement*>();
	StatementParser parser;

	while(true) {
		QString line = in.readLine();
		if( in.atEnd() ) break;
		if( line.isNull() )
			break;
		try {
			Statement* st = parser.parse(&line);
			if( st==0 ) continue;
			(*statements) << st;
		} catch (Error e) {
			throw e;
		}
	}
		
	return statements;
}

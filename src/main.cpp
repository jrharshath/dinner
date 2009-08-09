#include <QStringList>
#include <QTextStream>
#include <QSet>
#include <QSetIterator>
#include <QHash>

#include "InputParser.h"
#include "Statement.h"
#include "Error.h"

void displayError(const Error &e, QTextStream &out) {
	out << "Error occurred:\n"
	    << "Error type: " << ErrorTable[e.getCode()] << '\n'
		<< "Error description: " << e.getDescription() << '\n';
}
Error createPersonDoesNotExistError(QString name) {
	return Error(SEMANTIC, "Person named '"+name+"' does not exist!");
}
Error createInvalidFloatError(QString val) {
	return Error(SYNTAX, "Value '"+val+"' is not a valid floating point number!");
}
void dumpData(QSet<QString> people, QHash<QString,float> expenses, QHash<QString,float> paid, QTextStream& out);
int main() {
	QTextStream out(stdout);
	QTextStream in(stdin);
	QTextStream err(stderr);

	QSet<QString> people;
	QHash<QString, float> expenses;
	QHash<QString, float> paid;
	float totalExpense=0.0;
	float totalPaid=0.0;
	
	InputParser parser(in);
	QList<Statement*>* statements = 0;
	try {
		statements = parser.parse();
	} catch( Error e ) {
		displayError(e, err);
		return -1;
	}

	QListIterator<Statement*> iterator(*statements);
	QList<void*>* args;
	QString name;
	QStringList names;
	QString amountAsString;
	float amount;
	bool ok, allPeople;
	int i, size;
	while( iterator.hasNext() ) {
		Statement* currentStatement = iterator.next();
		args = currentStatement->getArgs();
		switch( currentStatement->getType() ) {
		case PERSON:
			name = QString( *((QString*)args->at(0)) );
			if( people.contains(name) )
				break;
			people << name;
			expenses[name] = 0.0;
			paid[name] = 0.0;
			break;
		case EXPENSE:
			allPeople = false;
			names = QList<QString>();
			size=args->size();
			for( i=0; i<size-1 ; i++ ) {
				name = QString( *((QString*)args->at(i)) );
				if( name=="*" ) {
					allPeople = true;
					break;
				}
				if( !people.contains(name) ) {
					displayError( createPersonDoesNotExistError(name), err );
					return -1;
				}
				names << name;
			}
			if( allPeople ) {
				QSetIterator<QString> iter(people);
				while(iter.hasNext()) {
					name = iter.next();
					if( !names.contains(name) )
						names << name;
				}
			}
			amountAsString = QString( *((QString*)args->at(size-1)) );
			ok = true;
			amount = amountAsString.toFloat(&ok);
			if( !ok ) {
				displayError( createInvalidFloatError(amountAsString), err );
				return -1;
			}
			// all is fine now, proceed
			totalExpense += amount;
			amount /= names.size();
			size = names.size();
			for( i=0; i<size; i++ ) {
				name = names.at(i);
				expenses[ name ] = expenses[ name ] + amount;
			}
			break;
		case PAID:
			name = QString( *((QString*)args->at(0)) );
			if( !people.contains(name) ) {
				displayError( createPersonDoesNotExistError(name), err );
				return -1;
			}
			amountAsString = QString( *((QString*)args->at(1)) );
			ok = true;
			amount = amountAsString.toFloat(&ok);
			if( !ok ) {
				displayError( createInvalidFloatError(amountAsString), err );
				return -1;
			}
			// all fine, proceed
			paid[name] = paid[name] + amount;
			totalPaid += amount;

		break;
		case UNKNOWN:
			err << "Unexpected situation: UNKNOWN type of statement appearred!";
		}
	}

	if( totalExpense != totalPaid ) {
		displayError( Error(SEMANTIC, QString("Records are inconsistent: ")+
		                              "Total expense("+totalExpense+") "+
		                              "does not match up with total paid amount("+totalPaid+")!" ), err );
		return -1;
	}
	
	out << "TotalExpense " << totalExpense << '\n' 
	    << "TotalPaid " << totalPaid    << '\n'
		<< '\n';

	QSetIterator<QString> peopleIter(people);
	float balances=0.0;
	while( peopleIter.hasNext() ) {
		name = peopleIter.next();
		float diff = paid[name] - expenses[name];
		balances += diff;
		out << name << ' '
		    << expenses[name] << ' '
			<< paid[name] << ' '
		    << diff
		    << '\n';
	}

	out << '\n' << "roundoff " << balances << '\n';

	return 0;
}


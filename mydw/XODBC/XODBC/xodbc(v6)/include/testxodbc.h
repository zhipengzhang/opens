#include <xodbc/XODBCDataSource.h>
#include <xodbc/XODBCRecordset.h>
#include <iostream>

#pragma warning(disable:4786)

using namespace xodbc;
using namespace std;


void testXODBCDatabase();
 

void testXODBCRecordset();
void printVariant(XDBVariant varValue);

void printWChar(const wchar_t * wstr);

void testSetpos();

void testXODBCDataSource();

void testDBType();

void testSQLType();
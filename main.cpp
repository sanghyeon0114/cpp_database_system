#include "database.h"
#include <iostream>

using namespace std;


// test code.
int main() {
    Database db;
    init(db);
    
    int *a = new int; *a = 11;
    string *b = new string; *b = "Hello";
    double *c = new double; *c = 33.33;

    add(db, create(INT, "first", a));
    add(db, create(STRING, "second", b));
    add(db, create(DOUBLE, "third", c));
    
    int *d = new int; *d = 11111;
    string *e = new string; *e = "World";
    double *f = new double; *f = 123.12;
    add(db, create(INT, "third", d));

    cout << "-----------db------------" << endl;
    list(db);
    cout << "-------------------------" << endl;
    cout << "Entry size: " << db.size << endl;

    string key = "second";
    remove(db, key);
    key = "third";
    remove(db, key);
    key = "first";
    remove(db, key);

    cout << "-----------db------------" << endl;
    list(db);
    cout << "-------------------------" << endl;
    cout << "Entry size: " << db.size << endl;

    destroy(db);
    return 0;
}
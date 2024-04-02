#include "database.h"
#include <iostream>

using namespace std;

void command_list(Database &database) {
    list(database);
}

Array *makeArray() {
    string inputArrayType;
    cout << "type (int, double, string, array): ";
    cin >> inputArrayType;

    Type type;
    if(inputArrayType.compare("int") == 0) {
        type = INT;
    } else if(inputArrayType.compare("double") == 0) {
        type = DOUBLE;
    } else if(inputArrayType.compare("string") == 0) {
        type = STRING;
    } else if(inputArrayType.compare("array") == 0) {
        type = ARRAY;
    } else {
        cout << "invalid type" << endl;
        return nullptr;
    }

    int size;
    cout << "size: ";
    cin >> size;

    Array *array = new Array;
    array->size = size;
    array->type = type;
    
    if(type == INT) {
        array->items = new int[size];
        for(int i = 0; i < size; i++) {
            cout << "item[" << i << "]: ";
            cin >> static_cast<int*>(array->items)[i];
        }
    } else if(type == DOUBLE) {
        array->items = new double[size];
        for(int i = 0; i < size; i++) {
            cout << "item[" << i << "]: ";
            cin >> static_cast<double*>(array->items)[i];
        }
    } else if(type == STRING) {
        array->items = new string[size];
        for(int i = 0; i < size; i++) {
            cout << "item[" << i << "]: ";
            cin.ignore();
            getline(cin, static_cast<string*>(array->items)[i]);
        }
    } else if(type == ARRAY) {
        array->items = new Array[size];
        for(int i = 0; i < size; i++) {
            cout << "item[" << i << "]: ";
            static_cast<void **>(array->items)[i] = makeArray();
            if(static_cast<Array *>(static_cast<void **>(array->items)[i]) == nullptr) {
                removeArray(array);
                return nullptr;
            }
        }
    }

    return array;
}

void command_add(Database &database) {
    Entry *entry;

    cout << "key: ";
    string key;
    cin >> key;

    cout << "type (int, double, string, array): ";
    string inputKey;
    cin >> inputKey;
    Type type;
    if(inputKey.compare("int") == 0) {
        type = INT;
    } else if(inputKey.compare("double") == 0) {
        type = DOUBLE;
    } else if(inputKey.compare("string") == 0) {
        type = STRING;
    } else if(inputKey.compare("array") == 0) {
        type = ARRAY;
    } else {
        cout << "invalid type" << endl;
        return;
    }

    cout << "value: ";
    if(type == INT) {
        int *value = new int;
        cin >> *value;
        entry = create(type, key, value);
    } else if(type == DOUBLE) {
        double *value = new double;
        cin >> *value;
        entry = create(type, key, value);
    } else if(type == STRING) {
        string *value = new string;
        cin.ignore();
        getline(cin, *value);
        entry = create(type, key, value);
    } else if(type == ARRAY) {
        Array *value = makeArray();
        if(value == nullptr) {
            return;
        }
        entry = create(type, key, value);
    }

    add(database, entry);
}



void command_get(Database &database) {
    string key;
    cout << "key: ";
    cin >> key;

    Entry *findEntry = get(database, key);
    if(findEntry == nullptr) {
        cout << "not found" << endl;
    } else {
        printEntry(*findEntry);
    }
}

void command_del(Database &database) {
    string key;
    cout << "key: ";
    cin >> key;

    Entry *findEntry = get(database, key);
    if(findEntry == nullptr) {
        cout << "not found" << endl;
    } else {
        remove(database, findEntry->key);
    }
}

int main() {
    Database db;
    init(db);
    
    string command;

    while(true) {
        cout << "command (list, add, get, del, exit): ";
        cin >> command;
        if(command.compare("list") == 0) {
            command_list(db);
        } else if(command.compare("add") == 0) {
            command_add(db);
        } else if(command.compare("get") == 0) {
            command_get(db);
        } else if(command.compare("del") == 0) {
            command_del(db);
        } else if(command.compare("exit") == 0) {
            break;
        }

        cout << endl;
    }

    destroy(db);
    return 0;
}
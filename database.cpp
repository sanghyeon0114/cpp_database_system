#include "database.h"
#include <iostream>
#include <string>

Entry *create(Type type, std::string key, void *value) {
    Entry *entry = new Entry;
    entry->type = type;
    entry->key = key;
    entry->value = value; // FYI: "value" must be a dynamically allocated.
    return entry;
}

void init(Database &database) {
    database.entry = nullptr;
    database.size = 0;
}

void add(Database &database, Entry *entry) {
    for(int i = 0; i < database.size; i++) {
        if((*database.entry[i]).key == entry->key) {
            if((*database.entry[i]).type == INT) {
                delete (int *)(*database.entry[i]).value;
            } else if((*database.entry[i]).type == DOUBLE) {
                delete (double *)(*database.entry[i]).value;
            } else if((*database.entry[i]).type == STRING) {
                delete (std::string *)(*database.entry[i]).value;
            } else if((*database.entry[i]).type == ARRAY) {
                // Todo
            }
            (*database.entry[i]).type = entry->type;
            (*database.entry[i]).value = entry->value;
            return;
        }
    }

    Entry **tmp = database.entry;
    database.entry = new Entry*[database.size+1];

    for(int i = 0; i < database.size; i++) {
        database.entry[i] = tmp[i];
    }
    database.entry[database.size++] = entry;
    delete[] tmp;
}

Entry *get(Database &database, std::string &key) {
    for(int i = 0; i < database.size; i++) {
        if((*database.entry[i]).key == key) {
            return database.entry[i];
        }
    }
    return nullptr;
}

void remove(Database &database, std::string &key) {
    bool isDelete = false;

    for(int i = 0; i < database.size; i++) {
        if(!isDelete) {
            if((*database.entry[i]).key == key) {
                isDelete = true;
                if((*database.entry[i]).type == INT) {
                    delete (int *)(*database.entry[i]).value;
                } else if((*database.entry[i]).type == DOUBLE) {
                    delete (double *)(*database.entry[i]).value;
                } else if((*database.entry[i]).type == STRING) {
                    delete (std::string *)(*database.entry[i]).value;
                } else if((*database.entry[i]).type == ARRAY) {
                    // Todo
                }
            }
        } else {
            database.entry[i-1] = database.entry[i];
        }
    }

    if(isDelete) {
        database.size--;
    }
}

void destroy(Database &database) {
    for(int i = 0; i < database.size; i++) {
        if((*database.entry[i]).type == INT) {
            delete (int *)(*database.entry[i]).value;
        } else if((*database.entry[i]).type == DOUBLE) {
            delete (double *)(*database.entry[i]).value;
        } else if((*database.entry[i]).type == STRING) {
            delete (std::string *)(*database.entry[i]).value;
        } else if((*database.entry[i]).type == ARRAY) {
            // Todo
        }
    }
    delete[] database.entry;
    database.size = 0;
}

void list(Database &database) {
    for(int i = 0; i < database.size; i++) {
        std::cout << "key: " << (*database.entry[i]).key << std::endl;
        if((*database.entry[i]).type == INT) {
            std::cout << "value: " << *(int *)((*database.entry[i]).value) << std::endl;
        } else if((*database.entry[i]).type == DOUBLE) {
            std::cout << "value: " << *(double *)((*database.entry[i]).value) << std::endl;
        } else if((*database.entry[i]).type == STRING) {
            std::cout << "value: " << *(std::string *)((*database.entry[i]).value) << std::endl;
        } else if((*database.entry[i]).type == ARRAY) {
            // Todo
        }
    }
}
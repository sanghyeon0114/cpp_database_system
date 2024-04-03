#include "database.h"
#include <iostream>
#include <string>

void removeArray(Array *array) {
    if(array == nullptr) {
        return;
    }

    if(array->items == nullptr) {
        delete array;
        return;
    }

    if(array->type == INT) {
        delete[] static_cast<int *>(array->items);
    } else if(array->type == DOUBLE) {
        delete[] static_cast<double *>(array->items);
    } else if(array->type == STRING) {
        delete[] static_cast<std::string *>(array->items);
    } else if(array->type == ARRAY) {
        for(int i = 0; i < array->size; i++) {
            if(static_cast<Array *>(static_cast<void **>(array->items)[i]) != nullptr) {
                removeArray(static_cast<Array *>(static_cast<void **>(array->items)[i])); // void* -> void** -> Array *
            }
        }
        delete[] static_cast<Array *>(array->items);
    }
    delete array;
}

void printArray(Array *array) {
    std::cout << "[";
    for(int i = 0; i < array->size; i++) {
        if(array->type == INT) {
            std::cout << static_cast<int *>(array->items)[i];
        } else if(array->type == DOUBLE) {
            std::cout << static_cast<double *>(array->items)[i];
        } else if(array->type == STRING) {
            std::cout << "\"" << static_cast<std::string *>(array->items)[i] << "\"";
        } else if(array->type == ARRAY) {
            printArray(static_cast<Array *>(static_cast<void **>(array->items)[i]));
        }
        if(i != array->size-1) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

void removeEntryValue(Entry *entry) {
    if(entry->type == INT) {
        delete static_cast<int *>(entry->value);
    } else if(entry->type == DOUBLE) {
        delete static_cast<double *>(entry->value);
    } else if(entry->type == STRING) {
        delete static_cast<std::string *>(entry->value);
    } else if(entry->type == ARRAY) {
        removeArray(static_cast<Array *>(entry->value));
    }
}

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
        if(database.entry[i]->key == entry->key) {
            removeEntryValue(database.entry[i]);
            database.entry[i]->type = entry->type;
            database.entry[i]->value = entry->value;
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
                removeEntryValue(database.entry[i]);
                delete database.entry[i];
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
        removeEntryValue(database.entry[i]);
    }
    delete[] database.entry;
    database.size = 0;
}

void printEntry(Entry &entry) {
    std::cout << entry.key;
    if(entry.type == INT) {
        std::cout << ": " << *static_cast<int *>(entry.value) << std::endl;
    } else if(entry.type == DOUBLE) {
        std::cout << ": " << *static_cast<double *>(entry.value) << std::endl;
    } else if(entry.type == STRING) {
        std::cout << ": " << "\"" << *static_cast<std::string *>(entry.value) << "\"" << std::endl;
    } else if(entry.type == ARRAY) {
        std::cout << ": ";
        printArray(static_cast<Array *>(entry.value));
        std::cout << std::endl;
    }
}

void list(Database &database) {
    for(int i = 0; i < database.size; i++) {
        printEntry(*database.entry[i]);
    }
}
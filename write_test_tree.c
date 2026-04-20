#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int object_write(ObjectType type, const void *data, size_t len, ObjectID *id_out);

int main() {
    Tree original;
    original.count = 2;
    original.entries[0].mode = 0100644;
    memset(original.entries[0].hash.hash, 0x11, HASH_SIZE);
    strcpy(original.entries[0].name, "file1.txt");
    original.entries[1].mode = 0100644;
    memset(original.entries[1].hash.hash, 0x22, HASH_SIZE);
    strcpy(original.entries[1].name, "file2.txt");

    void *data;
    size_t len;
    tree_serialize(&original, &data, &len);

    ObjectID id;
    object_write(OBJ_TREE, data, len, &id);

    char hex[65];
    hash_to_hex(&id, hex);
    char path[256];
    sprintf(path, ".pes/objects/%.2s/%s", hex, hex+2);
    
    printf("xxd %s | head -20\n", path);
    
    char cmd[512];
    sprintf(cmd, "xxd %s | head -20", path);
    system(cmd);

    free(data);
    return 0;
}

#include <bits/time.h>
#include <pthread.h>
#include <comparr/compressedarray.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <comparr/textutil.h>
#include <time.h>


struct compressedarray {
    bool error;
    enum ElementCapacity element_capacity;
    size_t length;
    byte* data;
};

compressedarray_t* spawnCompressedArray(enum ElementCapacity capacity, size_t length) {
    compressedarray_t* array = malloc(sizeof(struct compressedarray));
    *array = (struct compressedarray) {
        .error = false,
        .element_capacity = capacity,
        .length = length,
        .data = malloc((length * (8 / capacity) + 7) / 8)
    };
    return array;
}
void killCompressedArray(compressedarray_t* array) {
    free(array->data);
    free(array);
}
bool caHasErrors(compressedarray_t* array) {
    bool err_stat = array->error;
    array->error = false;
    return err_stat;
}
byte caGet(compressedarray_t* array, size_t at) {
    if (at > array->length) {
        array->error = true;
        return 0x00;
    }
    array->error = false;
    uint8_t bits = 8 / array->element_capacity;
    int element_index = at / array->element_capacity;
    int bit_offset_real = (array->element_capacity - 1 - (at % array->element_capacity)) * bits;
    byte mask = (1 << bits) - 1;
    return (array->data[element_index] >> bit_offset_real) & mask;
}
void caSet(compressedarray_t* array, size_t at, byte what) {
    if (at > array->length) {
        array->error = true;
        return;
    }
    array->error = false;
    uint8_t bitcount = 8 / array->element_capacity;
    int element_index = at / array->element_capacity;
    int bit_offset_real = (array->element_capacity - 1 - (at % array->element_capacity)) * bitcount;
    byte mask = (1 << bitcount) - 1;
    array->data[element_index] &= ~(mask << bit_offset_real); // clear
    array->data[element_index] |= (what & mask) << bit_offset_real; // set
}


byte caGetIndependant(byte* data, enum ElementCapacity elementcapacity, size_t length, uint8_t bitoffset, size_t at) {
    if (at > length) 
        return 0x00;
    uint8_t bitcount = 8 / elementcapacity;
    int element_index = at / elementcapacity;
    int bit_offset_real = (at % elementcapacity) * bitcount + bitoffset;
    byte mask = ((1 << bitcount) - 1);
    return (data[element_index] >> bit_offset_real) & mask;
}
void caSetIndependant(byte* data, enum ElementCapacity elementcapacity, size_t length, uint8_t bitoffset, size_t at, byte what) {
    if (at > length) 
        return;
    uint8_t bitcount = 8 / elementcapacity;
    int element_index = at / elementcapacity;
    int bit_offset_real = (at % elementcapacity) * bitcount + bitoffset;
    byte mask = ((1 << bitcount) - 1);
    data[element_index] &= ~(mask << bit_offset_real); // clear
    data[element_index] |= (what & mask) << bit_offset_real; // set
}

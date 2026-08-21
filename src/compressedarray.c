#include <bits/time.h>
#include <pthread.h>
#include <compressedarray.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <textutil.h>
#include <time.h>
struct compressedarray {
    enum ElementCapacity element_capacity;
    size_t length;
    byte* data;
};

compressedarray_t* spawnCompressedArray(enum ElementCapacity capacity, size_t length) {
    compressedarray_t* array = malloc(sizeof(struct compressedarray));
    *array = (struct compressedarray) {
        .element_capacity = capacity,
        .length = length,
        // 0b1 >> 3 | 1 = 1
        // 0b111 >> 3 | 1 = 1
        // 0b1000 >> 3 | 1 = 1
        .data = malloc((length * (8 / capacity) + 7) / 8)
    };
    printf("alloc: %ld\n", (length * (8 / capacity) + 7) / 8);
    return array;
}
void killCompressedArray(compressedarray_t* array) {
    free(array->data);
    free(array);
}
byte caGet(compressedarray_t* array, size_t at) {
    uint8_t bits = 8 / array->element_capacity;
    int byte_index = at / array->element_capacity;
    int bit_offset = (array->element_capacity - 1 - (at % array->element_capacity)) * bits;
    byte mask = (1 << bits) - 1;
    return (array->data[byte_index] >> bit_offset) & mask;
}
void caSet(compressedarray_t* array, size_t at, byte what) {
    uint8_t bits = 8 / array->element_capacity;
    int byte_index = at / array->element_capacity;
    int bit_offset = (array->element_capacity - 1 - (at % array->element_capacity)) * bits;
    byte mask = (1 << bits) - 1;
    array->data[byte_index] &= ~(mask << bit_offset); // clear
    array->data[byte_index] |= (what & mask) << bit_offset; // set
}


byte caGetIndependant(byte* data, enum ElementCapacity element_capacity, size_t length, uint8_t bitoffset, size_t at) {
    uint8_t bits = 8 / element_capacity;
    printf("bits: %d\n", bits);
    int byte_index = at / element_capacity;
    printf("byte at: %s\n", showBits(data[byte_index]));
    int bit_offset = (at % element_capacity) * bits + bitoffset;
    printf("bit offset: %d\n", bit_offset);
    byte mask = ((1 << bits) - 1);
    printf("mask: %s\n", showBits( mask));
    printf("bits at: %s\n", showBits(data[byte_index] >> bit_offset));
    printf("result: %s\n", showBits((data[byte_index] >> bit_offset) & mask));
    return (data[byte_index] >> bit_offset) & mask;
}
void caSetIndependant(byte* data, enum ElementCapacity element_capacity, size_t length, uint8_t bitoffset, size_t at, byte what) {
    uint8_t bits = 8 / element_capacity;
    int byte_index = at / element_capacity;
    int bit_offset = (at % element_capacity) * bits + bitoffset;
    byte mask = ((1 << bits) - 1);
    data[byte_index] &= ~(mask << bit_offset); // clear
    data[byte_index] |= (what & mask) << bit_offset; // set
}

#pragma once

#include <stdbool.h>
#include <stdint.h>
#define PREFIX(value) ca ## value

#include <stddef.h>
typedef uint8_t byte;
typedef struct compressedarray compressedarray_t;
enum ElementCapacity {
    // 8 elements / byte
    ELEMENT_CAPACITY_BITS1 = 8,
    // 4 elements / byte
    ELEMENT_CAPACITY_BITS2 = 4,
    // 2 elements / byte
    ELEMENT_CAPACITY_BITS4 = 2,
    // For others create array yourself
};
compressedarray_t* spawnCompressedArray(enum ElementCapacity capacity, size_t length);
void killCompressedArray(compressedarray_t* array);

/// Returns last error status, and resets it.
/// spawnCompressedArray(ELEMENT_CAPACITY_BITS1, 4);
/// caGet(array, 32);
/// if (caHasErrors(array)) {
///     perror("Failed to 32 index");
/// }
bool caHasErrors(compressedarray_t* array);

/// If out of bounds, return 0, error flag set to true
byte caGet(compressedarray_t* array, size_t at);
/// If out of bounds, return 0, error flag set to true
void caSet(compressedarray_t* array, size_t at, byte what);

byte caGetIndependant(byte* data, enum ElementCapacity element_capacity, size_t length, uint8_t bitoffset, size_t at);
void caSetIndependant(byte* data, enum ElementCapacity element_capacity, size_t length, uint8_t bitoffset, size_t at, byte what);
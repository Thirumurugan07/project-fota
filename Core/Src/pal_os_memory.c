/**
 * MIT License
 * Copyright (c) 2021 Infineon Technologies AG
 */

#include "pal_os_memory.h"
#include <stdlib.h>
#include <string.h>

void * pal_os_malloc(uint32_t block_size)
{
    return malloc(block_size);
}

void * pal_os_calloc(uint32_t number_of_blocks , uint32_t block_size)
{
    return calloc(number_of_blocks, block_size);
}

void pal_os_free(void * block)
{
    free(block);
}

void pal_os_memcpy(void * p_destination, const void * p_source, uint32_t size)
{
    memcpy(p_destination, p_source, size);
}

void pal_os_memset(void * p_buffer, uint32_t value, uint32_t size)
{
    // Since memset takes int for value and sets byte-wise, cast to unsigned char
    memset(p_buffer, (unsigned char)value, size);
}

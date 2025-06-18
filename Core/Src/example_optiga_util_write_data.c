/**
 * SPDX-FileCopyrightText: 2021-2024 Infineon Technologies AG
 * SPDX-License-Identifier: MIT
 *
 * \author Infineon Technologies AG
 *
 * \file example_optiga_util_write_data.c
 *
 * \brief   This file provides the example for writing data/metadata to OPTIGA using
 *          #optiga_util_write_data and #optiga_util_write_metadata.
 *
 * \ingroup grOptigaExamples
 *
 * @{
 */

#include "optiga/optiga_example.h"
#include "optiga/optiga_util.h"

#ifndef OPTIGA_INIT_DEINIT_DONE_EXCLUSIVELY
extern void example_optiga_init(void);
extern void example_optiga_deinit(void);
#endif

/**
 * Sample Trust Anchor
 */
uint8_t bootloader_hash[32] = {
		0x73, 0x08, 0xE4, 0x2A, 0x21, 0xC4, 0x13, 0xD1,
		    0x3E, 0x4D, 0x8C, 0x89, 0x47, 0xB0, 0xF5, 0x87,
		    0xC6, 0xD5, 0x28, 0xDE, 0x55, 0x52, 0x82, 0x2C,
		    0x3F, 0x44, 0x13, 0x74, 0xDA, 0x2C, 0x18, 0x0F
};

/**
 * Sample metadata
 */
static const uint8_t metadata[] = {
    0x20, 0x03,
    0xD1, 0x01, 0x00  // Allow read always
};

/**
 * Callback when optiga_util_xxxx operation is completed asynchronously
 */
static volatile optiga_lib_status_t optiga_lib_status;
// lint --e{818} suppress "argument "context" is not used in the sample provided"
static void optiga_util_callback(void *context, optiga_lib_status_t return_status) {
    optiga_lib_status = return_status;
    if (NULL != context) {
        // callback to upper layer here
    }
}

/**
 * The below example demonstrates write data/metadata functionalities
 *
 * Example for #optiga_util_write_data and #optiga_util_write_metadata
 *
 */
void example_optiga_util_write_data(void)
{
    optiga_lib_status_t return_status = OPTIGA_UTIL_ERROR;
    optiga_util_t *me = NULL;
    uint16_t optiga_oid = 0xE0E8;
    uint16_t offset = 0;

    printf("Creating OPTIGA Util instance...\r\n");
    me = optiga_util_create(0, optiga_util_callback, NULL);
    if (me == NULL)
    {
        printf("Failed to create OPTIGA Util instance.\r\n");
        return;
    }

    OPTIGA_UTIL_SET_COMMS_PROTECTION_LEVEL(me, OPTIGA_COMMS_NO_PROTECTION);

    // Write trust anchor
    optiga_lib_status = OPTIGA_LIB_BUSY;
    printf("Writing trust anchor to 0xE0E8...\r\n");
    return_status = optiga_util_write_data(
        me,
        optiga_oid,
        OPTIGA_UTIL_ERASE_AND_WRITE,
        offset,
		bootloader_hash,
        sizeof(bootloader_hash)
    );

    while (optiga_lib_status == OPTIGA_LIB_BUSY)
    {
        pal_os_event_trigger_registered_callback();
    }

    if (optiga_lib_status != OPTIGA_LIB_SUCCESS)
    {
        printf("Writing trust anchor failed: 0x%04X\r\n", optiga_lib_status);
    }
    else
    {
        printf("Trust anchor written successfully.\r\n");
    }

//    // Write metadata
//    optiga_lib_status = OPTIGA_LIB_BUSY;
//    printf("Writing metadata to 0xE0E8...\r\n");
//    return_status = optiga_util_write_metadata(
//        me,
//        optiga_oid,
//        metadata,
//        sizeof(metadata)
//    );
//
//    while (optiga_lib_status == OPTIGA_LIB_BUSY)
//    {
//        pal_os_event_trigger_registered_callback();
//    }
//
//    if (optiga_lib_status != OPTIGA_LIB_SUCCESS)
//    {
//        printf("Writing metadata failed: 0x%04X\r\n", optiga_lib_status);
//    }
//    else
//    {
//        printf("Metadata written successfully.\r\n");
//    }

    // Clean up
    if (me)
    {
        optiga_util_destroy(me);
    }
}

/**
 * @}
 */

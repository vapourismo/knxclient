/* KNX Client Library
 * A library which provides the means to communicate with several
 * KNX-related devices or services.
 *
 * Copyright (C) 2014-2015, Ole Krüger <ole@vprsm.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef KNXCLIENT_PROTO_CEMI_TPDU_H
#define KNXCLIENT_PROTO_CEMI_TPDU_H

#include "data.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * Transport Protocol Control Information
 */
typedef enum {
	KNX_TPCI_UNNUMBERED_DATA    = 0,
	KNX_TPCI_NUMBERED_DATA      = 1,
	KNX_TPCI_UNNUMBERED_CONTROL = 2,
	KNX_TPCI_NUMBERED_CONTROL   = 3
} knx_tpci;

/**
 * Control codes used when TPCI set to control mode
 */
typedef enum {
	KNX_TPCI_CONTROL_CONNECTED    = 0,
	KNX_TPCI_CONTROL_DISCONNECTED = 1,
	KNX_TPCI_CONTROL_ACK          = 2,
	KNX_TPCI_CONTROL_ERROR        = 3
} knx_tpci_control;

/**
 * Application Protocol Control Information
 */
typedef enum {
	KNX_APCI_GROUPVALUEREAD         = 0,
	KNX_APCI_GROUPVALUERESPONSE     = 1,
	KNX_APCI_GROUPVALUEWRITE        = 2,
	KNX_APCI_INDIVIDUALADDRWRITE    = 3,
	KNX_APCI_INDIVIDUALADDRREQUEST  = 4,
	KNX_APCI_INDIVIDUALADDRRESPONSE = 5,
	KNX_APCI_ADCREAD                = 6,
	KNX_APCI_ADCRESPONSE            = 7,
	KNX_APCI_MEMORYREAD             = 8,
	KNX_APCI_MEMORYRESPONSE         = 9,
	KNX_APCI_MEMORYWRITE            = 10,
	KNX_APCI_USERMESSAGE            = 11,
	KNX_APCI_MASKVERSIONREAD        = 12,
	KNX_APCI_MASKVERSIONRESPONSE    = 13,
	KNX_APCI_RESTART                = 14,
	KNX_APCI_ESCAPE                 = 15
} knx_apci;

/**
 * Transport Protocol Data Unit
 */
typedef struct {
	knx_tpci tpci;
	uint8_t seq_number;

	union {
		knx_tpci_control control;
		struct {
			knx_apci apci;
			const uint8_t* payload;
			size_t length;
		} data;
	} info;
} knx_tpdu;

/**
 * Unpack the TPDU fields.
 */
bool knx_tpdu_parse(const uint8_t* tpdu, size_t length, knx_tpdu* info);

/**
 * Generate the TPDU.
 */
void knx_tpdu_generate(uint8_t* tpdu, const knx_tpdu* info);

/**
 * Space required to fit the given TPDU.
 */
inline static size_t knx_tpdu_size(const knx_tpdu* info) {
	switch (info->tpci) {
		case KNX_TPCI_UNNUMBERED_DATA:
		case KNX_TPCI_NUMBERED_DATA: {
			size_t s = info->info.data.length + 1;

			if (s > 2)
				return s;
			else
				return 2;
		}

		case KNX_TPCI_UNNUMBERED_CONTROL:
		case KNX_TPCI_NUMBERED_CONTROL:
			return 1;
	}
}

// /**
//  * Interpret the TPDU payload to generate a C type.
//  */
// bool knx_tpdu_interpret(const uint8_t* tpdu, size_t length, knx_dpt type, void* value);

// /**
//  * Generate the TPDU containing the given datapoint type.
//  */
// void knx_tpdu_generate(uint8_t* tpdu, knx_apci apci, knx_dpt type, const void* value);

// /**
//  * Same as `knx_tpdu_generate` but allocates the array for you. The result needs to `free`d.
//  */
// uint8_t* knx_tpdu_generate_(size_t* length, knx_apci apci, knx_dpt type, const void* value);

#endif

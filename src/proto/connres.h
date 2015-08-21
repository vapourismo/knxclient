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

#ifndef KNXCLIENT_PROTO_KNXNETIP_CONNRES_H
#define KNXCLIENT_PROTO_KNXNETIP_CONNRES_H

#include "hostinfo.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * Connection Response
 */
typedef struct {
	/**
	 * Communication channel
	 */
	uint8_t channel;

	/**
	 * Connection status (`0` is good)
	 */
	uint8_t status;

	/**
	 * Control host information as seen by the gateway
	 */
	knx_host_info host;

	/**
	 * ???
	 */
	uint8_t extended[3];
} knx_connection_response;

/**
 * Generate a raw connection response.
 *
 * \see knx_connection_response_size
 * \param buffer Output buffer
 * \param res Input connection response
 */
void knx_connection_response_generate(uint8_t* buffer, const knx_connection_response* res);

/**
 * Parse a raw connection response.
 *
 * \param buffer Raw connection response
 * \param length Number of bytes in `buffer`
 * \param res Output connection response
 */
bool knx_connection_response_parse(const uint8_t* buffer, size_t length,
                                   knx_connection_response* res);

/**
 * Calculate the size of a raw connection response.
 */
inline static
size_t knx_connection_response_size(const knx_connection_response* res) {
	return (res->status == 0 ? KNX_HOST_INFO_SIZE + 6 : 2);
}

#endif

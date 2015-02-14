#include "tunnelres.h"
#include "header.h"
#include "../alloc.h"

// Tunnel Response:
//   Octet 0: Structure length
//   Octet 1: Channel
//   Octet 2: Sequence number
//   Octet 3: Status

bool knx_append_tunnel_response(msgbuilder* mb,
                                const knx_tunnel_response* res) {
	return
		knx_append_header(mb, KNX_TUNNEL_RESPONSE, 4) &&
		msgbuilder_append(mb, anona(const uint8_t, 4, res->channel, res->seq_number, res->status), 4);
}

bool knx_parse_tunnel_response(const uint8_t* message, size_t length,
                               knx_tunnel_response* res) {
	if (length < 4 || message[0] != 4)
		return false;

	res->channel = message[1];
	res->seq_number = message[2];
	res->status = message[3];

	return true;
}


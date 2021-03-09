#pragma once
#ifndef PACKET_H
#define PACKET_H

#include "memoryallocator.h"
//
#include <stdint.h>

#include "servercommon.h"

// UDP 512 bytes safe max
struct Packet {
  uint32_t sequence;
  char packet_type;
  char entity_id[36];
  char data[256];
};

#endif  // PACKET_H

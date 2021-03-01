#pragma once
#ifndef DAD_N_ME_EMULATE_H
#define DAD_N_ME_EMULATE_H

#include "memoryallocator.h"
//
#include "servercommon.h"

// Spawn thread for local server

struct DadNMeEmulate {
  int holder;
};

int dad_n_me_emulate_init(struct DadNMeEmulate* dad_n_me_emulate);

#endif  // DAD_N_ME_EMULATE_H
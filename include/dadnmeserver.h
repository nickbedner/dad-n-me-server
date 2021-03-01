#pragma once
#ifndef DAD_N_ME_SERVER_H
#define DAD_N_ME_SERVER_H

#include "memoryallocator.h"
//
#include "dadnmeemulate.h"
#include "dadnmesocket.h"

enum DadNMeServerType {
  DAD_N_ME_SERVER_SOCKET = 0,
  DAD_N_ME_SERVER_EMULATE
};

struct DadNMeServer {
  union {
    struct DadNMeSocket dad_n_me_socket;
    struct DadNMeEmulate dad_n_me_emulate;
  };
  enum DadNMeServerType dad_n_me_server_type;
};

int dad_n_me_server_init(struct DadNMeServer* dad_n_me_server, enum DadNMeServerType dad_n_me_server_type);
void dad_n_me_server_delete(struct DadNMeServer* dad_n_me_server);
void dad_n_me_server_send(struct DadNMeServer* dad_n_me_server);
void dad_n_me_server_recieve(struct DadNMeServer* dad_n_me_server);

#endif  // DAD_N_ME_SERVER_H
#include "dadnmeserver.h"

int dad_n_me_server_init(struct DadNMeServer* dad_n_me_server, enum DadNMeServerType dad_n_me_server_type, struct GameState* game_state) {
  dad_n_me_server->dad_n_me_server_type = dad_n_me_server_type;

  // TODO: Error checking
  switch (dad_n_me_server->dad_n_me_server_type) {
    case (DAD_N_ME_SERVER_SOCKET):
      // TODO: Spin up thread to send/recieve packets @ 15ms
      dad_n_me_server->game_state = calloc(1, sizeof(struct GameState));
      game_state_init(dad_n_me_server->game_state);
      dad_n_me_socket_init(&dad_n_me_server->dad_n_me_socket);
      break;
    case (DAD_N_ME_SERVER_EMULATE):
      // Create state
      dad_n_me_server->game_state = game_state;
      dad_n_me_emulate_init(&dad_n_me_server->dad_n_me_emulate);
      break;
    default:
      return 1;
  }

  return 0;
}

void dad_n_me_server_delete(struct DadNMeServer* dad_n_me_server) {
}

void dad_n_me_server_send(struct DadNMeServer* dad_n_me_server) {
}

void dad_n_me_server_recieve(struct DadNMeServer* dad_n_me_server) {
}
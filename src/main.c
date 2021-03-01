#include "dadnmesocket.h"

// Only ran when standalone server is hosted
int main(int argc, char **argv) {
  // TODO: Bad for performance flush manually on release? Yes, configure for debug only
  // Checked seems print operations per tick have huge cpu use
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  struct DadNMeSocket dad_n_me_socket;
  dad_n_me_socket_init(&dad_n_me_socket);

  while (1) {
    char buf[BUFLEN];
    memset(buf, '0', BUFLEN);

    socket_recieve(&dad_n_me_socket, buf);
    socket_send(&dad_n_me_socket, buf);

    sleep((1 / 30.0f) * 1000);
  }

  socket_delete(&dad_n_me_socket);

  return 0;
}
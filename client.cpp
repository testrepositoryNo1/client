#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <boost/type_index.hpp>

using namespace std;

const int port = 3425;

int main()
{
      int sTime = 0; /* дискриптор сокета */
      time_t currentTime  = time(NULL);;
      struct sockaddr_in addr;

      sTime = socket(AF_INET, SOCK_STREAM, 0);
      if(sTime < 0) {
              perror("socket");
              return -1;
          }

      addr.sin_family = AF_INET;
      addr.sin_port = htons(port);
      inet_pton(AF_INET, "172.16.5.110", &addr.sin_addr); /* local test*/
      //inet_pton(AF_INET, "89.223.26.96", &addr.sin_addr);    /* internet test */

      /* проверка соединения */
      if(connect(sTime, (sockaddr *)&addr, sizeof(addr)) < 0) {
              perror("connect");
              return -2;
          }

      recv(sTime, &currentTime, sizeof(currentTime), 0); /* получаем сооьщение*/
      cout << ctime(&currentTime);

      close(sTime); /* закрываем дискриптор сокета */

      return 0;
}

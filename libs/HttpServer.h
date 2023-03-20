#include <map>
#include <WebServer.h>

namespace LTLabs::HttpServer {
  enum HttpMethod { GET, POST, PUT, PATCH, DELETE };
  typedef std::function<void(void)> Handler;
  typedef std::map<HttpMethod, Handler> PathHandler;
  const String httpMethod[5] = {"GET", "POST", "PUT", "PATCH", "DELETE"};

  struct Config {
    int port;
  };


  class Server: public WebServer {
    public:
      Server(int port): WebServer(port) {
      }
  };


}

#include "net_client.h"
#include "Client.h"
#include "../include.h"

void CheckPassword(Client& client);
void CheckLogin(Client& client);
int SERVER_PORT = 60000;

int main() {
  Client client;
  client.connect("127.0.0.1", SERVER_PORT);

  if (!client.is_connected()) {
    std::cout << "No connection\n" << std::endl;
    return 1;
  }

  bool client_session = true;
  std::wstring buffer;

  while (client_session) {
    std::cout << "> ";
    getline(std::wcin, buffer);
    if (buffer == L"exit")
      client_session  = false;
    if (buffer == L"stop")
      client.StopServer();
    else {
      client.send_msg(buffer);
    }
    buffer.clear();

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    if (client.is_connected()) {
      if (!client.get_in_comming().empty()) {
        auto msg = client.get_in_comming().pop_front().msg;

        switch (msg.header.id) {
        case msg_type::ServerAccept: {
          std::cout << "Server Accepted Connection\n";
          break;
        }

        case msg_type::ServerMessage: {
          std::cout << "Hello from [" /*<< client_id*/ << "]\n";
          break;
        }

        case msg_type::LoginValid: {
          CheckPassword(client);
          break;
        }

        case msg_type::LoginInvalid: {
          CheckLogin(client);
          break;
        }

        case msg_type::PasswordValid: {
          std::cout << "Good autorization\n";
          break;
        }

        case msg_type::PasswordInvalid: {
          std::cout << "Bad autorization\n";
          break;
        }
        }
      }
    } else {
      std::cout << "Server Down\n";
      client_session  = false;
    }
  }

  return 0;
}

void CheckPassword(Client& client) {
  std::wstring password;
  getline(std::wcin, password);
  client.CheckPassword(password);
}

void CheckLogin(Client& client) {
  std::wstring login;
  getline(std::wcin, login);
  client.CheckLogin(login);
}
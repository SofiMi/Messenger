#include "../include.h"
#include "net_server.h"
#include <fstream>


int SERVER_PORT = 30000;
bool SERVER_WORK = true;

class Server : public net::server_interface<msg_type> {
public:
  Server(uint16_t port) : net::server_interface<msg_type>(port) {}

  void SendImg(std::shared_ptr<net::connection<msg_type>> client);

protected:
  virtual bool
  __on_client_connect(std::shared_ptr<net::connection<msg_type>> client) {
    net::message<msg_type> msg;
    msg.header.id = msg_type::ServerAccept;
    // client->send(msg);
    return true;
  }

  // Called when a client appears to have disconnected
  virtual void
  __on_client_disconnect(std::shared_ptr<net::connection<msg_type>> client) {
    std::cout << "Removing client [" << client->get_id() << "] \n";
  }

  // Called when a message arrives
  virtual void __on_message(std::shared_ptr<net::connection<msg_type>> client,
                            net::message<msg_type> &msg) {
    switch (msg.header.id) {
    case msg_type::CheckLogin: {
      std::wcout << "CheckLogin " << msg.data.data() << std::endl;
      std::wstring st = L"5";
      std::wstring st1 = msg.data.data();
      if (st1 == st) {
        msg.header.id = msg_type::LoginValid;
        msg.header.userid = 5;
      } else {
        msg.header.id = msg_type::LoginInvalid;
      }
      client->send(msg);
      break;
    }

    case msg_type::CheckPassword: {
      std::wcout << "CheckPassword " << msg.data.data() << std::endl;
      std::wstring st = L"5";
      std::wstring st1 = msg.data.data();
      if (st1 == st) {
        std::cout << "YES\n";
        msg.header.id = msg_type::PasswordValid;
      } else {
        std::cout << "NO\n";
        msg.header.id = msg_type::PasswordInvalid;
      }
      client->send(msg);
      break;
    }

    case msg_type::MessageAll: {
      std::wcout << "[" << msg.header.name.data()
                 << "]: Send the message to all user\n";

      // Construct a new message and send it to all clients
      net::message<msg_type> __msg;
      __msg.header.id = msg_type::ServerMessage;
      __msg.header.name = msg.header.name;
      message_all_clients(__msg, client);
      break;
    }

    case msg_type::JoinServer: {
      std::wcout << "[" << msg.header.name.data() << "] Join the server\n";
      break;
    }

    case msg_type::PassString: {
      std::wcout << "[" << msg.header.name.data() << "]: "
                 << " " << msg.header.userid << " " << msg.data.data() << '\n';
      break;
    }

    case msg_type::StopServer: {
      SERVER_WORK = false;
    }

    case msg_type::GetUpdateById: {
      int chat_id = 0;
      //__msg.header.id = msg_type::ServerMessage;
      //__msg.header.name = msg.header.name;
      std::copy(&msg.data[0], &msg.data[0] + sizeof(size_t),
                reinterpret_cast<char *>(&chat_id));
      std::cout << "User_id = " << msg.header.userid
                << ". Chat_id = " << chat_id << std::endl;
      net::message<msg_type> new_msg;
      new_msg.header.id = msg_type::NewMessageToThisChat;
      new_msg.header.userid = chat_id;
      std::wstring __data = L"Hello!";
      for (unsigned int i = 0; i < __data.size(); ++i) {
        new_msg.data[i] = __data[i];
      }
      client->send(new_msg);
    }

    case msg_type::GetImg : {
      SendImg(client);
    }
    }
  }

};

int main() {
  Server server(SERVER_PORT);
  server.start();

  while (SERVER_WORK) {
    server.update(-1);
  }

  return 0;
}


void Server::SendImg(std::shared_ptr<net::connection<msg_type>> client) {
  std::string name = "images.jpeg";
  std::ifstream in(name, std::ios::binary);
  std::ofstream out(std::string("clientImageSofi.jpeg"), std::ios::binary);

  if (!in.good()) {
    throw;
  }

  in.seekg(0, std::ios::end);
  size_t myFileSize = in.tellg();
  in.seekg(0, std::ios::beg);

  std::cout << "Count msg: " << myFileSize / 256 << std::endl;

  while (in.tellg() < myFileSize) {
    net::message<msg_type> __msg;
    __msg.header.id = msg_type::SendImgMore;
    in.read((char*)__msg.data.data(), 256);
    out.write((char*)__msg.data.data(), 256);
    client->send(__msg);
    std::cout << "send" << std::endl;
  }
  std::cout << "END" << std::endl;
  net::message<msg_type> __msg;
  __msg.header.id = msg_type::SendImgFinish;
  client->send(__msg);
  in.close();
  out.close();
}
#pragma once
#include <cstdint>

enum class msg_type : uint32_t {
  JoinServer,
  ServerAccept,
  ServerDeny,
  ServerPing,
  MessageAll,
  ServerMessage,
  PassString,

  CheckLogin,
  CheckPassword,
  LoginValid,
  LoginInvalid,
  PasswordValid,
  PasswordInvalid,
  StopServer,
  GetUpdateById,
  NewMessageToThisChat,
  NewMessageToOtherChat,
  GetImg,
  SendImgMore,
  SendImgFinish,
  GetChat
};
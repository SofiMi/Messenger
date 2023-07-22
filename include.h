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

  // Проверка Авторизации
  CheckLogin,
  CheckPassword,
  LoginValid,
  LoginInvalid,
  PasswordValid,
  PasswordInvalid,

  // Получение старых сообщения
  LastMessageId, 
  GetMessages,
  SendMsgMore,
  SendMsgFinish,

  // Получение чатов
  SendImgMore,
  SendImgFinish,
  GetChat,

  StopServer,
  GetUpdateById,
  NewMessageToThisChat,
  NewMessageToOtherChat,
  GetImg
};
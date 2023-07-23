#pragma once
#include <cstdint>

enum class msg_type : uint32_t {
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
  NewMessage,
};
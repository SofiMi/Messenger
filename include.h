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

  // Прекращение работы сервера
  StopServer,

  // Отправка нового сообщение
  NewMessage,

  // Добавление нового пользователя
  AddNewUser,
  CheckUniqueLogin,
  CheckUniqueNick,

  // Поиск 
  CheckChatName,
  CreateNewChat,
  CheckTetAtTetChat,

  // Обновление
  GetDataUpdate,
  SendUnpdateMore,
  SendUnpdateFinish,
};
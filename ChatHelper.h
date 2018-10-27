#pragma once
#ifndef CHATHELPER_H
#define CHATHELPER_H
#include <Windows.h>
#include "macro.h"
#include "EnterHelper.h"
#include "AnalysisHelper.h"
class ChatHelper
{
	CEH *eh;
	chat_analysis *ca;
public:
	//Конструктор
	ChatHelper(std::wstring pathToFile, Pattern* patterns, uint16_t size, bool chat_open = 1, KeyCode OpenChatLetter = VK_T);

	//Возвращает последние ошибки
	std::pair<unsigned int, unsigned int> GetLastErrors();

	//Возвращает последнее сообщение из чата
	Message GetLastMessage();

	//Есть ли последнее сообщение?
	bool MessageIsAnAvailable();
	//Добавить сообщение в очередь
	unsigned int  AddMessageToQueue(std::wstring nachalnii_kusok, std::wstring message);
};
#endif
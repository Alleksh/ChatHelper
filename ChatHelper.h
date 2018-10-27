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
	//�����������
	ChatHelper(std::wstring pathToFile, Pattern* patterns, uint16_t size, bool chat_open = 1, KeyCode OpenChatLetter = VK_T);

	//���������� ��������� ������
	std::pair<unsigned int, unsigned int> GetLastErrors();

	//���������� ��������� ��������� �� ����
	Message GetLastMessage();

	//���� �� ��������� ���������?
	bool MessageIsAnAvailable();
	//�������� ��������� � �������
	unsigned int  AddMessageToQueue(std::wstring nachalnii_kusok, std::wstring message);
};
#endif
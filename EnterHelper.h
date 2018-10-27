#ifndef ENTERHELPER_H
#define ENTERHELPER_H
#include "macro.h"
#include <string>
#include <map>
#include <windows.h>
#include <WinUser.h>
struct KeyCode
{
	bool shift = 0, control = 0;
	uint8_t LANGUAGE = LANG_ENG;
	BYTE KC = 0x0;
	KeyCode(BYTE key) { KC = key; }
	KeyCode() {}
};
class EnterHelper
{
private:
	std::map<wchar_t, KeyCode> M;
	uint8_t NOW_LANGUAGE = LANG_ENG;
	//������� ��������� ����������
	void ChangeLanguage();
	unsigned int lastError;
public:
	//�����������
	EnterHelper();
	EnterHelper(unsigned int& lastError)
	{
		this->lastError = lastError;
		this->lastError = 1;
		EnterHelper();
	}
	//������ �� �����
	void PressReturn();

	//������ �� ������� �� KeyCode
	void EnterKey(KeyCode KC);

	//������ �� ������� �� unsigned char
	void EnterKey(BYTE Key);

	//������ �� ����������� �������
	void EnterKeys(KeyCode* KCs, int size);

	//������� ������ � ������ ������
	KeyCode* StringToKeyCodes(std::wstring str);

	//����� � ������ ������ ���� ���������� � ������	
	uint8_t GetLanguage();
};
#include <mutex>
#include <vector>
class CEH
{
	EnterHelper* EH;
	unsigned int lastError;
	std::mutex lock;
	std::vector<std::wstring> queue;
public:
	CEH(bool chat_open = 1, KeyCode OpenChatLetter = VK_T);
	unsigned int addMessageToQueue(std::wstring str);
	unsigned int GetLastError()
	{
		return lastError;
	}
};
#endif
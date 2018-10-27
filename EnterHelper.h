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
	//Сменить раскладку клавиатуры
	void ChangeLanguage();
	unsigned int lastError;
public:
	//Конструктор
	EnterHelper();
	EnterHelper(unsigned int& lastError)
	{
		this->lastError = lastError;
		this->lastError = 1;
		EnterHelper();
	}
	//Нажать на энтер
	void PressReturn();

	//Нажать на клавишу по KeyCode
	void EnterKey(KeyCode KC);

	//Нажать на клавишу по unsigned char
	void EnterKey(BYTE Key);

	//Нажать на необходимые клавиши
	void EnterKeys(KeyCode* KCs, int size);

	//Перевод строки в массив клавиш
	KeyCode* StringToKeyCodes(std::wstring str);

	//Какой в данный момент язык установлен в классе	
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
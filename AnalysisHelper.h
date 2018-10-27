#ifndef ANALYSISHELPER_H
#define ANALYSISHELPER_H
#include "macro.h"
#include <string>
#include <vector>
#include <mutex>
/* TODO
* добавить вывод ошибок
*/
struct Pattern
{
	std::wstring pattern;
	int id = 0x0, size = 0x0;
	Pattern(int id) { this->id = id; }
	Pattern() {}
	Pattern(std::wstring pattern, int id, int size)
	{
		this->id = id;
		this->pattern = pattern;
		this->size = size;
	}
};

struct Message
{
	std::wstring * parts, message;
	Pattern pattern;
	// -1 - unrecognized pattern
	// -1 - Нераспознанный паттерн
	int PatternID = 0x0;
	std::string Date;
};
///////////////////////////////////////
//Класс анализа чата
class chat_analysis
{
private:
	//////////////////////////////
	//Переменные

	// Путь к файлу с логом
	std::wstring PathToFile;

	// Сообщения, загруженные из файла
	std::vector<std::wstring> MessagesFromLog;	

	// Распознаные сообщения
	std::vector<Message> Messages;				

	// Паттерны
	std::vector<Pattern> Patterns;			
	//мьютексы
	std::mutex MessagesFromLogAccess, MessagesAccess, PatternsAccess, LastErrorAccess;

	bool ReaderThreadClose = 0, ChatRecognizeThreadClose = 0;
	unsigned int LAST_RETURNED_MESSAGE_ID = 0, lastError = SUCCESS;
public:
	//конструктор
	chat_analysis(std::wstring PathToFile, Pattern* patterns, int size);
	//Получить последнее сообщение из чата.
	Message GetLastMessage();
	//Есть ли новое сообщение?
	bool MessageIsAnAvailable();
	unsigned int GetLastError()
	{
		return lastError;
	}
	Message& operator[](unsigned int num);
};
#endif
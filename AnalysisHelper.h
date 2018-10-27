#ifndef ANALYSISHELPER_H
#define ANALYSISHELPER_H
#include "macro.h"
#include <string>
#include <vector>
#include <mutex>
/* TODO
* �������� ����� ������
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
	// -1 - �������������� �������
	int PatternID = 0x0;
	std::string Date;
};
///////////////////////////////////////
//����� ������� ����
class chat_analysis
{
private:
	//////////////////////////////
	//����������

	// ���� � ����� � �����
	std::wstring PathToFile;

	// ���������, ����������� �� �����
	std::vector<std::wstring> MessagesFromLog;	

	// ����������� ���������
	std::vector<Message> Messages;				

	// ��������
	std::vector<Pattern> Patterns;			
	//��������
	std::mutex MessagesFromLogAccess, MessagesAccess, PatternsAccess, LastErrorAccess;

	bool ReaderThreadClose = 0, ChatRecognizeThreadClose = 0;
	unsigned int LAST_RETURNED_MESSAGE_ID = 0, lastError = SUCCESS;
public:
	//�����������
	chat_analysis(std::wstring PathToFile, Pattern* patterns, int size);
	//�������� ��������� ��������� �� ����.
	Message GetLastMessage();
	//���� �� ����� ���������?
	bool MessageIsAnAvailable();
	unsigned int GetLastError()
	{
		return lastError;
	}
	Message& operator[](unsigned int num);
};
#endif
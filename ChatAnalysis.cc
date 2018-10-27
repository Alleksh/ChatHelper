#include "AnalysisHelper.h"
#include <string>
#include <codecvt>
#include <fstream>
#include <thread>
#include <mutex>
#include <iomanip>
int SizeOFile(std::wstring filename)
{
	std::wifstream x(filename);
	x.seekg(0, std::ios::end);
	int returnValue = int(x.tellg());
	x.close();
	return returnValue;
}
/* TODO
* Переписать потоки для большей эффективности
*/
///////////////////////////////////////
//Поток для распознавания сообщений из чата
void	ChatReaderThread(bool *ReaderThreadClose, std::wstring* PathToFile, unsigned int* lastError,
	std::vector<std::wstring>* MessagesFromLog, std::mutex* MessagesFromLogAccess, std::mutex* LastErrorAccess)
{
	std::wifstream LogFile;
	LogFile.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));
	int lastSize = -1, MESSAGE_FROM_LOG_SIZE;
	LogFile.open((*PathToFile));
	if (!LogFile.is_open())
	{
		(*LastErrorAccess).lock();
		(*lastError) = ERR_WRONG_FILENAME;
		(*LastErrorAccess).unlock();
		return;
	}
	LogFile.close();
	int x = 0; std::wstring buffer;
	while (!(*ReaderThreadClose))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_DELAY));
		if (SizeOFile((*PathToFile)) != lastSize)
		{
			x = 0;
			LogFile.open((*PathToFile));
			(*MessagesFromLogAccess).lock();
			MESSAGE_FROM_LOG_SIZE = (*MessagesFromLog).size();
			(*MessagesFromLogAccess).unlock();
			while (x < MESSAGE_FROM_LOG_SIZE - 1) if (getline(LogFile, buffer)) x++;
			if (x >= MESSAGE_FROM_LOG_SIZE - 1)
			{
				(*MessagesFromLogAccess).lock();
				while (getline(LogFile, buffer)) { (*MessagesFromLog).push_back(buffer); }
				(*MessagesFromLogAccess).unlock();
				lastSize = SizeOFile((*PathToFile));
			}
			LogFile.close();
		}
		else std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_DELAY));
	}
}
///////////////////////////////////////
//Поток для обработки сообщений из чата
void	ChatRecognizeThread(bool *ChatRecognizeThreadClose, unsigned int* lastError,
	std::vector<std::wstring>* MessagesFromLog, std::vector<Message>* Messages, std::vector<Pattern>* Patterns,
	std::mutex*		   MessagesFromLogAccess, std::mutex* MessagesAccess, std::mutex* PatternsAccess, std::mutex* LastErrorAccess)
{
	Pattern UnrecognizedPattern(UNRECOGNIZED_PATTERN_ID);
	unsigned int LastMessageID = 0;
	bool x, Delay = 0;
	while (!(*ChatRecognizeThreadClose))
	{
		Delay = 0;
		if (Delay) std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_DELAY));
		std::wstring LAST_MESSAGE;
		(*MessagesFromLogAccess).lock();
		x = (LastMessageID < (*MessagesFromLog).size());
		if (x)
		{
			LAST_MESSAGE = (*MessagesFromLog)[LastMessageID];
			LastMessageID++;
		}
		(*MessagesFromLogAccess).unlock();
		if (x)
		{
			Message InsertibleValue;
			InsertibleValue.message = LAST_MESSAGE;
			(*PatternsAccess).lock();
			int PATTERNS_SIZE = (*Patterns).size();
			(*PatternsAccess).unlock();
			Pattern RecognizedPattern = UnrecognizedPattern;
			bool TRUE_PATTERN = 0;
			int i = 0;
			for (i = 0; i < PATTERNS_SIZE && !TRUE_PATTERN; i++)
			{
				(*PatternsAccess).lock();
				Pattern NOW_PATTERN = (*Patterns)[i];
				(*PatternsAccess).unlock();
				std::wstring buffer = InsertibleValue.message, *strBuffer = new std::wstring[NOW_PATTERN.size];
				for (int i = 0; i < NOW_PATTERN.size; i++) strBuffer[i] = L"_";
				unsigned int now_pattern_itr = 0, now_itr = 0;
				bool THIS_PATTERN = true;
				if (buffer.size() > NOW_PATTERN.pattern.size())
					for (unsigned int i = 0; i < buffer.size() && THIS_PATTERN; i++, now_pattern_itr++)
					{
						if (!(NOW_PATTERN.pattern[now_pattern_itr] >= '0' && NOW_PATTERN.pattern[now_pattern_itr] <= '9'))
						{
							if ((NOW_PATTERN.pattern[now_pattern_itr] != buffer[i])) THIS_PATTERN = false;
						}
						else if (NOW_PATTERN.pattern[now_pattern_itr] >= '0' && NOW_PATTERN.pattern[now_pattern_itr] <= '9')
						{
							strBuffer[now_itr] = L"#";
							while (i<buffer.size() && (NOW_PATTERN.pattern[now_pattern_itr] >= '0' && NOW_PATTERN.pattern[now_pattern_itr] <= '9') && (NOW_PATTERN.pattern[now_pattern_itr + 1] != buffer[i]))
							{
								strBuffer[now_itr] += buffer[i];
								i++;
							};
							now_itr++;
							i--;
						}
					}
				bool xyz = true;
				for (int i = 0; i < NOW_PATTERN.size; i++) if (strBuffer[i][0] != '#') xyz = false;
				for (int i = 0; i < NOW_PATTERN.size; i++)
				{
					std::wstring buffer;
					for (unsigned int y = 1; y < strBuffer[i].size(); y++) buffer += strBuffer[i][y];
					strBuffer[i] = buffer;
				}
				if (now_pattern_itr + 4 < NOW_PATTERN.pattern.size()) xyz = false;
				if (xyz)
				{
					TRUE_PATTERN = true;
					RecognizedPattern = NOW_PATTERN;
					InsertibleValue.PatternID = NOW_PATTERN.id;
					InsertibleValue.parts = strBuffer;
				}
			}
			InsertibleValue.pattern = RecognizedPattern;
			if (TRUE_PATTERN)
			{
				(*MessagesAccess).lock();
				(*Messages).push_back(InsertibleValue);
				(*MessagesAccess).unlock();
			}
			Delay = 0;
		}
		if (!x)
		{
			Delay = 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_DELAY));
		}
	}
}
chat_analysis::chat_analysis(std::wstring PathToFile, Pattern* patterns, int size)
{
	for (int i = 0; i<size; i++)	Patterns.push_back(patterns[i]);
	this->PathToFile = PathToFile;
	std::thread x(ChatReaderThread, &ReaderThreadClose, &this->PathToFile, &lastError, &MessagesFromLog, &MessagesFromLogAccess, &LastErrorAccess);
	std::thread y(ChatRecognizeThread, &ChatRecognizeThreadClose, &lastError, &MessagesFromLog, &Messages, &Patterns, &MessagesFromLogAccess, &MessagesAccess, &PatternsAccess, &LastErrorAccess);
	x.detach();
	y.detach();
}
Message		chat_analysis::GetLastMessage()
{
	Message x;
	MessagesAccess.lock();
	if (LAST_RETURNED_MESSAGE_ID < Messages.size())
	{
		x = Messages[LAST_RETURNED_MESSAGE_ID];
		LAST_RETURNED_MESSAGE_ID++;
	}
	else if (LAST_RETURNED_MESSAGE_ID > 0)
	{
		x = Messages[LAST_RETURNED_MESSAGE_ID - 1];
	}
	MessagesAccess.unlock();
	return x;
}
bool		chat_analysis::MessageIsAnAvailable()
{
	MessagesAccess.lock();
	bool x = (LAST_RETURNED_MESSAGE_ID < Messages.size());
	MessagesAccess.unlock();
	return x;
}
Message&	chat_analysis::operator[](unsigned int num)
{
	return Messages[num];
}
#include "ChatHelper.h"
ChatHelper::ChatHelper(std::wstring pathToFile, Pattern* patterns,uint16_t size, bool chat_open, KeyCode OpenChatLetter)
{
	eh = new CEH(chat_open, OpenChatLetter);
	ca = new chat_analysis(pathToFile, patterns, size);
}
std::pair<unsigned int, unsigned int> ChatHelper::GetLastErrors()
{
	return std::pair<unsigned int, unsigned int>(eh->GetLastError(), ca->GetLastError());
}
Message ChatHelper::GetLastMessage()
{
	return ca->GetLastMessage();
}
bool ChatHelper::MessageIsAnAvailable()
{
	return ca->MessageIsAnAvailable();
}
unsigned int ChatHelper::AddMessageToQueue(std::wstring nachalnii_kusok, std::wstring message)
{
	nachalnii_kusok += L" ";
	if (nachalnii_kusok.size() + message.size() < 100) return eh->addMessageToQueue(nachalnii_kusok + message);
	else
	{
		std::vector<std::wstring> words;
		std::wstring buffer;
		for (unsigned int i = 0; i < message.size(); i++)
			if (message[i] != ' ') buffer += message[i];
			else
			{
				if (buffer.size() + nachalnii_kusok.size() > 100) return ERR_TOO_BIG_WORD;
				words.push_back(buffer);
				buffer = L"";
			}
		words.push_back(buffer);
		std::wstring x = nachalnii_kusok;
		while (words.size() > 0)
		{
			std::wstring nowWord = words[0];
			if (x.size() + nowWord.size() > 100)
			{
				if (nachalnii_kusok == L"!") Sleep(3000);
				eh->addMessageToQueue(x);
				x = nachalnii_kusok;
				continue;
			}
			x += L" " + nowWord;
			words.erase(words.begin());
		}
		eh->addMessageToQueue(x);
	}
	return SUCCESS;
}
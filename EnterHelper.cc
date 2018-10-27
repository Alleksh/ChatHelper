#include "EnterHelper.h"
#include <thread>
#include <vector>
#include <mutex>
/* TODO
* ���������� ����� ��� ������� �������������
* ���������� �����������
* ��������� ������ ������
*/

//������� ��� ����������� �������������� �������
KeyCode returnZ(KeyCode Pattern, BYTE symbol)
{
	KeyCode returnValue(symbol);
	returnValue.shift = Pattern.shift;
	returnValue.control = Pattern.control;
	returnValue.LANGUAGE = Pattern.LANGUAGE;
	return returnValue;
}
//�����������
EnterHelper::EnterHelper()
{
	KeyCode RussianB, russian,//������ ��� ������� ����
		withshift, withoutshift, AnyLang, AnyLangShift;//������ ��� ���� � ������ � ���
	RussianB.LANGUAGE = LANG_RUS; russian.LANGUAGE = LANG_RUS;
	RussianB.shift = 1; 	withshift.shift = 1; AnyLangShift.shift = 1;
	AnyLang.LANGUAGE = ANY_LANG;	AnyLangShift.LANGUAGE = ANY_LANG;
	M = std::map<wchar_t, KeyCode>
	{
	{ ' ', returnZ(AnyLang, VK_SPACE) },			// ' '
	{ L'�', returnZ(RussianB, VK_OEM_3) },			// �
	{ L'�', returnZ(russian, VK_OEM_3) },			// �
	{ L'�', returnZ(RussianB, VK_F) },				// A
	{ L'�', returnZ(RussianB, VK_OEM_COMMA) },		// �
	{ L'�', returnZ(RussianB, VK_D) },				// �
	{ L'�', returnZ(RussianB, VK_U) },				// �
	{ L'�', returnZ(RussianB, VK_L) },				// �
	{ L'�', returnZ(RussianB, VK_T) },				// �
	{ L'�', returnZ(RussianB, VK_OEM_1) },			// �
	{ L'�', returnZ(RussianB, VK_P) },				// �
	{ L'�', returnZ(RussianB, VK_B) },				// �
	{ L'�', returnZ(RussianB, VK_Q) },				// �
	{ L'�', returnZ(RussianB, VK_R) },				// �
	{ L'�', returnZ(RussianB, VK_K) },				// �
	{ L'�', returnZ(RussianB, VK_V) },				// �
	{ L'�', returnZ(RussianB, VK_Y) },				// �
	{ L'�', returnZ(RussianB, VK_J) },				// �
	{ L'�', returnZ(RussianB, VK_G) },				// �
	{ L'�', returnZ(RussianB, VK_H) },				// �
	{ L'�', returnZ(RussianB, VK_C) },				// �
	{ L'�', returnZ(RussianB, VK_N) },				// �
	{ L'�', returnZ(RussianB, VK_E) },				// �
	{ L'�', returnZ(RussianB, VK_A) },				// �
	{ L'�', returnZ(RussianB, VK_OEM_4) },			// �
	{ L'�', returnZ(RussianB, VK_W) },				// �
	{ L'�', returnZ(RussianB, VK_X) },				// �
	{ L'�', returnZ(RussianB, VK_I) },				// �
	{ L'�', returnZ(RussianB, VK_O) },				// �
	{ L'�', returnZ(RussianB, VK_OEM_6) },			// �
	{ L'�', returnZ(RussianB, VK_S) },				// �
	{ L'�', returnZ(RussianB, VK_M) },				// �
	{ L'�', returnZ(RussianB, VK_OEM_7) },			// �
	{ L'�', returnZ(RussianB, VK_OEM_PERIOD) },		// �
	{ L'�', returnZ(RussianB, VK_Z) },				// �
	{ L'�', returnZ(russian, VK_F) },				// �
	{ L'�', returnZ(russian, VK_OEM_COMMA) },		// �
	{ L'�', returnZ(russian, VK_D) },				// �
	{ L'�', returnZ(russian, VK_U) },				// �
	{ L'�', returnZ(russian, VK_L) },				// �
	{ L'�', returnZ(russian, VK_T) },				// �
	{ L'�', returnZ(russian, VK_OEM_1) },			// �
	{ L'�', returnZ(russian, VK_P) },				// �
	{ L'�', returnZ(russian, VK_B) },				// �
	{ L'�', returnZ(russian, VK_Q) },				// �
	{ L'�', returnZ(russian, VK_R) },				// �
	{ L'�', returnZ(russian, VK_K) },				// �
	{ L'�', returnZ(russian, VK_V) },				// �
	{ L'�', returnZ(russian, VK_Y) },				// �
	{ L'�', returnZ(russian, VK_J) },				// �
	{ L'�', returnZ(russian, VK_G) },				// �
	{ L'�', returnZ(russian, VK_H) },				// �
	{ L'�', returnZ(russian, VK_C) },				// �
	{ L'�', returnZ(russian, VK_N) },				// �
	{ L'�', returnZ(russian, VK_E) },				// �
	{ L'�', returnZ(russian, VK_A) },				// �
	{ L'�', returnZ(russian, VK_OEM_4) },			// �
	{ L'�', returnZ(russian, VK_W) },				// �
	{ L'�', returnZ(russian, VK_X) },				// �
	{ L'�', returnZ(russian, VK_I) },				// �
	{ L'�', returnZ(russian, VK_O) },				// �
	{ L'�', returnZ(russian, VK_OEM_6) },			// �
	{ L'�', returnZ(russian, VK_S) },				// �
	{ L'�', returnZ(russian, VK_M) },				// �
	{ L'�', returnZ(russian, VK_OEM_7) },			// �
	{ L'�', returnZ(russian, VK_OEM_PERIOD) },		// �
	{ L'�', returnZ(russian, VK_Z) },				// �
	{ VK_1, returnZ(AnyLang, VK_1) },			// 1
	{ VK_2, returnZ(AnyLang, VK_2) },			// 2
	{ VK_3, returnZ(AnyLang, VK_3) },			// 3
	{ VK_4, returnZ(AnyLang, VK_4) },			// 4
	{ VK_5, returnZ(AnyLang, VK_5) },			// 5
	{ VK_6, returnZ(AnyLang, VK_6) },			// 6
	{ VK_7, returnZ(AnyLang, VK_7) },			// 7
	{ VK_8, returnZ(AnyLang, VK_8) },			// 8
	{ VK_9, returnZ(AnyLang, VK_9) },			// 9
	{ VK_0, returnZ(AnyLang, VK_0) },			// 0
	{ '!', returnZ(AnyLangShift, VK_1) },				// !
	{ '@', returnZ(withshift, VK_2) },				// @
	{ '#', returnZ(withshift, VK_3) },				// #
	{ '$', returnZ(withshift, VK_4) },				// $
	{ '%', returnZ(withshift, VK_5) },				// %
	{ '^', returnZ(withshift, VK_6) },				// ^
	{ '&', returnZ(withshift, VK_7) },				// &
	{ '*', returnZ(AnyLangShift, VK_8) },				// *
	{ '(', returnZ(AnyLangShift, VK_9) },				// (
	{ ')', returnZ(AnyLangShift, VK_0) },				// )
	{ '-', returnZ(AnyLang, VK_OEM_MINUS) },	// -
	{ '=', returnZ(AnyLang, VK_OEM_PLUS) },	// =
	{ '_', returnZ(AnyLangShift,	 VK_OEM_MINUS) },	// _
	{ '+', returnZ(AnyLangShift,	 VK_OEM_PLUS) },	// +
	{ '`', returnZ(AnyLang, VK_OEM_3) },		// `
	{ '~', returnZ(AnyLangShift,	 VK_OEM_3) },		// ~
	{ VK_A, returnZ(withshift, VK_A) },				// A
	{ VK_B, returnZ(withshift, VK_B) },				// B
	{ VK_C, returnZ(withshift, VK_C) },				// C
	{ VK_D, returnZ(withshift, VK_D) },				// D
	{ VK_E, returnZ(withshift, VK_E) },				// E
	{ VK_F, returnZ(withshift, VK_F) },				// F
	{ VK_G, returnZ(withshift, VK_G) },				// G
	{ VK_H, returnZ(withshift, VK_H) },				// H
	{ VK_I, returnZ(withshift, VK_I) },				// I
	{ VK_J, returnZ(withshift, VK_J) },				// J
	{ VK_K, returnZ(withshift, VK_K) },				// K
	{ VK_L, returnZ(withshift, VK_L) },				// L
	{ VK_M, returnZ(withshift, VK_M) },				// M
	{ VK_N, returnZ(withshift, VK_N) },				// N
	{ VK_O, returnZ(withshift, VK_O) },				// O
	{ VK_P, returnZ(withshift, VK_P) },				// P
	{ VK_Q, returnZ(withshift, VK_Q) },				// Q
	{ VK_R, returnZ(withshift, VK_R) },				// R
	{ VK_S, returnZ(withshift, VK_S) },				// S
	{ VK_T, returnZ(withshift, VK_T) },				// T
	{ VK_U, returnZ(withshift, VK_U) },				// U
	{ VK_V, returnZ(withshift, VK_V) },				// V
	{ VK_W, returnZ(withshift, VK_W) },				// W
	{ VK_X, returnZ(withshift, VK_X) },				// X
	{ VK_Y, returnZ(withshift, VK_Y) },				// Y
	{ VK_Z, returnZ(withshift, VK_Z) },				// Z
	{ VK_A + 32, returnZ(withoutshift, VK_A) },		// a
	{ VK_B + 32, returnZ(withoutshift, VK_B) },		// b
	{ VK_C + 32, returnZ(withoutshift, VK_C) },		// c
	{ VK_D + 32, returnZ(withoutshift, VK_D) },		// d
	{ VK_E + 32, returnZ(withoutshift, VK_E) },		// e
	{ VK_F + 32, returnZ(withoutshift, VK_F) },		// f
	{ VK_G + 32, returnZ(withoutshift, VK_G) },		// g
	{ VK_H + 32, returnZ(withoutshift, VK_H) },		// h
	{ VK_I + 32, returnZ(withoutshift, VK_I) },		// i
	{ VK_J + 32, returnZ(withoutshift, VK_J) },		// j
	{ VK_K + 32, returnZ(withoutshift, VK_K) },		// k
	{ VK_L + 32, returnZ(withoutshift, VK_L) },		// l
	{ VK_M + 32, returnZ(withoutshift, VK_M) },		// m
	{ VK_N + 32, returnZ(withoutshift, VK_N) },		// n
	{ VK_O + 32, returnZ(withoutshift, VK_O) },		// o
	{ VK_P + 32, returnZ(withoutshift, VK_P) },		// p
	{ VK_Q + 32, returnZ(withoutshift, VK_Q) },		// q
	{ VK_R + 32, returnZ(withoutshift, VK_R) },		// r
	{ VK_S + 32, returnZ(withoutshift, VK_S) },		// s
	{ VK_T + 32, returnZ(withoutshift, VK_T) },		// t
	{ VK_U + 32, returnZ(withoutshift, VK_U) },		// u
	{ VK_V + 32, returnZ(withoutshift, VK_V) },		// v
	{ VK_W + 32, returnZ(withoutshift, VK_W) },		// w
	{ VK_X + 32, returnZ(withoutshift, VK_X) },		// x
	{ VK_Y + 32, returnZ(withoutshift, VK_Y) },		// y
	{ VK_Z + 32, returnZ(withoutshift, VK_Z) },		// z
	{ '[', returnZ(withoutshift,	VK_OEM_4) },			// [
	{ '{', returnZ(withshift,		VK_OEM_4) },			// {
	{ ']', returnZ(withoutshift,	VK_OEM_6) },			// ]
	{ '}', returnZ(withshift,		VK_OEM_6) },			// }
	{ ';', returnZ(withoutshift,	VK_OEM_1) },			// ]
	{ ':', returnZ(withshift,		VK_OEM_1) },			// }
	{ '\'', returnZ(withoutshift,	VK_OEM_7) },			// '
	{ '\"', returnZ(withshift,		VK_OEM_7) },			// "
	{ '\\', returnZ(withoutshift,	VK_OEM_5) },			/* \  */
	{ '|', returnZ(withshift,		VK_OEM_5) },			// |
	{ ',', returnZ(withoutshift,	VK_OEM_COMMA) },		// ,
	{ '<', returnZ(withshift,		VK_OEM_COMMA) },		// <
	{ '.', returnZ(withoutshift,	VK_OEM_PERIOD) },		// .
	{ '>', returnZ(withshift,		VK_OEM_PERIOD) },		// >
	{ '/', returnZ(withoutshift,	VK_OEM_2) },			// /
	{ '?', returnZ(withshift,		VK_OEM_2) }				// ?
	};
	NOW_LANGUAGE = LANG_ENG;
}

void		EnterHelper::ChangeLanguage()
{
	if (NOW_LANGUAGE == LANG_ENG) NOW_LANGUAGE = LANG_RUS;
	else NOW_LANGUAGE = LANG_ENG;
#ifndef DEBUG_MODE_OFF_KEYS
	keybd_event(VK_SHIFT, 0, 0, 0);
	keybd_event(VK_MENU, 0, 0, 0);
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(CHANGE_LANGUAGE_SLEEP_CONST));
#endif

}
void		EnterHelper::PressReturn()
{
#ifndef DEBUG_MODE_OFF_KEYS
	keybd_event(VK_RETURN, 0, 0, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(RETURN_KEY_SLEEP_CONST));
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
#endif
}
void		EnterHelper::EnterKey(KeyCode KC)
{
	if (KC.KC == 0x0) return;
	if (KC.LANGUAGE != ANY_LANG)
		if (KC.LANGUAGE != NOW_LANGUAGE)
			ChangeLanguage();
#ifndef DEBUG_MODE_OFF_KEYS
	if (KC.shift) keybd_event(VK_SHIFT, 0, 0, 0);
	if (KC.control) keybd_event(VK_CONTROL, 0, 0, 0);
#endif
#ifndef DEBUG_MODE_OFF_KEYS
	keybd_event(KC.KC, 0, 0, 0);
#endif
#ifndef NO_DELAY
#endif
#ifndef DEBUG_MODE_OFF_KEYS
	keybd_event(KC.KC, 0, KEYEVENTF_KEYUP, 0);
#endif

#ifndef DEBUG_MODE_OFF_KEYS
	if (KC.shift) keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
	if (KC.control) keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	if (KC.shift) std::this_thread::sleep_for(std::chrono::milliseconds(SHIFT_KEY_SLEEP_CONST));
	std::this_thread::sleep_for(std::chrono::milliseconds(ENTER_KEY_SLEEP_CONST));
	if (KC.control) std::this_thread::sleep_for(std::chrono::milliseconds(SHIFT_KEY_SLEEP_CONST));
#endif
}
void		EnterHelper::EnterKey(BYTE Key)
{
	if (Key == 0x0) return;
	keybd_event(Key, 0, 0, 0);
#ifndef NO_DELAY
	std::this_thread::sleep_for(std::chrono::milliseconds(ENTER_KEY_SLEEP_CONST));
#endif
	keybd_event(Key, 0, KEYEVENTF_KEYUP, 0);
}
void		EnterHelper::EnterKeys(KeyCode* KCs, int size)
{
	for (int i = 0; i < size; i++) EnterKey(KCs[i]);
}
uint8_t		EnterHelper::GetLanguage() { return NOW_LANGUAGE; }
KeyCode*	EnterHelper::StringToKeyCodes(std::wstring str)
{
	KeyCode* KeyCodes = new KeyCode[str.size()];
	for (unsigned int i = 0; i < str.size(); i++) if (M.find(str[i]) != M.end()) KeyCodes[i] = M.at(str[i]);
	return KeyCodes;
}
void enterQueueThread(std::mutex* lock, std::vector<std::wstring>* queue, EnterHelper* EH, KeyCode OpenChatLetter, bool chatAlwaysOpen)
{
	uint64_t b;
	uint64_t numOfMessages = 0, otherNumOfMessages = 0;
	uint64_t lastMessageTime = clock();
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_DELAY));
		(*lock).lock();
		b = (*queue).size();
		(*lock).unlock();
		if (b != 0)
		{
			if (!(numOfMessages >= 5 && lastMessageTime + 3000 > clock()))
			{
				if (!(otherNumOfMessages >= 15 && lastMessageTime + 5000 > clock()))
				{
					lastMessageTime = clock();
					if (numOfMessages >= 5) numOfMessages = -1;
					if (otherNumOfMessages >= 15) otherNumOfMessages = -1;
					(*lock).lock();
					if (!chatAlwaysOpen) {
						(*EH).EnterKey(OpenChatLetter);
						std::this_thread::sleep_for(std::chrono::milliseconds(OPEN_CHAT_DELAY));
					}
					(*EH).EnterKeys((*EH).StringToKeyCodes((*queue)[0]), (*queue)[0].size());
					(*EH).PressReturn();
					(*queue).erase((*queue).begin());
					(*lock).unlock();
					numOfMessages++;
					otherNumOfMessages++;
				}
			}
		}
		else std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_DELAY));
	}
}
CEH::CEH(bool chat_open, KeyCode OpenChatLetter)
{
	lock.lock();
	lock.unlock();
	EH = new EnterHelper(lastError);
	std::thread x(enterQueueThread, &lock, &queue, EH, OpenChatLetter, chat_open);
	x.detach();
}
unsigned int CEH::addMessageToQueue(std::wstring str)
{
	lock.lock();
	queue.push_back(str);
	lock.unlock();
	return SUCCESS;
}
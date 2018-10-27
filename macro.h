#ifndef  MACRO_H
#define MACRO_H
///////////////////////////////////////////
//Changeable values
#define RETURN_ERRORS

// Задержка потоков						(25 мс)
//!!!!!! Не ставить 0, будет кушать много ресурсов процессора.
#define THREAD_DELAY 0x19 

// Задержка открытия чата				(75 мс)
#define OPEN_CHAT_DELAY					0x4B	

// Задержка нажатий на клавиши			(3 мс)
#define ENTER_KEY_SLEEP_CONST			0x03	

// Задержка нажатия на шифт				(16 мс)
#define SHIFT_KEY_SLEEP_CONST			0x10	

// Задержка нажатия на enter			(16 мс)
#define RETURN_KEY_SLEEP_CONST			0x10	

// Задержка смены раскладки клавиатуры	(16 мс)
#define CHANGE_LANGUAGE_SLEEP_CONST		0x10	

//	Отключить нажатия на клавиши
//#define DEBUG_MODE_OFF_KEYS

//end
///////////////////////////////////////////
//defines
#define SUCCESS						0x0
#define ERR_WRONG_FILENAME			0x1001
#define ERR_WRONG_ID				0x1002
#define ERR_WRONG_LANGUAGE			0x1003
#define UNRECOGNIZED_PATTERN_ID		0x1004
#define ERR_TOO_BIG_WORD			0x1005
#define LANG_ENG 0x0
#define LANG_RUS 0x1
#define ANY_LANG 0x2
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A	
//end
#endif
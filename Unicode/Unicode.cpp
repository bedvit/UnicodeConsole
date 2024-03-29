﻿// Unicode.cpp: определяет точку входа для консольного приложения.
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include <iostream>
#include <sstream>

int wmain(int argc, wchar_t* argv[], wchar_t *envp[]) //https://msdn.microsoft.com/ru-ru/library/bky3b5dh.aspx?f=255&MSPPError=-2147217396
{	////////////////////Переводим в Юникод
	_setmode(_fileno(stdout), _O_U16TEXT); // https://msdn.microsoft.com/ru-ru/library/tw4k6df8.aspx
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	////////////////////Меняем размер консоли - можно пропустить, если вам не надо
	system("mode con cols=100 lines=50"); //размер окна, вывод нужного количества строк в консоль (видимых)
	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  size{ 100,100 };//символов строки, строк (если больше чем видимых, скрываются под ползунком прокрутки)
	SetConsoleScreenBufferSize(hout, size);//размер буфера
	////////////////////Меняем шрифт
	CONSOLE_FONT_INFOEX cfi; //https://docs.microsoft.com/en-us/windows/console/console-font-infoex
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 14;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;//400;
	wcscpy_s(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(hout, false, &cfi);
	////////////////////

	wchar_t* wchar_C = new wchar_t[255];
	//или
	std::wstring wstring_cpp;

	wprintf(L"%s", L"Testing unicode -- English -- Русский -- Ελληνικά -- Español.\n");
	// или
	std::wcout << L"Testing unicode -- English -- Русский -- Ελληνικά -- Español." << std::endl;
	
	//далее
	wprintf(L"%s", L"Введите строку с пробелами (разными символами, разной раскладки)(C): \n");
	fgetws(wchar_C, 255, stdin); //забираем строку с пробелами
	wchar_C[wcscspn(wchar_C, L"\n")] = 0; //убираем перевод строки
	wprintf(L"%s", wchar_C); //выводим
	//или
	std::wcout << L"\nВведите строку с пробелами (разными символами, разной раскладки)(C++std::): \n";
	std::getline(std::wcin, wstring_cpp); //забираем строку с пробелами
	std::wcout << wstring_cpp + L"\n"; //выводим

	_wsystem(L"pause");//пауза для просмотра результата
    return 0;
}

//https://msdn.microsoft.com/ru-ru/library/bky3b5dh.aspx?f=255&MSPPError=-2147217396
//https://msdn.microsoft.com/ru-ru/library/tw4k6df8.aspx
//https://docs.microsoft.com/en-us/windows/console/console-font-infoex
//https://ru.stackoverflow.com/questions/459154/%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9-%D1%8F%D0%B7%D1%8B%D0%BA-%D0%B2-%D0%BA%D0%BE%D0%BD%D1%81%D0%BE%D0%BB%D0%B8

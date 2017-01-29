#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <boost/program_options.hpp>

BOOL CALLBACK SearchVoiceroid(HWND hwnd, LPARAM lp);
HWND CALLBACK SearchTextArea(HWND mainWindow);
void sendText(HWND hwnd, std::string text);
HWND CALLBACK SearchPlayButton(HWND mainWindow);

// オプション用の構造体
struct Options {
	// 読み上げ用文字列
	std::string comment;
} typedef Options;

HWND voiceroid;

void main(int argc, char* argv[]) {
	Options option;

	namespace po = boost::program_options;
	po::options_description opt("オプション");
	opt.add_options()
		("help,h", "ヘルプを表示")
		("comment,c", po::value<std::string>(), "コメント");
	po::variables_map vm;
	try
	{
		po::store(po::parse_command_line(argc, argv, opt), vm);
	}
	catch (const boost::program_options::error_with_option_name& e)
	{
		std::cout << e.what() << std::endl;
	}
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << opt << std::endl;
	}
	else
	{
		try
		{
			option.comment = vm["comment"].as<std::string>();
			std::cout << option.comment << std::endl;
		}
		catch (const boost::bad_any_cast& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// Voiceroidのハンドラの取得
	EnumWindows(SearchVoiceroid, 0x0);

	HWND textArea = SearchTextArea(voiceroid);

	SendMessage(textArea, WM_SETTEXT, (WPARAM)_T(""), NULL);

	sendText(textArea, option.comment);

	HWND play_button = SearchPlayButton(voiceroid);
	SendMessage(play_button, BM_CLICK, 0, 0);

}


BOOL CALLBACK SearchVoiceroid(HWND hwnd, LPARAM lp) {
	TCHAR strWindowText[1024];
	GetWindowText(hwnd, strWindowText, 1024);
	
	if (_tcscmp(_T("VOICEROID＋ 結月ゆかり EX"), strWindowText) == 0
		 || _tcscmp(_T("VOICEROID＋ 結月ゆかり EX*"), strWindowText) == 0)
	 {
		_tprintf(_T("%s が見つかりました。\n"), strWindowText);
		voiceroid = hwnd;
		return false;
	}
	return true;
}

HWND CALLBACK SearchTextArea(HWND mainWindow) {
	HWND hwnd = GetWindow(mainWindow, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_HWNDNEXT);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	
	return hwnd;
	
}

void sendText(HWND hwnd, std::string text) {
	size_t num = 0;
	wchar_t *wcs = new wchar_t[text.length() + 1];
	errno_t err = mbstowcs_s(&num, wcs, text.length() + 1, text.c_str(), _TRUNCATE);

	for (int i = 0; i < wcslen(wcs); i++) {
		SendMessage(hwnd, WM_CHAR, (WPARAM)wcs[i], 0);
	}
	delete wcs;
}

HWND CALLBACK SearchPlayButton(HWND mainWindow) {
	HWND hwnd = GetWindow(mainWindow, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_HWNDNEXT);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_CHILD);
	hwnd = GetWindow(hwnd, GW_HWNDNEXT);
	hwnd = GetWindow(hwnd, GW_CHILD);
	
	return hwnd;
	
}
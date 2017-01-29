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
std::string wstring2string(const std::wstring &src);

// オプション用の構造体
struct Options {
	// 読み上げ用文字列
	std::wstring comment;
} typedef Options;

HWND voiceroid;

void _tmain(int argc, _TCHAR* argv[]) {
	Options option;

	namespace po = boost::program_options;
	po::options_description opt("オプション");
	opt.add_options()
		("help,h", "ヘルプを表示");
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

	auto pr = parse_command_line(argc, argv, opt);
	std::wstring echo_text = _T("");

	// オプション以外のコマンドライン引数取得
	for (auto const& str : collect_unrecognized(pr.options, po::include_positional)) {
		echo_text.append(str);
	}

	printf("echo_text:%d\n", echo_text.length());

	// Voiceroidのハンドラの取得
	EnumWindows(SearchVoiceroid, 0x0);

	HWND textArea = SearchTextArea(voiceroid);

	SendMessage(textArea, WM_SETTEXT, (WPARAM)_T(""), NULL);

	sendText(textArea, wstring2string(echo_text));

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

	printf("wcslen(wcs):%d\n", wcslen(wcs));

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

std::string wstring2string(const std::wstring &src) {
	//ロケール指定
	setlocale(LC_ALL, "japanese");

	size_t num = 0;

	char *mbs = new char[src.length() * MB_CUR_MAX + 1];
	errno_t err = wcstombs_s(&num, mbs, src.length() * MB_CUR_MAX + 1, src.c_str(), _TRUNCATE);

	std::string dest = mbs;
	delete[] mbs;

	return dest;
}

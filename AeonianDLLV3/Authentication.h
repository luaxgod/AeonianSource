#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <TlHelp32.h>
#include <WinInet.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "wininet.lib")

using namespace std; //don't tell ceanko

bool isauthed = false;
bool firsttime = false;

std::string autherrreturn;

#include "Authentication/XorString.h"
#include "Authentication/AES256.hpp"
#include "Authentication/base64.h"


string ReplaceAll(string subject, const string& search,
	const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

string DownloadURL(string URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = ReplaceAll(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	string p = ReplaceAll(rtn, "|n", "\r\n");
	return p;
}

BOOL is_wow64()
{
	BOOL b_is_wow64 = FALSE;

	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fn_is_wow64_process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fn_is_wow64_process)
	{
		if (!fn_is_wow64_process(GetCurrentProcess(), &b_is_wow64))
		{
			return FALSE; 
		}
	}
	return b_is_wow64;
}


std::vector<std::string> split_string(const std::string &str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string tok;

	while (std::getline(ss, tok, delimiter))
		tokens.push_back(tok);

	return tokens;
}

#define ERRMB(s, s1) MessageBox(NULL, s, s1, MB_ICONERROR | MB_OK);
#define INFOMB(s, s1) MessageBox(NULL, s, s1, MB_ICONINFORMATION | MB_OK); 

enum AuthLevel {
	InformationUpdate
};

#include "Authentication/HWIDGen.h"

void AuthenticateCredentials(string User_Name, string Pass_Word, AuthLevel AType) {
	if (!is_wow64)
	{
		ERRMB("32 bit systems are not currently supported!", "Eror!");
		exit(0);
	}
	
	if (AType == AuthLevel::InformationUpdate)
	{

		string EncUN = base64_encode(User_Name);
		string EncPW = base64_encode(Pass_Word);

		string EncHWID = base64_encode(GetID());

		XorS(WLURL, "no authey wauthey urley for u skiddie");

		XorS(INFa1, "?17=");
		XorS(INFa2, "&38=");
		XorS(INFa3, "&dab=");

		string vF = WLURL.decrypt();

		std::string args;

		args += INFa1.decrypt();
		args += EncUN;
		args += INFa2.decrypt();
		args += EncPW;
		args += INFa3.decrypt();
		args += EncHWID;

		std::string wassuccess = DownloadURL(vF += args);

		XorS(FIRSTTIME, "HASGDJGHASDJHSDN");
		XorS(S, "AHBNWDHFBDNEIUEWBFNC");
		XorS(FAEN, "2ENAB");
		XorS(UCORRFAIL, "UNAMECORRECTPASSINCORRECT");
		XorS(FAIL, "NOINDB");

		if (wassuccess == FIRSTTIME.decrypt())
		{
			XorS(SUCC, "Success! Welcome, ");
			std::cout << igreen << SUCC.decrypt() << User_Name << "\n";
			isauthed = true;
			firsttime = true;
			return;
		}

		if (wassuccess == S.decrypt())
		{
			XorS(SUCC, "Success! Welcome, ");
			std::cout << igreen << SUCC.decrypt() << User_Name << "\n";
			isauthed = true;
			return;
		}

		XorS(AER, "Auth Error!");

		if (wassuccess == FAEN.decrypt())
		{
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
			XorS(T, "This account has 2FA Enabled!");
			INFOMB(T.decrypt(), AER.decrypt());
			::ShowWindow(::GetConsoleWindow(), SW_SHOW);
			return;
		}

		if (wassuccess == UCORRFAIL.decrypt())
		{
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
			XorS(ERR6, "Error while Authenticating Error Code: 6");
			ERRMB(ERR6.decrypt(), AER.decrypt());
			exit(0);
		}

		if (wassuccess == FAIL.decrypt())
		{
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
			XorS(ERR7, "Error while Authenticating Error Code: 7");
			ERRMB(ERR7.decrypt(), AER.decrypt());
			exit(0);
		}

		std::vector<string> blcheck = split_string(wassuccess, '|');

		if (blcheck.at(0) == "BL")
		{
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
			
			XorS(ERRBL, "You have been blacklisted from Aeonian for the reason: ");
			blcheck.at(1) = ERRBL.decrypt() + blcheck.at(1);

			ERRMB(blcheck.at(1).c_str(), AER.decrypt());
			exit(0);
		}

		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		XorS(ERR8, "Error while Authenticating Error Code: 8");
		ERRMB(ERR8.decrypt(), AER.decrypt());
		exit(0);
	}
}

#include <Windows.h>

#include <string>

#include <sstream>

std::string GetID() {
	std::string ss = "Err_StringIsNu";

	UCHAR sz_filesys[255], sz_volname_buff[255];
	DWORD dw_serial;
	DWORD dw_mfl;
	DWORD dw_sys_flags;
	int error = 0;

	bool success = GetVolumeInformation(LPCTSTR("C:\\"), (LPTSTR)sz_volname_buff, 255, &dw_serial, &dw_mfl, &dw_sys_flags, (LPTSTR)sz_filesys, 255);

	if (!success) {
		ss = "Err_Not_Elevated";
	}

	std::stringstream error_stream;
	error_stream << dw_serial;
	return std::string(error_stream.str());
}
#include "extspoof.h"

int IsArg(const int argc, const TCHAR* argv[], const TCHAR* tzArg) {
	int i;

	for (i = 0; i < argc; ++i) {
		if (!_tcscmp(argv[i], tzArg))
			return i;
	}
	return 0;	// assuming 0 is path in common OSs
}

int wmain(int argc, TCHAR* argv[]) {	// fuck error checking
	BOOL	bDontForceOverwrite = FALSE;
	wchar_t wzNewFile[MAX_PATH] = {0},
			wzOldExt[MAX_PATH] = {0},
			wzReverseNewExt[MAX_PATH] = {0},
		   *pExt = NULL,
		   *wzDup = NULL,
		    wOverRide = (WORD)0x202e;
	int		i;
	LPWSTR  wzLastErr = NULL;

	if (argc < 3) {
		_tprintf(tzUsage);
		_gettch();
		return 0;
	}
	
	bDontForceOverwrite = !IsArg(argc, argv, TEXT("-o"));
	wzDup = wcsdup(argv[1]);	// before transformations
	wcscpy(wzNewFile, argv[1]);
	pExt = wcsrchr(wzNewFile, TEXT('.'));
	if (pExt != NULL) {
		wcscpy(wzOldExt, pExt);
		memset(pExt, 0, wcslen(wzOldExt) * sizeof(wchar_t));
	}
	for (i = 0; i < wcslen(argv[2]); ++i) {
		wzReverseNewExt[wcslen(argv[2]) - i - 1] = argv[2][i];
	}
	// swprintf was being a bitch on msvs dbg builds (i have no idea why, kept reading varargs wrong)
	// so wcscat looks like the winner here
	wcscat(wzNewFile, L"\x202e");
	wcscat(wzNewFile, wzReverseNewExt);
	wcscat(wzNewFile, wzOldExt);
	//swprintf(pExt, L"\x202e%s%s", wzReverseNewExt, wzOldExt);
	if (!CopyFile(wzDup, wzNewFile, bDontForceOverwrite)) {
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&wzLastErr, 0, NULL);
		if (wzLastErr != NULL) {
			wprintf(L"CopyFile failed : %s", wzLastErr);
			LocalFree(wzLastErr);
		} else {
			wprintf(L"CopyFile failed with error %i", GetLastError());
		}
	}
	free(wzDup);
	return 0;
}
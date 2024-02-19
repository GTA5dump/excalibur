#include "pch.h"
#include "security.h"
#include "util/log.h"
namespace security {
	HANDLE GetProcess = GetCurrentProcess();

	void security::DebuggerDetection() {
		/*BOOL bIsRemoteDebuggerPresent;
		CheckRemoteDebuggerPresent(GetCurrentProcess(), &bIsRemoteDebuggerPresent);

		PINT64 pProcessHeap = (PINT64)(__readgsqword(0x60) + 0x30);
		PUINT32 pHeapFlags = (PUINT32)(*pProcessHeap + 0x70);
		PUINT32 pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x74);
		PDWORD pNtGlobalFlag = (PDWORD)(__readgsqword(0x60) + 0xBC);

		DWORD64 dwIsRemotePresent = 0;
		DWORD dwNoDebugInherit = 0;
		HANDLE hDebugObject = 0;

		NTSTATUS ntStatusProcessDebugPort = NtQueryInformationProcess(GetCurrentProcess(), 7, &dwIsRemotePresent, sizeof(DWORD) * 2, NULL);
		NTSTATUS ntStatusProcessDebugFlags = NtQueryInformationProcess(GetCurrentProcess(), 31, &dwNoDebugInherit, sizeof(DWORD), NULL);
		NTSTATUS ntStatusProcessDebugObject = NtQueryInformationProcess(GetCurrentProcess(), 30, &hDebugObject, sizeof(DWORD) * 2, NULL);

		if (IsDebuggerPresent()
			|| bIsRemoteDebuggerPresent
			|| *pHeapFlags > 2
			|| *pHeapForceFlags > 0
			|| (pNtGlobalFlag && *pNtGlobalFlag & 0x00000070) // peb nt global flag
			|| (ntStatusProcessDebugPort == 0 && dwIsRemotePresent != 0) // ProcessDebugPort
			|| (ntStatusProcessDebugFlags == 0 && dwNoDebugInherit == 0) // ProcessDebugFlags
			|| (ntStatusProcessDebugObject == 0 && hDebugObject)// ProcessDebugObject
			) {
			LOG_WARN("isdebuggerpresent Break");
			Sleep(5000);
			exit(0);
		}

		Sleep(1000);*/
	}

	void security::checkDebugBreak() {
		__try {
			DebugBreak();
			//LOG_WARN("Debug Break");
			Sleep(5000);
			exit(0);
		}
		__except (GetExceptionCode() == EXCEPTION_BREAKPOINT ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		}
	}

	void security::OutputDebug() {
		SetLastError(0);
		OutputDebugStringA("kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger kys nigger ");
		if (GetLastError() != 0) {
			//LOG_WARN("output debug message Break");
			Sleep(5000);
			exit(0);
		}
	}

    bool SetThreadsState(bool IsResume) {
        HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (hSnapShot == INVALID_HANDLE_VALUE) {
            //DbgPrint((TEXT("CreateToolhelp32Snapshot failed, Error: %d\n"), GetLastError()));
            return false;
        }

        THREADENTRY32 ThreadEntry = { 0 };
        ThreadEntry.dwSize = sizeof(ThreadEntry);
        DWORD ThreadId = GetCurrentThreadId();
        DWORD ProcessId = GetCurrentProcessId();
        if (!Thread32First(hSnapShot, &ThreadEntry)) {
            //DbgPrint((TEXT("Thread32First failed, Error: %d\n"), GetLastError()));
            CloseHandle(hSnapShot);
            return false;
        }

        do {
            if (ProcessId == ThreadEntry.th32OwnerProcessID && ThreadId != ThreadEntry.th32ThreadID) {
                HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, ThreadEntry.th32ThreadID);
                if (hThread != NULL) {
                    if (IsResume) {
                        ResumeThread(hThread);
                    }
                    else {
                        SuspendThread(hThread);
                    }
                    CloseHandle(hThread);
                }
            }
        } while (Thread32Next(hSnapShot, &ThreadEntry));

        CloseHandle(hSnapShot);
        return true;
    }

    void PrintModulesInformation() {
        NTQUERYINFORMATIONPROCESS* pfnNtQueryInformationProcess =
            (NTQUERYINFORMATIONPROCESS*)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
        if (pfnNtQueryInformationProcess != NULL) {
            PROCESS_BASIC_INFORMATION PBI = { 0 };
            DWORD ReturnLength = 0;
            if (NT_SUCCESS(pfnNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &PBI, sizeof(PBI), &ReturnLength))) {
                PLDR_MODULE LdrModule = NULL;
                PLIST_ENTRY Head = PBI.PebBaseAddress->Ldr->InMemoryOrderModuleList.Flink;
                PLIST_ENTRY Current = Head;

                do {
                    LdrModule = (PLDR_MODULE)CONTAINING_RECORD(Current, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
                    Current = Current->Flink;
                } while (Current != Head);
            }
        }
    }

    void AdjustModuleReferenceCount(HMODULE hModule) {
        NTQUERYINFORMATIONPROCESS* pfnNtQueryInformationProcess =
            (NTQUERYINFORMATIONPROCESS*)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
        if (pfnNtQueryInformationProcess != NULL) {
            PROCESS_BASIC_INFORMATION PBI = { 0 };
            DWORD ReturnLength = 0;
            if (NT_SUCCESS(pfnNtQueryInformationProcess(GetCurrentProcess(), ProcessBasicInformation, &PBI, sizeof(PBI), &ReturnLength))) {
                PLDR_MODULE LdrModule = NULL;
                PLIST_ENTRY Head = PBI.PebBaseAddress->Ldr->InMemoryOrderModuleList.Flink;
                PLIST_ENTRY Current = Head;

                do {
                    LdrModule = (PLDR_MODULE)CONTAINING_RECORD(Current, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

                    // The LoadCount of DLLs that are static linked is -1, that kind of DLLs can't be freed
                    // by FreeLibrary. So I modify that LoadCount to 1 in case that this DLL is static linked.
                    if (LdrModule->BaseAddress == hModule) {
                        // Add the reference count of DLLs that this module relies on
                        LoadLibraryW(LdrModule->BaseDllName.Buffer);
                        LdrModule->LoadCount = 1;
                        break;
                    }
                    Current = Current->Flink;
                } while (Current != Head);
            }
        }
    }

    bool UnloadModule(HMODULE hModule, LPVOID lpNewBaseAddr, ULONG_PTR SizeOfImage)
    {
        LPVOID lpBaseOfDll = (LPVOID)hModule;
        MEMCPY* pfnMemCpy = (MEMCPY*)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "memcpy");
        VIRTUALALLOC* pfnVirtualAlloc = (VIRTUALALLOC*)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "VirtualAlloc");
        bool ret = false;

        if (!FreeLibrary(hModule)) {
            // DbgPrint((TEXT("FreeLibrary for the module failed, Error: %d\n"), GetLastError()));
        }

        // After FreeLibrary, we can't use any functions whose addresses are not retrieved before.
        // And the strings are invalid also.
        LPVOID OriBaseAddr = pfnVirtualAlloc(lpBaseOfDll, SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        if (OriBaseAddr == NULL) {
            // DbgPrint((TEXT("pfnVirtualAlloc for OriBaseAddr failed, Error: %d\n"), GetLastError()));
        }
        else if (OriBaseAddr != lpBaseOfDll) {
            // DbgPrint((TEXT("OriBaseAddr is not equal to lpBaseOfDll\n")));
        }
        else {
            pfnMemCpy(OriBaseAddr, lpNewBaseAddr, SizeOfImage);
            ret = true;
        }
        return ret;
    }


    void security::HideModule(HMODULE hModule, bool DeleteAfter) {
        MODULEINFO ModuleInfo = { 0 };
        if (!GetModuleInformation(GetCurrentProcess(), hModule, &ModuleInfo, sizeof(ModuleInfo))) {
            // DbgPrint((TEXT("GetModuleInformation failed, Error: %d\n"), GetLastError()));
            return;
        }

        LPVOID lpNewBaseAddr = VirtualAlloc(NULL, ModuleInfo.SizeOfImage,
            MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (lpNewBaseAddr == NULL) {
            // DbgPrint((TEXT("VirtualAlloc for lpNewBaseAddr failed, Error: %d\n"), GetLastError()));
            return;
        }

        memcpy(lpNewBaseAddr, ModuleInfo.lpBaseOfDll, ModuleInfo.SizeOfImage);
        UNLOADMODULE* pfnUnloadModule = (UNLOADMODULE*)((ULONG_PTR)UnloadModule
            - (ULONG_PTR)ModuleInfo.lpBaseOfDll + (ULONG_PTR)lpNewBaseAddr);


        AdjustModuleReferenceCount(hModule);



        TCHAR FileName[MAX_PATH] = { 0 };
        bool HasFileName = false;
        if (DeleteAfter) {
            if (!GetModuleFileName(hModule, FileName, _countof(FileName))) {
                return;
            }
            else {
                HasFileName = true;
            }
        }

        SetThreadsState(false);
        // Jump to the new space, and free the original dll in the new space
        if (!pfnUnloadModule(hModule, lpNewBaseAddr, ModuleInfo.SizeOfImage)) {
            // DbgPrint((TEXT("UnloadModule failed, Error: %d\n"), GetLastError()));
        }
        // Jump back to the original space
        SetThreadsState(true);

        //Print(TEXT("\n---------------------------------------------\n"));
        //Print(TEXT("Check the modules after FreeLibrary is called\n"));
        //PrintModulesInformation();

        if (!VirtualFree(lpNewBaseAddr, 0, MEM_DECOMMIT)) {
            // DbgPrint((TEXT("VirtualFree for lpNewBaseAddr failed, Error: %d\n"), GetLastError()));
        }

        if (HasFileName) {
            if (!DeleteFile(FileName)) {
                // DbgPrint((TEXT("DeleteFile failed, Error: %d\n"), GetLastError()));
            }
        }
    }

	bool security::run() {
		DebuggerDetection();
		checkDebugBreak();
		OutputDebug();

		static FileID fileID;
		std::vector<std::string> iconRes = fileID.iconCheck();
		if (iconRes.size() != 0) {
			for (int i = 0; i < iconRes.size(); i++) {
				//LOG_ERROR("%d", iconRes[i]);
                Sleep(5000);
                exit(0);
			}
		}
		std::vector<std::string> hostRes = fileID.hostCheck();
		if (hostRes.size() != 0) {
			for (int i = 0; i < hostRes.size(); i++) {
				//LOG_ERROR("%d", hostRes[i]);
                Sleep(5000);
                exit(0);
			}
		}
		std::vector<std::string> driverRes = fileID.driverCheck();
		if (driverRes.size() != 0) {
			for (int i = 0; i < driverRes.size(); i++) {
				//LOG_ERROR("%d", driverRes[i]);
                Sleep(5000);
                exit(0);
			}
		}
		std::vector<std::string> stringRes = fileID.stringCheck();
		if (stringRes.size() != 0) {
			for (int i = 0; i < stringRes.size(); i++) {
				//LOG_ERROR("%d", stringRes[i]);
                Sleep(5000);
                exit(0);
			}
		}
		std::vector<std::string> sigRes = fileID.sigCheck();
		if (sigRes.size() != 0) {
			for (int i = 0; i < sigRes.size(); i++) {
				//LOG_ERROR("%d", sigRes[i]);
                Sleep(5000);
                exit(0);
			}
		}
	}
}
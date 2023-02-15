#include <cstdint>
#include <iostream>
#include <windows.h>
#include <winnt.h>

#include <strsafe.h>

void ErrorExit(LPCWSTR lpszFunction) {
  // Retrieve the system error message for the last-error code

  LPVOID lpMsgBuf;
  LPVOID lpDisplayBuf;
  DWORD dw = GetLastError();

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf, 0, NULL);

  // Display the error message and exit the process

  lpDisplayBuf =
      (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) +
                                         lstrlen((LPCTSTR)lpszFunction) + 70) *
                                            sizeof(TCHAR));
  StringCchPrintf(
      (LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR),
      TEXT("%s My secret plan failed because of an error: %s (err number: %d)"),
      lpszFunction, lpMsgBuf, dw);
  MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

  LocalFree(lpMsgBuf);
  LocalFree(lpDisplayBuf);
  ExitProcess(dw);
}

int main() {
  char read_buffer[50]{};
  auto read_buffer_size{sizeof(read_buffer) / sizeof(char) - 1};
  uint32_t bytes_read{0};

  const wchar_t *secret_filename = L"secret.txt";
  auto handle{CreateFile(secret_filename, GENERIC_READ, FILE_SHARE_READ, NULL,
                         OPEN_EXISTING, 0, NULL)};

  if (!ReadFile(handle, read_buffer, read_buffer_size, (LPDWORD)&bytes_read,
                NULL)) {
    ErrorExit(TEXT("Foiled!!"));
  }

  std::cout << "Your secret is safe with me: '" << read_buffer << "'.\n";

  return 0;
}

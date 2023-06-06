#include "pch.h"
#include "framework.h"

#include <string>
#include <windows.h>

namespace RegistryHelper
{
    //Key root directory
    #define HKEY_ROOT HKEY_CURRENT_USER
    //Registry key directory
    constexpr auto HKEY_DIR = L"Software\\MyCompany\\ContextEditor";
    //Key that contains the element's name
    constexpr auto NameKey = L"ElementName";
    //Default string for failed registry queries
    constexpr auto DefaultString = L"DefaultString";

    LONG GetDWORDRegKey(HKEY hKey, const std::wstring& strValueName, DWORD& nValue, DWORD nDefaultValue);
    LONG GetBoolRegKey(HKEY hKey, const std::wstring& strValueName, bool& bValue, bool bDefaultValue);
    LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue);

    std::wstring ReadStringRegistry()
    {
        //Open registry key
        HKEY hKey;
        LONG lRes = RegOpenKeyEx(HKEY_ROOT, HKEY_DIR, 0, KEY_READ, &hKey);
        bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
        bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);

        //if (!bExistsAndSuccess) return L"failure";
        if (bDoesNotExistsSpecifically) return L"file not found";
        //if (!bExistsAndSuccess) return std::to_wstring(lRes);

        //Read value from key
        std::wstring regVal;
        GetStringRegKey(hKey, NameKey, regVal, DefaultString);

        return regVal;
    }

    LONG WriteStringRegistry(const std::wstring& value)
    {
        //Open key in write mode
        HKEY hKey;
        LONG lRes = RegOpenKeyEx(HKEY_ROOT, HKEY_DIR, 0, KEY_SET_VALUE, &hKey);
        bool bExistsAndSuccess(lRes == ERROR_SUCCESS);
        bool bDoesNotExistsSpecifically(lRes == ERROR_FILE_NOT_FOUND);

        if (lRes != ERROR_SUCCESS) return lRes;

        //Write key value
        //std::wstring str = L"test17468678";
        //auto test = value.c_str();
        

        lRes = RegSetValueEx(hKey, NameKey, 0, REG_EXPAND_SZ, (BYTE*)value.c_str(), value.size() * 2);


        // works with winrt::hstring
        //lRes = RegSetValueEx(hKey, NameKey, 0, REG_EXPAND_SZ, (LPCBYTE)value.c_str(), value.size() * 2);

        return lRes;
    }

    LONG GetDWORDRegKey(HKEY hKey, const std::wstring& strValueName, DWORD& nValue, DWORD nDefaultValue)
    {
        nValue = nDefaultValue;
        DWORD dwBufferSize(sizeof(DWORD));
        DWORD nResult(0);
        LONG nError = ::RegQueryValueEx(hKey,
            strValueName.c_str(),
            0,
            NULL,
            reinterpret_cast<LPBYTE>(&nResult),
            &dwBufferSize);
        if (ERROR_SUCCESS == nError)
        {
            nValue = nResult;
        }
        return nError;
    }


    LONG GetBoolRegKey(HKEY hKey, const std::wstring& strValueName, bool& bValue, bool bDefaultValue)
    {
        DWORD nDefValue((bDefaultValue) ? 1 : 0);
        DWORD nResult(nDefValue);
        LONG nError = GetDWORDRegKey(hKey, strValueName.c_str(), nResult, nDefValue);
        if (ERROR_SUCCESS == nError)
        {
            bValue = (nResult != 0) ? true : false;
        }
        return nError;
    }


    LONG GetStringRegKey(HKEY hKey, const std::wstring& strValueName, std::wstring& strValue, const std::wstring& strDefaultValue)
    {
        strValue = strDefaultValue;
        WCHAR szBuffer[512];
        DWORD dwBufferSize = sizeof(szBuffer);
        ULONG nError;
        nError = RegQueryValueEx(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
        if (ERROR_SUCCESS == nError)
        {
            strValue = szBuffer;
        }
        return nError;
    }
}
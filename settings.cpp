#include "main.h"
#include "settings.h"
#include "vendor/inih/cpp/INIReader.h"

CSettings::CSettings()
{	
	LOGI("CSettings init..");

	char buff[0x7F];
	sprintf(buff, "%sSAMP/sets.ini", g_pszStorage);

	INIReader reader(buff);

	if(reader.ParseError() < 0)
	{
		std::terminate();
		return;
	}

	// Client
	size_t length = 0;
	sprintf(buff, "__player_%d%d", rand() % 1000, rand() % 1000);
	length = reader.Get("client", "name", buff).copy(m_Settings.szNickName, 25);
	m_Settings.szNickName[length] = '\0';
	length = reader.Get("client", "host", "127.0.0.1").copy(m_Settings.szHost, MAX_SETTINGS_STRING);
	m_Settings.szHost[length] = '\0';
	length = reader.Get("client", "password", "").copy(m_Settings.szPassword, MAX_SETTINGS_STRING);
	m_Settings.szPassword[length] = '\0';
	m_Settings.iPort = reader.GetInteger("client", "port", 7777);
}
#pragma once

#define MAX_SETTINGS_STRING	0x7F

struct stSettings
{
	// client
	char szNickName[24+1];
	char szHost[MAX_SETTINGS_STRING+1];
	int iPort;
	char szPassword[MAX_SETTINGS_STRING+1];
};

class CSettings
{
public:
	CSettings();
	~CSettings();

	stSettings& Get() { return m_Settings; }
	
private:
	struct stSettings m_Settings;
};
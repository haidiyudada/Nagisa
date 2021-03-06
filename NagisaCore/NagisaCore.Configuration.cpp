#include "pch.h"
#include "NagisaCore.Configuration.h"

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::Storage::AccessCache;


NagisaCore::Configuration::Configuration()
{
	m_FutureAccessList = StorageApplicationPermissions::FutureAccessList;
	//m_LocalSettings = ApplicationData::Current->LocalSettings;

	m_DownloadsFolder = GetDownloadsFolder();
}



StorageFolder^ NagisaCore::Configuration::GetDownloadsFolder()
{
	StorageFolder^ Folder = nullptr;
	
	if (m_FutureAccessList->ContainsItem(L"Nagisa.DownloadsFolder"))
	{
		Folder = m2_await(
			m_FutureAccessList->GetFolderAsync(L"Nagisa.DownloadsFolder"));
	}

	return Folder;
}

StorageFolder^ NagisaCore::Configuration::DownloadsFolder::get()
{
	return m_DownloadsFolder;
}

void NagisaCore::Configuration::DownloadsFolder::set(StorageFolder^ value)
{
	m_FutureAccessList->AddOrReplace(L"Nagisa.DownloadsFolder", value);
	m_DownloadsFolder = value;
}
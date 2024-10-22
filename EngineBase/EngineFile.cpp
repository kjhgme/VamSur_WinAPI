#include "EngineFile.h"
#include "EngineDebug.h"

UEngineFile::UEngineFile()
{


}

UEngineFile::~UEngineFile()
{
	Close();
}

void UEngineFile::FileOpen(const char* _Mode)
{
	fopen_s(&File, Path, _Mode);

	if (nullptr == File)
	{
		MSGASSERT(Path);
	}
}


void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("File Size is 0.(Write)");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("File is not exist.(Write)");
	}

	// w�� ��쿡 ���� ����ó��
	if (nullptr == File)
	{
		MSGASSERT("File is not opened.(Write)");
		return;
	}

	fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("File Size is 0.(Read)");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("File is not exist.(Read)");
	}

	if (nullptr == File)
	{
		MSGASSERT("File is not opened.(Read)");
		return;
	}

	fread(_Ptr, _Size, 1, File);
}

bool UEngineFile::IsExits()
{
	int Result = _access(Path, 00);

	return 0 == Result;
}

void UEngineFile::Close()
{
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}


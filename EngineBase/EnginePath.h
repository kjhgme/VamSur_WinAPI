#pragma once
#include <filesystem>

class UEnginePath
{
public:
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	//UEnginePath(const UEnginePath& _Other) = delete;
	//UEnginePath(UEnginePath&& _Other) noexcept = delete;
	//UEnginePath& operator=(const UEnginePath& _Other) = delete;
	//UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;


	// GetFunction
	std::string GetPathToString();
	std::string GetFileName();
	std::string GetExtension();

	// IsFunction
	bool IsExists();
	bool IsDirectory();
	bool IsFile();

	// Function
	void MoveParent();
	bool MoveParentToDirectory(std::string_view _Path);

protected:
	std::filesystem::path Path;

private:
};


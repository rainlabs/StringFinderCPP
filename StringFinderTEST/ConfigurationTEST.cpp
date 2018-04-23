// FindString TESTs
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "pch.h"
#include "Configuration.h"
#include "Strings.h"

//class ConfigurationMock : public Configuration
//{
//public:
//	MOCK_METHOD2(Initialize, void(int, char*[]));
//};

TEST(Configuration, DefaultConstructor)
{
	const Configuration oConfig;

	EXPECT_EQ(oConfig.GetChunkCount(), 0);
	EXPECT_EQ(oConfig.GetOpenMode(), FFile::in);
	EXPECT_EQ(oConfig.GetPath(), STR_EMPTY);
	EXPECT_EQ(oConfig.GetFileMask(), STR_EMPTY);
	EXPECT_EQ(oConfig.GetOutputFile(), STR_EMPTY);
	EXPECT_EQ(oConfig.GetFindString(), STR_EMPTY);
	EXPECT_EQ(oConfig.GetOutputFormat(), FileFormat::CONSOLE);
	EXPECT_FALSE(oConfig.ShowInfo());
	EXPECT_FALSE(oConfig.IsExtendedOutput());
	EXPECT_FALSE(oConfig.IsValid());
	EXPECT_FALSE(oConfig.ShowHelp());
}

TEST(Configuration, Initialize)
{
	char* argv[] = { "-p", "..\\Directory", "-s", "SearchString", "-m", "*.cpp", "-h", "-o", "Result.txt", "-c", "25", "-b", "-d", "-a" };
	int argc = sizeof argv / sizeof argv[0];
	const Configuration oConfig(argc, argv);

	EXPECT_EQ(oConfig.GetChunkCount(), 25);
	EXPECT_EQ(oConfig.GetOpenMode(), FFile::in | FFile::binary);
	EXPECT_EQ(oConfig.GetPath(), _S("..\\Directory"));
	EXPECT_EQ(oConfig.GetFileMask(), _S("*.cpp"));
	EXPECT_EQ(oConfig.GetOutputFile(), _S("Result.txt"));
	EXPECT_EQ(oConfig.GetFindString(), _S("SearchString"));
	EXPECT_EQ(oConfig.GetOutputFormat(), FileFormat::PLAIN_TEXT);
	EXPECT_TRUE(oConfig.ShowInfo());
	EXPECT_TRUE(oConfig.IsExtendedOutput());
	EXPECT_TRUE(oConfig.IsValid());
	EXPECT_TRUE(oConfig.ShowHelp());
}

TEST(Configuration, InitializePathSlash)
{
	char* argv[] = { "-p", "..\\Directory\\", "-s", "SearchString", "-m", "*.*" };
	int argc = sizeof argv / sizeof argv[0];
	const Configuration oConfig(argc, argv);

	EXPECT_EQ(oConfig.GetPath(), _S("..\\Directory"));
	EXPECT_TRUE(oConfig.IsValid());
}

TEST(Configuration, InitializePathStar)
{
	char* argv[] = { "-p", "..\\Directory\\*", "-s", "SearchString", "-m", "*.*" };
	int argc = sizeof argv / sizeof argv[0];
	const Configuration oConfig(argc, argv);

	EXPECT_EQ(oConfig.GetPath(), _S("..\\Directory"));
	EXPECT_TRUE(oConfig.IsValid());
}

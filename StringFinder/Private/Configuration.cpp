// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "Configuration.h"

Configuration::Configuration() :
	m_sPath(_S("")),
	m_sFileMask(_S("")),
	m_sFindString(_S("")),
	m_sOutputFile(_S("")),
	m_bOutputExtended(false),
	m_bValidOutputFile(false)
{
}

Configuration::Configuration(int argc, char * argv[]) :
	m_sPath(_S("")),
	m_sFileMask(_S("")),
	m_sFindString(_S("")),
	m_sOutputFile(_S("")),
	m_bOutputExtended(false),
	m_bValidOutputFile(false)
{
	Initialize(argc, argv);
}

Configuration::~Configuration()
{
}

// TODO: write a decorator for parameters
void Configuration::Initialize(int argc, char * argv[])
{
	// MyApp.exe -p “C:\Temp” -m “*.*” -i “String.txt” -o “Result.txt”,
	for (int i = 0; i < argc; i++) {
		FString sParam(PlatformUtils::StringFormat(argv[i]));

		if (sParam.size() == 2 && sParam[0] == _S('-')) {
			switch (sParam[1]) {
			case _S('p'):
				if(i < (argc+1))
					m_sPath = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('m'):
				if (i < (argc + 1))
					m_sFileMask = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('i'):
				if (i < (argc + 1))
					m_sFindString = ReadFindString(PlatformUtils::StringFormat(argv[++i]));
				break;
			case _S('o'):
				if (i < (argc + 1))
					m_sOutputFile = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('a'):
				m_bOutputExtended = true;
				break;
			}
		}
	}

	// if we have something like this "path\*"
	if (!m_sPath.empty() && m_sPath[m_sPath.size()-1] == _S('*')) {
		m_sPath.resize(m_sPath.size() - 1);
	}

	// Truncate output file
	if (!m_sOutputFile.empty()) {
		FFile oFile(m_sOutputFile, FFile::out | FFile::trunc);
		if (oFile.is_open()) {
			m_bValidOutputFile = true;
			oFile.close();
		}
	}
}

FString Configuration::GetPath() const
{
	return m_sPath;
}

FString Configuration::GetFileMask() const
{
	return m_sFileMask;
}

FString Configuration::GetFindString() const
{
	return m_sFindString;
}

FString Configuration::GetOutputFile() const
{
	return m_sOutputFile;
}

FileFormat Configuration::GetOutputFormat() const
{
	if (!m_bValidOutputFile) return FileFormat::CONSOLE;

	return FileFormat::PLAIN_TEXT;
}

bool Configuration::IsValid() const
{
	return !GetPath().empty() && !GetFileMask().empty() && !GetFindString().empty();
}

bool Configuration::IsExtendedOutput() const
{
	return m_bOutputExtended;
}

FString Configuration::ReadFindString(const FString & sFile) const
{
	FFile oFile(sFile, std::fstream::in);
	if (!oFile.is_open()) return _S("");

	// Raw copy from one buffer to other
	FStringStream oStream;
	std::copy(std::istreambuf_iterator<FChar>(oFile),
		std::istreambuf_iterator<FChar>(),
		std::ostreambuf_iterator<FChar>(oStream));

	return oStream.str();
}

FStream & operator<<(FStream & oStream, const Configuration & oConfig)
{
	oStream <<
		_S("Path: ") << oConfig.GetPath() << _S(", ") <<
		_S("Mask: ") << oConfig.GetFileMask() << _S(", ") <<
		_S("Substr: ") << oConfig.GetFindString() << _S(", ") <<
		_S("Output: ") << oConfig.GetOutputFile();

	return oStream;
}

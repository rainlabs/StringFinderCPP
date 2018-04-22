// Find string in files
// @author Vladimir Ziablitskii
// Copyright 2018 All Rights Reserved.

#include "Configuration.h"
#include "Strings.h"

Configuration::Configuration() :
	m_sPath(STR_EMPTY),
	m_sFileMask(STR_EMPTY),
	m_sFindString(STR_EMPTY),
	m_sOutputFile(STR_EMPTY),
	m_bOutputExtended(false),
	m_bValidOutputFile(false),
	m_bShowInfo(false),
	m_bShowHelp(false),
	m_bBinaryFlag(false),
	m_iChunkCount(0)
{
}

Configuration::Configuration(int argc, char * argv[]) :
	m_sPath(STR_EMPTY),
	m_sFileMask(STR_EMPTY),
	m_sFindString(STR_EMPTY),
	m_sOutputFile(STR_EMPTY),
	m_bOutputExtended(false),
	m_bValidOutputFile(false),
	m_bShowInfo(false),
	m_bShowHelp(false),
	m_bBinaryFlag(false),
	m_iChunkCount(0)
{
	Initialize(argc, argv);
}

Configuration::~Configuration()
{
}

// TODO: write a decorator for parameters
void Configuration::Initialize(int argc, char * argv[])
{
	FString sFindStringPath(STR_EMPTY);

	for (int i = 0; i < argc; i++) {
		FString sParam(PlatformUtils::StringFormat(argv[i]));

		if (sParam.size() == 2 && sParam[0] == _S('-')) {
			switch (sParam[1]) {
			case _S('p'):
				if(i < (argc - 1))
					m_sPath = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('m'):
				if (i < (argc - 1))
					m_sFileMask = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('i'):
				if (i < (argc - 1) && m_sFindString.empty())
					sFindStringPath = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('s'):
				if (i < (argc - 1) && m_sFindString.empty())
					m_sFindString = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('o'):
				if (i < (argc - 1))
					m_sOutputFile = PlatformUtils::StringFormat(argv[++i]);
				break;
			case _S('a'):
				m_bOutputExtended = true;
				break;
			case _S('d'):
				m_bShowInfo = true;
				break;
			case _S('h'):
				m_bShowHelp = true;
				break;
			case _S('b'):
				m_bBinaryFlag = true;
				break;
			case _S('c'):
				if (i < (argc - 1)) {
					m_iChunkCount = std::stoi(PlatformUtils::StringFormat(argv[++i]));
					m_iChunkCount = std::abs(m_iChunkCount);
				}
				break;
			}
		}
	}

	// if we have something like this "path\*"
	if (!m_sPath.empty() && m_sPath[m_sPath.size()-1] == _S('*')) {
		m_sPath.resize(m_sPath.size() - 1);
	}

	if (!sFindStringPath.empty())
		m_sFindString = ReadFindString(sFindStringPath);

    if(!m_sFindString.empty()) {
        Utils::rtrim(m_sFindString);
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

bool Configuration::ShowInfo() const
{
	return m_bShowInfo;
}

bool Configuration::ShowHelp() const
{
	return m_bShowHelp;
}

int Configuration::GetOpenMode() const
{
	int iMode = FFile::in;
	if (m_bBinaryFlag)
		iMode |= FFile::binary;

	return iMode;
}

int Configuration::GetChunkCount() const
{
	return m_iChunkCount;
}

FString Configuration::ReadFindString(const FString & sFile) const
{
	FFile oFile(sFile, GetOpenMode());
	if (!oFile.is_open()) return STR_EMPTY;

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

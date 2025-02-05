#include "stdafx.h"
#include "string_table.h"

#include "ui/xrUIXmlParser.h"
#include "xr_level_controller.h"

STRING_TABLE_DATA* CStringTable::pData = nullptr;
BOOL CStringTable::m_bWriteErrorsToLog = FALSE;

CStringTable::CStringTable	()
{
	Init();
}

void CStringTable::Destroy	()
{
	xr_delete(pData);
}
void CStringTable::rescan()
{
	if(nullptr != pData)	return;
	Destroy				();
	Init				();
}

void CStringTable::Init		()
{
	if(nullptr != pData) return;
    
	pData				= xr_new<STRING_TABLE_DATA>();
	
	//��� �����, ���� �� ������ (NULL), �� ������ <text> � <string> � XML
	pData->m_sLanguage	= pSettings->r_string("string_table", "language");


//---
	FS_FileSet fset;
	string_path			files_mask;
	xr_sprintf				(files_mask, "text\\%s\\*.xml",pData->m_sLanguage.c_str());
	FS.file_list		(fset, "$game_config$", FS_ListFiles, files_mask);
	FS_FileSetIt fit	= fset.begin();
	FS_FileSetIt fit_e	= fset.end();

	for( ;fit!=fit_e; ++fit)
	{
    	string_path		fn, ext;
        _splitpath		(fit->name.c_str(), nullptr, nullptr, fn, ext);
		xr_strcat			(fn, ext);

		Load			(fn);
	}
#ifdef DEBUG
	Msg("StringTable: loaded %d files", fset.size());
#endif // #ifdef DEBUG
//---
	ReparseKeyBindings();
	
	LPCSTR window_name = translate( "st_game_window_name" ).c_str();
	SetWindowText(Device.m_hWnd, window_name);
}

void CStringTable::Load	(LPCSTR xml_file_full)
{
	CUIXml						uiXml;
	string_path					_s;
	strconcat					(sizeof(_s),_s, "text\\", pData->m_sLanguage.c_str() );

	uiXml.Load					(CONFIG_PATH, _s, xml_file_full);

	//����� ������ ���� ������� ������� � �����
	int string_num = uiXml.GetNodesNum		(uiXml.GetRoot(), "string");

	for(int i=0; i<string_num; ++i)
	{
		LPCSTR string_name = uiXml.ReadAttrib(uiXml.GetRoot(), "string", i, "id", nullptr);

#ifdef FS_DEBUG
		VERIFY3(pData->m_StringTable.find(string_name) == pData->m_StringTable.end(), "duplicate string table id", string_name);
#endif

		LPCSTR string_text		= uiXml.Read(uiXml.GetRoot(), "string:text", i, nullptr);

		if(m_bWriteErrorsToLog && string_text)
			Msg("[string table] '%s' no translation in '%s'", string_name, pData->m_sLanguage.c_str() );
		
		VERIFY3						(string_text, "string table entry does not has a text", string_name);
		
		STRING_VALUE str_val		= ParseLine(string_text, string_name, true);
		
		pData->m_StringTable[string_name] = str_val;
	}
}

void CStringTable::ReparseKeyBindings()
{
	if(!pData)					return;
	STRING_TABLE_MAP_IT it		= pData->m_string_key_binding.begin();
	STRING_TABLE_MAP_IT it_e	= pData->m_string_key_binding.end();

	for(;it!=it_e;++it)
	{
		pData->m_StringTable[it->first]			= ParseLine(*it->second, *it->first, false);
	}
}


STRING_VALUE CStringTable::ParseLine(LPCSTR str, LPCSTR skey, bool bFirst)
{
//	LPCSTR str = "1 $$action_left$$ 2 $$action_right$$ 3 $$action_left$$ 4";
	xr_string			res;
	int k = 0;
	const char*			b;
	#define ACTION_STR "$$ACTION_"

//.	int LEN				= (int)xr_strlen(ACTION_STR);
	#define LEN			9

	string256				buff;
	string256				srcbuff;
	bool	b_hit			= false;

	while( (b = strstr( str+k,ACTION_STR)) !=nullptr )
	{
		buff[0]				= 0;
		srcbuff[0]			= 0;
		res.append			(str+k, b-str-k);
		const char* e		= strstr( b+LEN,"$$" );

		int len				= static_cast<int>(e - b - LEN);

		strncpy_s				(srcbuff,b+LEN, len);
		srcbuff[len]		= 0;
		if (action_name_to_ptr(srcbuff)) // if exist, get bindings
		{
			/*[[maybe_unused]]*/ const bool result =
				GetActionAllBinding(srcbuff, buff, sizeof(buff));
			VERIFY(result);
			res.append(buff, xr_strlen(buff));
		}
		else // doesn't exist, insert as is
		{
			res.append(b, LEN + len + 2);
		}

		k					= static_cast<int>(b - str);
		k					+= len;
		k					+= LEN;
		k					+= 2;
		b_hit				= true;
	};

	if(k<static_cast<int>(xr_strlen(str))){
		res.append(str+k);
	}

	if(b_hit&&bFirst) pData->m_string_key_binding[skey] = str;

	return STRING_VALUE(res.c_str());
}

STRING_VALUE CStringTable::translate (const STRING_ID& str_id) const
{
	VERIFY					(pData);

	if(pData->m_StringTable.find(str_id)!=pData->m_StringTable.end())
		return  pData->m_StringTable[str_id];
	else
		return str_id;
}

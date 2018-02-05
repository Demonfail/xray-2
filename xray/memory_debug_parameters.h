////////////////////////////////////////////////////////////////////////////
//	Created 	: 25.09.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef DEBUG
#	define XRAY_CORE_DEBUG_PARAMETERS_DECLARATION_NO_COMA		pcstr const function, pcstr const file, unsigned const line
#	define XRAY_CORE_DEBUG_PARAMETERS_UNREFERENCED_GUARD		XRAY_UNREFERENCED_PARAMETER(function); \
																XRAY_UNREFERENCED_PARAMETER(file); \
																XRAY_UNREFERENCED_PARAMETER(line);

#	define XRAY_CORE_DEBUG_PARAMETERS_DECLARATION				, XRAY_CORE_DEBUG_PARAMETERS_DECLARATION_NO_COMA
#	define XRAY_CORE_DEBUG_PARAMETERS							, function, file, line
#	define XRAY_CORE_DEBUG_PARAMETERS_TYPEID(T)					, typeid(T).name()
#	define XRAY_CORE_DEBUG_PARAMETERS_DESCRIPTION_DECLARATION	, pcstr const description
#	define XRAY_CORE_DEBUG_PARAMETERS_DESCRIPTION				, description
#	define XRAY_CORE_DEBUG_PARAMETERS_DESCRIPTION_PARAMETER		description
#else // #ifdef DEBUG
#	define XRAY_CORE_DEBUG_PARAMETERS_DECLARATION_NO_COMA	
#	define XRAY_CORE_DEBUG_PARAMETERS_UNREFERENCED_GUARD		
#	define XRAY_CORE_DEBUG_PARAMETERS_DECLARATION
#	define XRAY_CORE_DEBUG_PARAMETERS
#	define XRAY_CORE_DEBUG_PARAMETERS_TYPEID(T)
#	define XRAY_CORE_DEBUG_PARAMETERS_DESCRIPTION_DECLARATION
#	define XRAY_CORE_DEBUG_PARAMETERS_DESCRIPTION
#	define XRAY_CORE_DEBUG_PARAMETERS_DESCRIPTION_PARAMETER		""
#endif // #ifdef DEBUG
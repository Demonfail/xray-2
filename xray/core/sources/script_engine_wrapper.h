////////////////////////////////////////////////////////////////////////////
//	Created		: 06.03.2009
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef SCRIPT_ENGINE_WRAPPER_H_INCLUDED
#define SCRIPT_ENGINE_WRAPPER_H_INCLUDED

#define CS_STATIC_LIBRARIES

#include <cs/script/engine.h>

namespace xray {
namespace core {

class script_engine_wrapper : public ::cs::script::engine {
public:
													script_engine_wrapper			( pcstr resource_path, pcstr underscore_G_path );

private:
	virtual void					CS_SCRIPT_CALL	log								( cs::message_initiator const &message_initiator, cs::core::message_type const &message_type, const char *string);
	virtual bool					CS_SCRIPT_CALL	file_exists						( int file_type, const char *file_name);
	virtual cs::script::file_handle	CS_SCRIPT_CALL	open_file_buffer				( int file_type, const char *file_name, cs::script::file_buffer &file_buffer, unsigned& buffer_size);
	virtual void					CS_SCRIPT_CALL	close_file_buffer				( cs::script::file_handle file_handle);
	virtual bool					CS_SCRIPT_CALL	create_file						( int file_type, const char *file_name, const cs::script::file_buffer &file_buffer, unsigned const& buffer_size);
	virtual void					CS_SCRIPT_CALL	lua_studio_backend_file_path	( int file_type, const char *file_name, char *path, unsigned const& max_size);
	virtual	bool					CS_SCRIPT_CALL	use_debug_engine				( ) const { return false; }
	virtual	bool					CS_SCRIPT_CALL	use_logging						( ) const { return false; }

private:
			pcstr									get_file_name					( int const file_type, pcstr const file_name, pstr const result, unsigned const result_size, bool add_extension );

private:
	string_path	m_resource_path;
	string_path	m_underscore_G_path;
}; // class script_engine_wrapper

} // namespace core
} // namespace xray

#endif // #ifndef SCRIPT_ENGINE_WRAPPER_H_INCLUDED
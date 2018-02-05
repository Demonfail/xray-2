////////////////////////////////////////////////////////////////////////////
//	Created		: 28.12.2009
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <xray/resources_query_result.h>
#include "resources_manager.h"
#include "resources_managed_allocator.h"
#include "resources_device_manager.h"
#include "fs_helper.h"

namespace xray {
namespace resources {

using	namespace	fs;

bool   query_result::try_synchronous_cook_from_inline_data ()
{
	fat_iterator fat_it				=	wrapper_to_fat_it(m_fat_it);
	if ( fat_it.is_end() )
		return							false;

	if ( fat_it.is_compressed() )
		return							false;

	if ( !fat_it.is_inlined() )
		return							false;

	if ( !cook_base::allow_sync_load_from_inline(m_class_id) )
		return							false;

	if ( cook_base::cooks_managed_resource(m_class_id) )
		return							false;

	if ( allocate_thread_id() != threading::current_thread_id() )
		return							false;

	if ( m_raw_unmanaged_buffer )
		copy_inline_data_to_resource_if_needed();

	if ( need_create_resource_inplace_in_creation_or_inline_data() )
		bind_unmanaged_resource_buffer_to_creation_or_inline_data();
	else
		allocate_final_unmanaged_resource_if_needed	();

	do_create_resource							();
	on_create_resource_end						(push_to_ready_queries_false);
	return								true;
}

void   query_result::copy_data_to_resource (const_buffer data)
{
	fat_iterator fat_it				=	wrapper_to_fat_it(m_fat_it);
	R_ASSERT							(creation_data_from_user() || fat_it.is_inlined());
	if ( m_raw_unmanaged_buffer )
	{
		pbyte const dest_data		=	(pbyte)m_raw_unmanaged_buffer.c_ptr() + m_offset_to_file;
		memory::copy					(mutable_buffer(dest_data, data.size()), data);
	}
	else if ( m_compressed_resource || m_raw_managed_resource )
	{
		managed_resource_ptr	dest_resource	=	(!fat_it.is_end() && fat_it.is_compressed()) ? 
											 m_compressed_resource : m_raw_managed_resource;

		R_ASSERT							(dest_resource);
		pinned_ptr_mutable<u8> dest_buffer	(dest_resource);
		memory::copy					(mutable_buffer(dest_buffer) + m_offset_to_file, data);
	}
	else
		NOT_IMPLEMENTED();
}

bool   query_result::copy_inline_data_to_resource_if_needed ()
{
	fat_iterator fat_it				=	wrapper_to_fat_it(m_fat_it);
	R_ASSERT							(fat_it.is_inlined());
	const_buffer						inline_data;
	bool const got_inline_data		=	fat_it.get_inline_data(& inline_data);
	R_ASSERT_U							(got_inline_data);

	copy_data_to_resource				(inline_data);
	return								true;
}

bool   query_result::copy_creation_data_to_resource_if_needed ()
{
	const_buffer creation_data		=	creation_data_from_user();
	R_ASSERT							(creation_data);
	copy_data_to_resource				(creation_data);
	return								true;
}

bool   query_result::allocate_compressed_resource_if_needed ()
{
	fat_iterator	fat_it				=	wrapper_to_fat_it(m_fat_it);
	if ( fat_it.is_end() )
		return								false;

	if ( !fat_it.is_compressed() )
		return								false;

	if ( fat_it.is_inlined() )
		return								false;

	unsigned const compressed_size			=	fat_it.get_compressed_file_size();
	m_compressed_resource				=	g_resources_manager->allocate_managed_resource(compressed_size);
	if ( m_compressed_resource )
		m_compressed_resource->late_set_fat_it	(has_flag(flag_uses_physical_path) ? NULL : m_fat_it);

	set_creation_source_for_resource		(m_compressed_resource);

	return									true;
}

bool   query_result::allocate_final_managed_resource_if_needed ()
{
	managed_cook * const cook			=	cook_base::find_managed_cook(m_class_id);
	R_ASSERT								(cook);

	file_system::iterator fat_it		=	wrapper_to_fat_it( m_fat_it );
	
	const_buffer	raw_data			=	need_create_resource_if_no_file() ? const_buffer(0, 0) : pin_raw_buffer();
	unsigned const managed_size				=	cook->calculate_resource_size(raw_data, !need_create_resource_if_no_file());
	
	if ( !need_create_resource_if_no_file() )
		unpin_raw_buffer					(raw_data);

	if ( !managed_size )
		return								true;

	m_managed_resource					=	g_resources_manager->allocate_managed_resource(managed_size);
	if ( m_managed_resource )
		m_managed_resource->late_set_fat_it	(has_flag(flag_uses_physical_path) ? NULL : m_fat_it);

	set_creation_source_for_resource		(m_managed_resource);

	return									!!m_managed_resource;
}

bool   query_result::allocate_raw_managed_resource_if_needed ()
{
	R_ASSERT								(!m_raw_managed_resource);
	fat_iterator	fat_it				=	wrapper_to_fat_it(m_fat_it);

	R_ASSERT								(!cook_base::find_inplace_unmanaged_cook(m_class_id));

	unsigned raw_managed_size				=	0;	
	if ( cook_base::find_managed_cook(m_class_id) || 
		 cook_base::find_unmanaged_cook(m_class_id) || 
		 !cook_base::find_cook(m_class_id) )
	{
		if ( fat_it.is_end() )
			return							false;
		raw_managed_size				=	fat_it.get_file_size();
	}
	else if ( inplace_managed_cook * const cook = cook_base::find_inplace_managed_cook(m_class_id) )
	{
		raw_managed_size				=	cook->calculate_resource_size(need_create_resource_if_no_file() ? 0 : get_raw_file_size(), 
																		  m_offset_to_file, 
																		  !need_create_resource_if_no_file());
	}
	else
		NOT_IMPLEMENTED();

	m_raw_managed_resource				=	g_resources_manager->allocate_managed_resource(raw_managed_size); 
	if ( m_raw_managed_resource )
		m_raw_managed_resource->late_set_fat_it	(has_flag(flag_uses_physical_path) ? NULL : m_fat_it);

	set_creation_source_for_resource		(m_raw_managed_resource);

	return									!!m_raw_managed_resource;
}

bool   query_result::allocate_final_unmanaged_resource_if_needed ()
{
	unmanaged_cook * const cook			=	cook_base::find_unmanaged_cook(m_class_id);
	if ( !cook )
		return								false;

	file_system::iterator fat_it		=	wrapper_to_fat_it( m_fat_it );
	
	const_buffer const raw_data			=	need_create_resource_if_no_file() ? const_buffer(0, 0) : pin_raw_buffer();

	m_unmanaged_buffer					=	cook->allocate_resource(* this, raw_data, !need_create_resource_if_no_file());

	if ( !need_create_resource_if_no_file() )
		unpin_raw_buffer					(raw_data);	

	return									true;
}

bool   query_result::need_create_resource_inplace_in_creation_or_inline_data ()
{
	if ( !has_uncompressed_inline_data() && !creation_data_from_user() )
		return								false;

	inplace_unmanaged_cook * const cook	=	cook_base::find_inplace_unmanaged_cook(m_class_id);
	if ( !cook )
		return								false;

	if ( has_uncompressed_inline_data() )
		return								!!cook->get_create_resource_inplace_in_inline_fat_delegate();

	return									!!cook->get_create_resource_inplace_in_creation_data_delegate();
}

void   query_result::bind_unmanaged_resource_buffer_to_creation_or_inline_data ()
{
	if ( has_uncompressed_inline_data() )
	{
		fat_iterator fat_it				=	wrapper_to_fat_it(m_fat_it);
		const_buffer						inline_data;
		fat_it.get_inline_data				(& inline_data);
		m_raw_unmanaged_buffer			=	cast_away_const(inline_data);
	}
	else if ( creation_data_from_user() )
	{
		m_raw_unmanaged_buffer			=	cast_away_const(m_creation_data_from_user);	
	}
	else
		NOT_IMPLEMENTED();
}

bool   query_result::allocate_raw_unmanaged_resource_if_needed ()
{
	file_system::iterator fat_it		=	wrapper_to_fat_it( m_fat_it );

	inplace_unmanaged_cook * const cook	=	cook_base::find_inplace_unmanaged_cook(m_class_id);
	if ( !cook )
		return								false;

	if ( allocate_thread_id() != threading::current_thread_id() )
		return								false;

	if ( need_create_resource_inplace_in_creation_or_inline_data() )
		return								false;

	if ( need_create_resource_if_no_file() )
	{
		m_raw_unmanaged_buffer			=	cook->allocate_resource(*this, 0, m_offset_to_file, false);	
	}
	else
	{
		unsigned const raw_file_size			=	get_raw_file_size();
		m_offset_to_file				=	0;
		m_raw_unmanaged_buffer			=	cook->allocate_resource(*this, raw_file_size, m_offset_to_file, true);
		R_ASSERT							(m_raw_unmanaged_buffer);
	}

	R_ASSERT								(m_offset_to_file || !m_raw_unmanaged_buffer,
											 "cook::allocate_raw_unmanaged should set offs_to_raw_file to a non-zero value");
	return									true;
}

struct helper_unmanaged_resource : public unmanaged_resource 
{
public:
	//virtual	void				recalculate_memory_usage_impl	() { m_memory_usage_self.unmanaged = get_size(); }
};

void   query_result::free_unmanaged_buffer ()
{
	R_ASSERT								(!m_raw_unmanaged_buffer || !m_unmanaged_buffer);
	mutable_buffer const unmanaged_buffer	=	m_raw_unmanaged_buffer ? m_raw_unmanaged_buffer : m_unmanaged_buffer;
	if ( !unmanaged_buffer )
		return;

	R_ASSERT								(unmanaged_buffer.size() >= sizeof(unmanaged_resource));
	unmanaged_resource_ptr	ptr			=	new ( unmanaged_buffer.c_ptr() ) helper_unmanaged_resource();

	set_deleter_object						(ptr.c_ptr());
	ptr->late_set_fat_it					(get_fat_it_zero_if_physical_path_it());
	ptr->set_creation_source				(resource_base::creation_source_deallocate_buffer_helper, m_request_path, unmanaged_buffer.size());

	m_raw_unmanaged_buffer.reset			();
	m_unmanaged_buffer.reset				();
}

void   query_result::set_deleter_object (unmanaged_resource * resource)
{
	cook_base *	const cook				=	cook_base::find_cook(m_class_id);
	unsigned deallocate_thread_id			=	cook->allocate_thread_id();
	
	if ( deallocate_thread_id == cook_base::use_user_thread_id )
		deallocate_thread_id			=	m_user_thread_id;
	
	resource->set_deleter_object			(cook, deallocate_thread_id);
}

void   query_result::send_to_allocate_final_resource ()
{
	if ( cook_base::find_managed_cook(m_class_id) || cook_base::find_unmanaged_cook(m_class_id)  )
	{
		g_resources_manager->send_to_allocate_final_resource_impl	(this);
		return;
	}

	on_allocated_final_resource			();
}

void   query_result::on_allocated_final_resource ()
{
	send_to_create_resource				();		
}

resource_base::creation_source_enum   query_result::creation_source_for_resource ()
{
	resource_base::creation_source_enum	  creation_source	=	creation_source_unset;
	if ( creation_data_from_user() )
	{
		creation_source					=	resource_base::creation_source_user_data;
	}
	else if ( cook_base::find_translate_query_cook(m_class_id) )
	{
		creation_source					=	creation_source_translate_query;
	}
	else
	{
		R_ASSERT							(has_flag(flag_processed_request_path) || has_flag(flag_translated_query));
		if ( has_flag(flag_uses_physical_path) )
			creation_source				=	resource_base::creation_source_physical_path;
		else
			creation_source				=	resource_base::creation_source_fat;
	}
	ASSERT									(creation_source != creation_source_unset);

	return									creation_source;
}

void   query_result::set_creation_source_for_resource (managed_resource_ptr resource)
{
	resource->set_creation_source			(creation_source_for_resource(), m_request_path);
}

void   query_result::set_creation_source_for_resource (unmanaged_resource_ptr resource)
{
	resource->set_creation_source			(creation_source_for_resource(), m_request_path, resource->get_size());
}

void   query_result_for_cook::save_generated_resource (const_buffer const & in_data)
{
	m_generated_data_to_save			=	memory::buffer(MT_ALLOC(char, in_data.size()), in_data.size());
	memory::copy							(m_generated_data_to_save, in_data);
	
	query_result * const this_ptr		=	static_cast_checked<query_result *>(this);
	this_ptr->set_flag						(query_result::flag_need_saving_of_generated_resource);
}

unsigned   query_result::allocate_thread_id () const
{
	cook_base * const cook				=	cook_base::find_cook(m_class_id);
	R_ASSERT								(cook);

	unsigned allocate_thread_id				=	cook->allocate_thread_id();
	if ( allocate_thread_id == cook_base::use_user_thread_id )
		allocate_thread_id				=	m_user_thread_id;

	return									allocate_thread_id;
}

} // namespace resources
} // namespace xray


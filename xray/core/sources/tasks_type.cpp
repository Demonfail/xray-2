////////////////////////////////////////////////////////////////////////////
//	Created		: 06.05.2010
//	Author		: Sergey Chechin
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "tasks_allocator.h"
#include "tasks_type.h"
#include <xray/memory_fixed_size_allocator.h>
#include <xray/construction.h>

namespace xray {
namespace tasks {

typedef	memory::fixed_size_allocator<task_type, threading::multi_threading_mutex_policy>	tasks_types_allocator; 

static unsigned const						s_task_types_arena_size			=	1024 * 1024;
static char								s_task_types_arena					[s_task_types_arena_size];
static tasks_types_allocator *			s_task_types_allocator			=	NULL;
static threading::atomic32_type			s_task_types_creation_flag		=	0;

XRAY_ALIGN(XRAY_MAX_CACHE_LINE_SIZE)
static char								s_task_types_allocator_buffer		[sizeof(tasks_types_allocator)];

static task_type_list_container * 		s_task_type_list				=	NULL;
static XRAY_DEFAULT_ALIGN char			s_task_type_list_buffer				[sizeof(task_type_list_container)];
static threading::atomic32_type			s_task_type_list_creation_flag	=	0;

task_type::task_type () : m_description(NULL), m_flags(0), m_min_task_ordinal(0), m_next_task_type(NULL) 
{
}

task_type::task_type (pcstr description, task_type_flags_enum const flags) : 
		 m_description(description), m_flags((char)flags), m_min_task_ordinal(0), m_next_task_type(NULL) 
{
}

task_type_list_container *   get_task_type_list () 
{
	return								s_task_type_list;
}

struct inplace_constructor
{
	void   operator () (tasks_types_allocator * pointer)
	{
		new (pointer) tasks_types_allocator(memory::buffer(s_task_types_arena));//, XRAY_MAX_CACHE_LINE_SIZE);
	}
};

task_type *   create_new_task_type (pcstr description, enum_flags<enum xray::tasks::task_type_flags_enum> flags)
{
	if ( ! s_task_types_allocator )
	{
		bind_pointer_to_buffer_mt_safe	(	s_task_types_allocator, 
											s_task_types_allocator_buffer, 
											s_task_types_creation_flag,
											inplace_constructor()	);
	}

	task_type * new_type			=	s_task_types_allocator->allocate();
	if ( new_type )
		new (new_type)					task_type(description, flags);

	if ( !s_task_type_list )
	{
		bind_pointer_to_buffer_mt_safe	(	s_task_type_list, 
											s_task_type_list_buffer, 
											s_task_type_list_creation_flag,
											bind_pointer_to_buffer_mt_safe_placement_new_predicate()	);
	}
	
	s_task_type_list->push_back			(new_type);

	return								new_type;
}

} // namespace tasks
} // namespace xray
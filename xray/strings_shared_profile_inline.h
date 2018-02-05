////////////////////////////////////////////////////////////////////////////
//	Created 	: 10.10.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef XRAY_STRINGS_SHARED_PROFILE_INLINE_H_INCLUDED
#define XRAY_STRINGS_SHARED_PROFILE_INLINE_H_INCLUDED

inline xray::threading::atomic32_type const& xray::strings::shared::profile::reference_count	( ) const
{
	return				( m_reference_count );
}

inline const unsigned &xray::strings::shared::profile::checksum			( ) const
{
	ASSERT				( m_checksum == create_checksum ( value(), value() + m_length ), "shared string is corrupted" );
	return				( m_checksum );
}

inline const unsigned &xray::strings::shared::profile::checksum_no_check	( ) const
{
	return				(m_checksum);
}

inline unsigned const& xray::strings::shared::profile::length			( ) const
{
	ASSERT				( strings::length( value( ) ) == m_length, "shared string is corrupted" );
	return				( m_length );
}

inline unsigned const& xray::strings::shared::profile::length_no_check	( ) const
{
	return				( m_length );
}

inline pcstr xray::strings::shared::profile::value					( ) const
{
	return				( ( ( pcstr )this ) + sizeof( profile ) );
}

inline xray::strings::shared::profile* xray::strings::shared::profile::get_next_hash_node	( ) const
{
	return				( m_next );
}

inline void xray::strings::shared::profile::set_next_hash_node		( profile* const value )
{
	m_next				= value;
}

#endif // #ifndef XRAY_STRINGS_SHARED_PROFILE_INLINE_H_INCLUDED
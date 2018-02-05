////////////////////////////////////////////////////////////////////////////
//	Created 	: 23.10.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef XRAY_MATH_AABB_H_INCLUDED
#define XRAY_MATH_AABB_H_INCLUDED

namespace xray {
namespace math {

class XRAY_CORE_API aabb {
public:
	typedef float	type;

public:
	float3			min;
	float3			max;

public:
	inline			aabb		( );
	

	inline	aabb&	zero		( );
	inline	aabb&	identity	( );
	inline	aabb&	invalidate	( );
	
	

	inline	aabb&	operator +=	( type value );
	inline	aabb&	operator +=	( float3 const& value );
	inline	aabb&	operator -=	( type value );
	inline	aabb&	operator -=	( float3 const& value );
	inline	aabb&	operator *=	( type value );
	inline	aabb&	operator *=	( float3 const& value );
	inline	aabb&	operator /=	( type value );
	inline	aabb&	operator /=	( float3 const& value );

	inline	aabb&	move		( float3 const& value );

	inline	aabb&	modify		( float3 const& position );
	inline	aabb&	modify		( aabb const& other );
			aabb&	modify		( float4x4 const& transform );

	inline	float3	extents		( ) const;
	inline	type	volume		( ) const;

	inline	float3	center		( ) const;
	inline	float3	center		( float3& size ) const;

	inline	sphere	sphere		( ) const;

	inline	bool	intersect	( aabb const& other ) const;

	inline	bool	contains	( float3 const& position ) const;
	inline	bool	contains	( aabb const& other ) const;

	inline	bool	similar		( aabb const& other ) const;

	intersection	intersect	( float3 const& position, float3 const& direction, float3& result ) const;

	inline	float3	vertex		( unsigned index ) const;
	inline	void	vertices	( float3 ( &result )[ 8 ] ) const;

	inline	bool	valid		( ) const;
}; // class aabb

inline 		aabb	operator +	( aabb const& aabb, aabb::type value );
inline 		aabb	operator +	( aabb::type value, aabb const& aabb );
inline 		aabb	operator +	( aabb const& aabb, float3 const& value );
inline 		aabb	operator +	( float3 const& value, aabb const& aabb );
inline 		aabb	operator -	( aabb const& aabb, aabb::type value );
inline 		aabb	operator -	( aabb::type value, aabb const& aabb );
inline 		aabb	operator -	( aabb const& aabb, float3 const& value );
inline 		aabb	operator -	( float3 const& value, aabb const& aabb );
inline 		aabb	operator *	( aabb const& aabb, aabb::type value );
inline 		aabb	operator *	( aabb::type value, aabb const& aabb );
inline 		aabb	operator *	( aabb const& aabb, float3 const& value );
inline 		aabb	operator *	( float3 const& value, aabb const& aabb );
inline 		aabb	operator /	( aabb const& aabb, aabb::type value );
inline 		aabb	operator /	( aabb::type value, aabb const& aabb );
inline 		aabb	operator /	( aabb const& aabb, float3 const& value );
inline 		aabb	operator /	( float3 const& value, aabb const& aabb );

} // namespace math
} // namespace xray

#include <xray/math_aabb_inline.h>

#endif // #ifndef XRAY_MATH_AABB_H_INCLUDED
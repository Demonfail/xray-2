////////////////////////////////////////////////////////////////////////////
//	Created 	: 23.10.2008
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef XRAY_MATH_COLOR_INLINE_H_INCLUDED
#define XRAY_MATH_COLOR_INLINE_H_INCLUDED

namespace xray {
namespace math {

inline color::color		( )
{
}

inline color::color	( color const& other)
:super( other )
{

}

inline color::color	( float4 const& other)
:super( other )
{

}

inline color::color		( type r, type g, type b, type a ) 
:super( r, g, b, a )
{
}

inline color::color		( unsigned r, unsigned g, unsigned b, unsigned a )
{
	type t = 1.0f / 255.0f;
	set(r*t, g*t, b*t, a*t);
}

inline color::color		( unsigned argb )
{
	type t = 1.0f / 255.0f;
	a = t * type((argb >> 24)& 0xff);
	r = t * type((argb >> 16)& 0xff);
	g = t * type((argb >>  8)& 0xff);
	b = t * type((argb >>  0)& 0xff);

	set(r, g, b, a);
}

inline unsigned color::get_d3dcolor() const
{
	return color_argb(u8(math::floor(a*255)), u8(math::floor(r*255)), u8(math::floor(g*255)), u8(math::floor(b*255)));
}

inline unsigned color_argb	( u8 const alpha, u8 const red, u8 const green, u8 const blue )
{
	return		(
		( unsigned( alpha ) << 24 ) |
		( unsigned( red )   << 16 ) |
		( unsigned( green ) <<  8 ) |
		( unsigned( blue )  <<  0 )
	);
}

inline unsigned color_xrgb	( u8 const red, u8 const green, u8 const blue )
{
	return		( color_argb ( 255, red, green, blue ) );
}


} // namespace math
} // namespace xray

#endif // #ifndef XRAY_MATH_COLOR_INLINE_H_INCLUDED
////////////////////////////////////////////////////////////////////////////
//	Created		: 18.02.2009
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#ifndef XRAY_MATH_AABB_PLANE_H_INCLUDED
#define XRAY_MATH_AABB_PLANE_H_INCLUDED

namespace xray {
namespace math {

class XRAY_CORE_API aabb_plane {
public:
	void				normalize	();
	intersection		test		( aabb const& aabb ) const;

public:
	plane				plane;

private:
	unsigned					m_lut_id;
}; // struct aabb_plane

} // namespace math
} // namespace xray

#endif // #ifndef XRAY_MATH_AABB_PLANE_H_INCLUDED
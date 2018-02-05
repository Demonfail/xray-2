////////////////////////////////////////////////////////////////////////////
//	Created		: 05.03.2009
//	Author		: Armen Abroyan
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include <xray/geometry_primitives.h>

using xray::math::float3;
using xray::math::float4x4;

namespace xray {
namespace geometry_utils{

////////////////////////////////////////////////////////////////////////////
// Oriented Bounding Box
////////////////////////////////////////////////////////////////////////////

namespace obb {

	const unsigned	vertex_count = 8;
	const float	vertices[ vertex_count * 3 ] =
	{
		-1.f,-1.f,-1.f,
		-1.f,+1.f,-1.f,
		+1.f,+1.f,-1.f,
		+1.f,-1.f,-1.f,
		-1.f,-1.f,+1.f,
		-1.f,+1.f,+1.f,
		+1.f,+1.f,+1.f,
		+1.f,-1.f,+1.f
	};

	const unsigned	pair_count = 12;
	const u16	pairs[ pair_count * 2 ] =
	{
		0,1,  1,2,  2,3,  3,0,  4,5,  5,6,  6,7,  7,4,  1,5,  2,6,  3,7,  0,4
	};

} // namespace obb

////////////////////////////////////////////////////////////////////////////
// Rectangle
////////////////////////////////////////////////////////////////////////////
namespace rectangle {

	const unsigned	vertex_count = 4;
	const float	vertices[ vertex_count * 3 ] =
	{
		-1.f, 0.f, -1.f,
		-1.f, 0.f, +1.f,
		+1.f, 0.f, +1.f,
		+1.f, 0.f, -1.f,
	};

	const unsigned	pair_count = 4;
	const u16	pairs[ pair_count * 2 ] =
	{
		0,1,  1,2,  2,3,  3,0
	};

} // namespace Rectangle

////////////////////////////////////////////////////////////////////////////
// Ellipsoid
////////////////////////////////////////////////////////////////////////////
namespace ellipsoid {
	const unsigned	vertex_count = 114;
	const float	vertices[ vertex_count * 3 ] =
	{
		0.0000f,0.0000f,1.0000f,	0.0000f,0.3827f,0.9239f,	-0.1464f,0.3536f,0.9239f,
		-0.2706f,0.2706f,0.9239f,	-0.3536f,0.1464f,0.9239f,	-0.3827f,0.0000f,0.9239f,
		-0.3536f,-0.1464f,0.9239f,  -0.2706f,-0.2706f,0.9239f,  -0.1464f,-0.3536f,0.9239f,
		0.0000f,-0.3827f,0.9239f,	0.1464f,-0.3536f,0.9239f,	0.2706f,-0.2706f,0.9239f,
		0.3536f,-0.1464f,0.9239f,	0.3827f,0.0000f,0.9239f,	0.3536f,0.1464f,0.9239f,
		0.2706f,0.2706f,0.9239f,	0.1464f,0.3536f,0.9239f,	0.0000f,0.7071f,0.7071f,
		-0.2706f,0.6533f,0.7071f,	-0.5000f,0.5000f,0.7071f,	-0.6533f,0.2706f,0.7071f,
		-0.7071f,0.0000f,0.7071f,	-0.6533f,-0.2706f,0.7071f,  -0.5000f,-0.5000f,0.7071f,
		-0.2706f,-0.6533f,0.7071f,  0.0000f,-0.7071f,0.7071f,	0.2706f,-0.6533f,0.7071f,
		0.5000f,-0.5000f,0.7071f,	0.6533f,-0.2706f,0.7071f,	0.7071f,0.0000f,0.7071f,
		0.6533f,0.2706f,0.7071f,	0.5000f,0.5000f,0.7071f,	0.2706f,0.6533f,0.7071f,
		0.0000f,0.9239f,0.3827f,	-0.3536f,0.8536f,0.3827f,	-0.6533f,0.6533f,0.3827f,
		-0.8536f,0.3536f,0.3827f,	-0.9239f,0.0000f,0.3827f,	-0.8536f,-0.3536f,0.3827f,
		-0.6533f,-0.6533f,0.3827f,  -0.3536f,-0.8536f,0.3827f,  0.0000f,-0.9239f,0.3827f,
		0.3536f,-0.8536f,0.3827f,	0.6533f,-0.6533f,0.3827f,	0.8536f,-0.3536f,0.3827f,
		0.9239f,0.0000f,0.3827f,	0.8536f,0.3536f,0.3827f,	0.6533f,0.6533f,0.3827f,
		0.3536f,0.8536f,0.3827f,	0.0000f,1.0000f,0.0000f,	-0.3827f,0.9239f,0.0000f,
		-0.7071f,0.7071f,0.0000f,	-0.9239f,0.3827f,0.0000f,	-1.0000f,0.0000f,0.0000f,
		-0.9239f,-0.3827f,0.0000f,  -0.7071f,-0.7071f,0.0000f,  -0.3827f,-0.9239f,0.0000f,
		0.0000f,-1.0000f,0.0000f,	0.3827f,-0.9239f,0.0000f,	0.7071f,-0.7071f,0.0000f,
		0.9239f,-0.3827f,0.0000f,	1.0000f,0.0000f,0.0000f,	0.9239f,0.3827f,0.0000f,
		0.7071f,0.7071f,0.0000f,	0.3827f,0.9239f,0.0000f,	0.0000f,0.9239f,-0.3827f,
		-0.3536f,0.8536f,-0.3827f,  -0.6533f,0.6533f,-0.3827f,  -0.8536f,0.3536f,-0.3827f,
		-0.9239f,0.0000f,-0.3827f,  -0.8536f,-0.3536f,-0.3827f, -0.6533f,-0.6533f,-0.3827f,
		-0.3536f,-0.8536f,-0.3827f,	0.0000f,-0.9239f,-0.3827f,  0.3536f,-0.8536f,-0.3827f,
		0.6533f,-0.6533f,-0.3827f,  0.8536f,-0.3536f,-0.3827f,  0.9239f,0.0000f,-0.3827f,
		0.8536f,0.3536f,-0.3827f,	0.6533f,0.6533f,-0.3827f,	0.3536f,0.8536f,-0.3827f,
		0.0000f,0.7071f,-0.7071f,	-0.2706f,0.6533f,-0.7071f,  -0.5000f,0.5000f,-0.7071f,
		-0.6533f,0.2706f,-0.7071f,	-0.7071f,0.0000f,-0.7071f,  -0.6533f,-0.2706f,-0.7071f,
		-0.5000f,-0.5000f,-0.7071f,	-0.2706f,-0.6533f,-0.7071f,	0.0000f,-0.7071f,-0.7071f,
		0.2706f,-0.6533f,-0.7071f,	0.5000f,-0.5000f,-0.7071f,  0.6533f,-0.2706f,-0.7071f,
		0.7071f,0.0000f,-0.7071f,	0.6533f,0.2706f,-0.7071f,	0.5000f,0.5000f,-0.7071f,
		0.2706f,0.6533f,-0.7071f,	0.0000f,0.3827f,-0.9239f,	-0.1464f,0.3536f,-0.9239f,
		-0.2706f,0.2706f,-0.9239f,  -0.3536f,0.1464f,-0.9239f,  -0.3827f,0.0000f,-0.9239f,
		-0.3536f,-0.1464f,-0.9239f,	-0.2706f,-0.2706f,-0.9239f, -0.1464f,-0.3536f,-0.9239f,
		0.0000f,-0.3827f,-0.9239f,  0.1464f,-0.3536f,-0.9239f,  0.2706f,-0.2706f,-0.9239f,
		0.3536f,-0.1464f,-0.9239f,  0.3827f,0.0000f,-0.9239f,	0.3536f,0.1464f,-0.9239f,
		0.2706f,0.2706f,-0.9239f,	0.1464f,0.3536f,-0.9239f,	0.0000f,0.0000f,-1.0000f
	};

	const unsigned	pair_count = 336;
	const u16	pairs[ pair_count * 2 ] =
	{
		0,   1,   0,   2,   0,   3,   0,   4,   0,   5,   0,   6,   0,   7,   0,   8,   0,   9,   0,  10,
		0,  11,   0,  12,   0,  13,   0,  14,   0,  15,   0,  16,   1,   2,   1,  16,   1,  17,   1,  18,
		2,   3,   2,  18,   2,  19,   3,   4,   3,  19,   3,  20,   4,   5,   4,  20,   4,  21,   5,   6,
		5,  21,   5,  22,   6,   7,   6,  22,   6,  23,   7,   8,   7,  23,   7,  24,   8,   9,   8,  24,
		8,  25,   9,  10,   9,  25,   9,  26,  10,  11,  10,  26,  10,  27,  11,  12,  11,  27,  11,  28,
		12,  13,  12,  28,  12,  29,  13,  14,  13,  29,  13,  30,  14,  15,  14,  30,  14,  31,  15,  16,
		15,  31,  15,  32,  16,  17,  16,  32,  17,  18,  17,  32,  17,  33,  17,  34,  18,  19,  18,  34,
		18,  35,  19,  20,  19,  35,  19,  36,  20,  21,  20,  36,  20,  37,  21,  22,  21,  37,  21,  38,
		22,  23,  22,  38,  22,  39,  23,  24,  23,  39,  23,  40,  24,  25,  24,  40,  24,  41,  25,  26,
		25,  41,  25,  42,  26,  27,  26,  42,  26,  43,  27,  28,  27,  43,  27,  44,  28,  29,  28,  44,
		28,  45,  29,  30,  29,  45,  29,  46,  30,  31,  30,  46,  30,  47,  31,  32,  31,  47,  31,  48,
		32,  33,  32,  48,  33,  34,  33,  48,  33,  49,  33,  50,  34,  35,  34,  50,  34,  51,  35,  36,
		35,  51,  35,  52,  36,  37,  36,  52,  36,  53,  37,  38,  37,  53,  37,  54,  38,  39,  38,  54,
		38,  55,  39,  40,  39,  55,  39,  56,  40,  41,  40,  56,  40,  57,  41,  42,  41,  57,  41,  58,
		42,  43,  42,  58,  42,  59,  43,  44,  43,  59,  43,  60,  44,  45,  44,  60,  44,  61,  45,  46,
		45,  61,  45,  62,  46,  47,  46,  62,  46,  63,  47,  48,  47,  63,  47,  64,  48,  49,  48,  64,
		49,  50,  49,  64,  49,  65,  49,  66,  50,  51,  50,  66,  50,  67,  51,  52,  51,  67,  51,  68,
		52,  53,  52,  68,  52,  69,  53,  54,  53,  69,  53,  70,  54,  55,  54,  70,  54,  71,  55,  56,
		55,  71,  55,  72,  56,  57,  56,  72,  56,  73,  57,  58,  57,  73,  57,  74,  58,  59,  58,  74,
		58,  75,  59,  60,  59,  75,  59,  76,  60,  61,  60,  76,  60,  77,  61,  62,  61,  77,  61,  78,
		62,  63,  62,  78,  62,  79,  63,  64,  63,  79,  63,  80,  64,  65,  64,  80,  65,  66,  65,  80,
		65,  81,  65,  82,  66,  67,  66,  82,  66,  83,  67,  68,  67,  83,  67,  84,  68,  69,  68,  84,
		68,  85,  69,  70,  69,  85,  69,  86,  70,  71,  70,  86,  70,  87,  71,  72,  71,  87,  71,  88,
		72,  73,  72,  88,  72,  89,  73,  74,  73,  89,  73,  90,  74,  75,  74,  90,  74,  91,  75,  76,
		75,  91,  75,  92,  76,  77,  76,  92,  76,  93,  77,  78,  77,  93,  77,  94,  78,  79,  78,  94,
		78,  95,  79,  80,  79,  95,  79,  96,  80,  81,  80,  96,  81,  82,  81,  96,  81,  97,  81,  98,
		82,  83,  82,  98,  82,  99,  83,  84,  83,  99,  83, 100,  84,  85,  84, 100,  84, 101,  85,  86,
		85, 101,  85, 102,  86,  87,  86, 102,  86, 103,  87,  88,  87, 103,  87, 104,  88,  89,  88, 104,
		88, 105,  89,  90,  89, 105,  89, 106,  90,  91,  90, 106,  90, 107,  91,  92,  91, 107,  91, 108,
		92,  93,  92, 108,  92, 109,  93,  94,  93, 109,  93, 110,  94,  95,  94, 110,  94, 111,  95,  96,
		95, 111,  95, 112,  96,  97,  96, 112,  97,  98,  97, 112,  97, 113,  98,  99,  98, 113,  99, 100,
		99, 113, 100, 101, 100, 113, 101, 102, 101, 113, 102, 103, 102, 113, 103, 104, 103, 113, 104, 105,
		104, 113, 105, 106, 105, 113, 106, 107, 106, 113, 107, 108, 107, 113, 108, 109, 108, 113, 109, 110,
		109, 113, 110, 111, 110, 113, 111, 112, 111, 113, 112, 113
	};
} // namespace ellipsoid

////////////////////////////////////////////////////////////////////////////
// Cone
////////////////////////////////////////////////////////////////////////////
namespace cone {
	const unsigned	vertex_count = 17;
	const float	vertices[ vertex_count * 3 ] =
	{
		0.000000f,  1.000000f,   0.000000f,
		1.000000f, -1.000000f,   0.000000f,
		0.923880f, -1.000000f,   0.382683f,
		0.707107f, -1.000000f,   0.707107f,
		0.382683f, -1.000000f,   0.923880f,
		-0.000000f, -1.000000f,   1.000000f,
		-0.382684f, -1.000000f,   0.923880f,
		-0.707107f, -1.000000f,   0.707107f,
		-0.923880f, -1.000000f,   0.382683f,
		-1.000000f, -1.000000f,  -0.000000f,
		-0.923880f, -1.000000f,  -0.382683f,
		-0.707107f, -1.000000f,  -0.707107f,
		-0.382683f, -1.000000f,  -0.923880f,
		0.000000f, -1.000000f,  -1.000000f,
		0.382684f, -1.000000f,  -0.923879f,
		0.707107f, -1.000000f,  -0.707107f,
		0.923880f, -1.000000f,  -0.382683f
	};

	const unsigned	pair_count = 32;
	const u16	pairs[ pair_count * 2 ] =
	{
		0,  1,
		0,  2,
		0,  3,
		0,  4,
		0,  5,
		0,  6,
		0,  7,
		0,  8,
		0,  9,
		0, 10,
		0, 11,
		0, 12,
		0, 13,
		0, 14,
		0, 15,
		0, 16,
		1,  2,
		2,  3,
		3,  4,
		4,  5,
		5,  6,
		6,  7,
		7,  8,
		8,  9,
		9, 10,
		10, 11,
		11, 12,
		12, 13,
		13, 14,
		14, 15,
		15, 16,
		16,  1
	};
} // namespace cone


////////////////////////////////////////////////////////////////////////////
// Ellipse 
////////////////////////////////////////////////////////////////////////////
namespace ellipse {
	const unsigned	vertex_count = 64;
	const float	vertices[ vertex_count * 3 ] =
	{
		1.000000f,	0.000000f,	0.000000f,
		0.995185f,	0.000000f,	0.098017f,
		0.980785f,	0.000000f,	0.195090f,
		0.956940f,	0.000000f,	0.290285f,
		0.923880f,	0.000000f,	0.382683f,
		0.881921f,	0.000000f,	0.471397f,
		0.831470f,	0.000000f,	0.555570f,
		0.773010f,	0.000000f,	0.634393f,
		0.707107f,	0.000000f,	0.707107f,
		0.634393f,	0.000000f,	0.773010f,
		0.555570f,	0.000000f,	0.831470f,
		0.471397f,	0.000000f,	0.881921f,
		0.382683f,	0.000000f,	0.923880f,
		0.290285f,	0.000000f,	0.956940f,
		0.195090f,	0.000000f,	0.980785f,
		0.098017f,	0.000000f,	0.995185f,
		0.000000f,	0.000000f,	1.000000f,
		-0.098017f,	0.000000f,	0.995185f,
		-0.195090f,	0.000000f,	0.980785f,
		-0.290285f,	0.000000f,	0.956940f,
		-0.382683f,	0.000000f,	0.923880f,
		-0.471397f,	0.000000f,	0.881921f,
		-0.555570f,	0.000000f,	0.831470f,
		-0.634393f,	0.000000f,	0.773010f,
		-0.707107f,	0.000000f,	0.707107f,
		-0.773010f,	0.000000f,	0.634393f,
		-0.831470f,	0.000000f,	0.555570f,
		-0.881921f,	0.000000f,	0.471397f,
		-0.923880f,	0.000000f,	0.382683f,
		-0.956940f,	0.000000f,	0.290285f,
		-0.980785f,	0.000000f,	0.195090f,
		-0.995185f,	0.000000f,	0.098017f,
		-1.000000f,	0.000000f,	0.000000f,
		-0.995185f,	0.000000f,	-0.098017f,
		-0.980785f,	0.000000f,	-0.195090f,
		-0.956940f,	0.000000f,	-0.290285f,
		-0.923879f,	0.000000f,	-0.382684f,
		-0.881921f,	0.000000f,	-0.471397f,
		-0.831470f,	0.000000f,	-0.555570f,
		-0.773010f,	0.000000f,	-0.634393f,
		-0.707107f,	0.000000f,	-0.707107f,
		-0.634393f,	0.000000f,	-0.773011f,
		-0.555570f,	0.000000f,	-0.831470f,
		-0.471397f,	0.000000f,	-0.881921f,
		-0.382683f,	0.000000f,	-0.923880f,
		-0.290285f,	0.000000f,	-0.956940f,
		-0.195090f,	0.000000f,	-0.980785f,
		-0.098017f,	0.000000f,	-0.995185f,
		0.000000f,	0.000000f,	-1.000000f,
		0.098017f,	0.000000f,	-0.995185f,
		0.195090f,	0.000000f,	-0.980785f,
		0.290285f,	0.000000f,	-0.956940f,
		0.382684f,	0.000000f,	-0.923879f,
		0.471397f,	0.000000f,	-0.881921f,
		0.555570f,	0.000000f,	-0.831470f,
		0.634393f,	0.000000f,	-0.773010f,
		0.707107f,	0.000000f,	-0.707107f,
		0.773011f,	0.000000f,	-0.634393f,
		0.831470f,	0.000000f,	-0.555570f,
		0.881921f,	0.000000f,	-0.471397f,
		0.923880f,	0.000000f,	-0.382683f,
		0.956940f,	0.000000f,	-0.290285f,
		0.980785f,	0.000000f,	-0.195090f,
		0.995185f,	0.000000f,	-0.098017f
	};

	const unsigned	pair_count = 64;
	const u16	pairs[ pair_count * 2 ] =
	{
		0, 1, 
		1, 2, 
		2, 3, 
		3, 4, 
		4, 5, 
		5, 6, 
		6, 7, 
		7, 8, 
		8, 9, 
		9, 10, 
		10, 11, 
		11, 12, 
		12, 13, 
		13, 14, 
		14, 15, 
		15, 16, 
		16, 17, 
		17, 18, 
		18, 19, 
		19, 20, 
		20, 21, 
		21, 22, 
		22, 23, 
		23, 24, 
		24, 25, 
		25, 26, 
		26, 27, 
		27, 28, 
		28, 29, 
		29, 30, 
		30, 31, 
		31, 32, 
		32, 33, 
		33, 34, 
		34, 35, 
		35, 36, 
		36, 37, 
		37, 38, 
		38, 39, 
		39, 40, 
		40, 41, 
		41, 42, 
		42, 43, 
		43, 44, 
		44, 45, 
		45, 46, 
		46, 47, 
		47, 48, 
		48, 49, 
		49, 50, 
		50, 51, 
		51, 52, 
		52, 53, 
		53, 54, 
		54, 55, 
		55, 56, 
		56, 57, 
		57, 58, 
		58, 59, 
		59, 60, 
		60, 61, 
		61, 62, 
		62, 63, 
		63, 0
	};
} // namespace ellipse

////////////////////////////////////////////////////////////////////////////
// Cube solid
////////////////////////////////////////////////////////////////////////////
namespace cube_solid {
	const unsigned vertex_count = 8;
	const float vertices[vertex_count*3] = 
	{
		-1.000000f,	 1.000000f,	-1.000000f,
		1.000000f,	-1.000000f,	-1.000000f,
		-1.000000f,	-1.000000f,	-1.000000f,
		1.000000f,	 1.000000f,	-1.000000f,
		-1.000000f,	 1.000000f,	 1.000000f,
		1.000000f,	 1.000000f,	 1.000000f,
		-1.000000f,	-1.000000f,	 1.000000f,
		1.000000f,	-1.000000f,	 1.000000f
	};

	const unsigned face_count = 12; 
	const unsigned index_count = face_count*3; 
	const u16 faces[index_count] = {
		0,		1,		2,
		3,		1,		0,
		4,		3,		0,
		5,		3,		4,
		6,		5,		4,
		7,		5,		6,
		2,		7,		6,
		1,		7,		2,
		3,		7,		1,
		5,		7,		3,
		4,		2,		6,
		0,		2,		4
	};
} //namespace cube_solid 


////////////////////////////////////////////////////////////////////////////
// Rectangle solid
////////////////////////////////////////////////////////////////////////////
namespace rectangle_solid {

	const unsigned vertex_count = 4;
	const float vertices[vertex_count*3] = 
	{
		-1.000000f,	0.000000f, 	-1.000000f,
		-1.000000f,	0.000000f,	 1.000000f,
		1.000000f,	0.000000f,	 1.000000f,
		1.000000f,	0.000000f,	-1.000000f
	};

	const unsigned face_count = 2;
	const unsigned index_count = face_count*3; 
	const u16 faces[index_count] = {
		0,		1,		2,
		3,		0,		2
	};

} // namespace Rectangle

////////////////////////////////////////////////////////////////////////////
// Cone solid
////////////////////////////////////////////////////////////////////////////
namespace cone_solid {
	const unsigned vertex_count = 17;
	const float vertices[vertex_count*3] = {
		1.414214f,	-1.000000f,	 1.414212f,
		2.000000f,	-1.000000f,	-0.000000f,
		1.847760f,	-1.000000f,	 0.765365f,
		1.847759f,	-1.000000f,	-0.765367f,
		1.414214f,	-1.000000f,	-1.414214f,
		0.765367f,	-1.000000f,	-1.847760f,
		-0.000000f,	-1.000000f,	-2.000000f,
		-0.765367f,	-1.000000f,	-1.847759f,
		-1.414214f,	-1.000000f,	-1.414214f,
		-1.847759f,	-1.000000f,	-0.765367f,
		-2.000000f,	-1.000000f,	 0.000000f,
		-1.847758f,	-1.000000f,	 0.765367f,
		-1.414213f,	-1.000000f,	 1.414214f,
		-0.765366f,	-1.000000f,	 1.847759f,
		0.000001f,	-1.000000f,	 2.000000f,
		0.765368f,	-1.000000f,	 1.847758f,
		0.000000f,	 1.000000f,	-0.000000f
	};

	const unsigned face_count = 30; 
	const unsigned index_count = face_count*3; 
	const u16 faces[index_count] = {
		0,		1,		2,	
		0,		3,		1,
		0,		4,		3,
		0,		5,		4,
		0,		6,		5,
		0,		7,		6,
		0,		8,		7,
		0,		9,		8,
		0,		10,		9,
		0,		11,		10,
		0,		12,		11,
		0,		13,		12,
		0,		14,		13,
		0,		15,		14,
		16,		0,		2,
		16,		15,		0,
		16,		14,		15,
		16,		13,		14,
		16,		12,		13,
		16,		11,		12,
		16,		10,		11,
		16,		9,		10,
		16,		8,		9,
		16,		7,		8,
		16,		6,		7,
		16,		5,		6,
		16,		4,		5,
		16,		3,		4,
		16,		1,		3,
		16,		2,		1
	};
} // namespace cone_solid


////////////////////////////////////////////////////////////////////////////
// Cylinder
////////////////////////////////////////////////////////////////////////////
namespace cylinder_solid {
	const unsigned vertex_count = 34;
	const float vertices[vertex_count*3] = {
		1.847760f,	 1.000000f,	 0.765366f,
		1.414214f,	-1.000000f,	 1.414213f,
		1.847760f,	-1.000000f,	 0.765366f,
		1.414214f,	 1.000000f,	 1.414213f,
		0.765368f,	-1.000000f,	 1.847759f,
		0.765368f,	 1.000000f,	 1.847759f,
		0.000001f,	-1.000000f,	 2.000000f,
		0.000001f,	 1.000000f,	 2.000000f,
		-0.765366f,	-1.000000f,	 1.847759f,
		-0.765366f,	 1.000000f,	 1.847759f,
		-1.414213f,	-1.000000f,	 1.414214f,
		-1.414213f,	 1.000000f,	 1.414214f,
		-1.847759f,	-1.000000f,	 0.765368f,
		-1.847759f,	 1.000000f,	 0.765368f,
		-2.000000f,	-1.000000f,	 0.000001f,
		-2.000000f,	 1.000000f,	 0.000001f,
		-1.847759f,	-1.000000f,	-0.765366f,
		-1.847759f,	 1.000000f,	-0.765366f,
		-1.414214f,	-1.000000f,	-1.414213f,
		-1.414214f,	 1.000000f,	-1.414213f,
		-0.765367f,	-1.000000f,	-1.847759f,
		-0.765367f,	 1.000000f,	-1.847759f,
		-0.000000f,	-1.000000f,	-2.000000f,
		-0.000000f,	 1.000000f,	-2.000000f,
		0.765367f,	-1.000000f,	-1.847759f,
		0.765367f,	 1.000000f,	-1.847759f,
		1.414213f,	-1.000000f,	-1.414214f,
		1.414213f,	 1.000000f,	-1.414214f,
		1.847759f,	-1.000000f,	-0.765367f,
		1.847759f,	 1.000000f,	-0.765367f,
		2.000000f,	-1.000000f,	 0.000000f,
		2.000000f,	 1.000000f,	 0.000000f,
		0.000000f,	-1.000000f,	 0.000000f,
		0.000000f,	 1.000000f,	 0.000000f
	};

	const unsigned face_count = 64; 
	const unsigned index_count = face_count*3; 
	const u16 faces[index_count] = {
		0,		1,		2,
		3,		1,		0,
		3,		4,		1,
		5,		4,		3,
		5,		6,		4,
		7,		6,		5,
		7,		8,		6,
		9,		8,		7,
		9,		10,		8,
		11,		10,		9,
		11,		12,		10,
		13,		12,		11,
		13,		14,		12,
		15,		14,		13,
		15,		16,		14,
		17,		16,		15,
		17,		18,		16,
		19,		18,		17,
		19,		20,		18,
		21,		20,		19,
		21,		22,		20,
		23,		22,		21,
		23,		24,		22,
		25,		24,		23,
		25,		26,		24,
		27,		26,		25,
		27,		28,		26,
		29,		28,		27,
		29,		30,		28,
		31,		30,		29,
		31,		2,		30,
		0,		2,		31,
		32,		2,		1,
		32,		1,		4,
		32,		4,		6,
		32,		6,		8,
		32,		8,		10,
		32,		10,		12,
		32,		12,		14,
		32,		14,		16,
		32,		16,		18,
		32,		18,		20,
		32,		20,		22,
		32,		22,		24,
		32,		24,		26,
		32,		26,		28,
		32,		28,		30,
		32,		30,		2,
		33,		3,		0,
		33,		5,		3,
		33,		7,		5,
		33,		9,		7,
		33,		11,		9,
		33,		13,		11,
		33,		15,		13,
		33,		17,		15,
		33,		19,		17,
		33,		21,		19,
		33,		23,		21,
		33,		25,		23,
		33,		27,		25,
		33,		29,		27,
		33,		31,		29,
		33,		0,		31
	};
} //namespace cylinder_solid 

////////////////////////////////////////////////////////////////////////////
// Ellipsoid solid
////////////////////////////////////////////////////////////////////////////
namespace ellipsoid_solid {
	const unsigned vertex_count = 92;
	const float vertices[vertex_count*3] = {
		0.0000f,    1.0000f,     0.0000f ,
		0.8944f,    0.4472f,     0.0000f ,
		0.2764f,    0.4472f,     0.8507f ,
		-0.7236f,    0.4472f,     0.5257f ,
		-0.7236f,    0.4472f,     -0.5257f,
		0.2764f,    0.4472f,     -0.8507f,
		0.7236f,    -0.4472f,    0.5257f ,
		-0.2764f,    -0.4472f,    0.8507f ,
		-0.8944f,    -0.4472f,    -0.0000f,
		-0.2764f,    -0.4472f,    -0.8507f,
		0.7236f,    -0.4472f,    -0.5257f,
		0.0000f,    -1.0000f,    0.0000f ,
		0.3607f,    0.9327f,     0.0000f ,
		0.6729f,    0.7397f,     0.0000f ,
		0.1115f,    0.9327f,     0.3431f ,
		0.2079f,    0.7397f,     0.6399f ,
		-0.2918f,    0.9327f,     0.2120f ,
		-0.5444f,    0.7397f,     0.3955f ,
		-0.2918f,    0.9327f,     -0.2120f,
		-0.5444f,    0.7397f,     -0.3955f,
		0.1115f,    0.9327f,     -0.3431f,
		0.2079f,    0.7397f,     -0.6399f,
		0.7844f,    0.5168f,     0.3431f ,
		0.5687f,    0.5168f,     0.6399f ,
		-0.0839f,    0.5168f,     0.8520f ,
		-0.4329f,    0.5168f,     0.7386f ,
		-0.8362f,    0.5168f,     0.1835f ,
		-0.8362f,    0.5168f,     -0.1835f,
		-0.4329f,    0.5168f,     -0.7386f,
		-0.0839f,    0.5168f,     -0.8520f,
		0.5687f,    0.5168f,     -0.6399f,
		0.7844f,    0.5168f,     -0.3431f,
		0.9647f,    0.1561f,     0.2120f ,
		0.9051f,    -0.1561f,    0.3955f ,
		0.0965f,    0.1561f,     0.9830f ,
		-0.0965f,    -0.1561f,    0.9830f ,
		-0.9051f,    0.1561f,     0.3955f ,
		-0.9647f,    -0.1561f,    0.2120f ,
		-0.6558f,    0.1561f,     -0.7386f,
		-0.4998f,    -0.1561f,    -0.8520f,
		0.4998f,    0.1561f,     -0.8520f,
		0.6558f,    -0.1561f,    -0.7386f,
		0.9647f,    0.1561f,     -0.2120f,
		0.9051f,    -0.1561f,    -0.3955f,
		0.4998f,    0.1561f,     0.8520f ,
		0.6558f,    -0.1561f,    0.7386f ,
		-0.6558f,    0.1561f,     0.7386f ,
		-0.4998f,    -0.1561f,    0.8520f ,
		-0.9051f,    0.1561f,     -0.3955f,
		-0.9647f,    -0.1561f,    -0.2120f,
		0.0965f,    0.1561f,     -0.9830f,
		-0.0965f,    -0.1561f,    -0.9830f,
		0.4329f,    -0.5168f,    0.7386f ,
		0.0839f,    -0.5168f,    0.8520f ,
		-0.5687f,    -0.5168f,    0.6399f ,
		-0.7844f,    -0.5168f,    0.3431f ,
		-0.7844f,    -0.5168f,    -0.3431f,
		-0.5687f,    -0.5168f,    -0.6399f,
		0.0839f,    -0.5168f,    -0.8520f,
		0.4329f,    -0.5168f,    -0.7386f,
		0.8362f,    -0.5168f,    -0.1835f,
		0.8362f,    -0.5168f,    0.1835f ,
		0.2918f,    -0.9327f,    0.2120f ,
		0.5444f,    -0.7397f,    0.3955f ,
		-0.1115f,    -0.9327f,    0.3431f ,
		-0.2079f,    -0.7397f,    0.6399f ,
		-0.3607f,    -0.9327f,    -0.0000f,
		-0.6729f,    -0.7397f,    -0.0000f,
		-0.1115f,    -0.9327f,    -0.3431f,
		-0.2079f,    -0.7397f,    -0.6399f,
		0.2918f,       -0.9327f,    -0.2120f,
		0.5444f,    -0.7397f,    -0.3955f,
		0.4795f,    0.8054f,       0.3484f ,
		-0.1832f,    0.8054f,       0.5637f ,
		-0.5927f,    0.8054f,       -0.0000f,
		-0.1832f,    0.8054f,       -0.5637f,
		0.4795f,    0.8054f,       -0.3484f,
		0.9855f,    -0.1699f,    0.0000f ,
		0.3045f,    -0.1699f,    0.9372f ,
		-0.7973f,    -0.1699f,    0.5792f ,
		-0.7973f,    -0.1699f,    -0.5792f,
		0.3045f,    -0.1699f,    -0.9372f,
		0.7973f,    0.1699f,       0.5792f ,
		-0.3045f,    0.1699f,       0.9372f ,
		-0.9855f,    0.1699f,       -0.0000f,
		-0.3045f,    0.1699f,       -0.9372f,
		0.7973f,    0.1699f,       -0.5792f,
		0.1832f,    -0.8054f,    0.5637f ,
		-0.4795f,    -0.8054f,    0.3484f ,
		-0.4795f,    -0.8054f,    -0.3484f,
		0.1832f,    -0.8054f,    -0.5637f,
		0.5927f,    -0.8054f,    0.0000f  
	};

	const unsigned face_count = 180; 
	const unsigned index_count = face_count*3; 
	const u16 faces[index_count] = {
		14,    12,    0,
		72,   13,   12,
		14,   72,   12,
		15,   72,   14,
		22,    1,   13,
		72,   22,   13,
		23,   22,   72,
		15,   23,   72,
		2,   23,   15,
		16,   14,    0,
		73,   15,   14,
		16,   73,   14,
		17,   73,   16,
		24,    2,   15,
		73,   24,   15,
		25,   24,   73,
		17,   25,   73,
		3,   25,   17,
		18,   16,    0,
		74,   17,   16,
		18,   74,   16,
		19,   74,   18,
		26,    3,   17,
		74,   26,   17,
		27,   26,   74,
		19,   27,   74,
		4,   27,   19,
		20,   18,    0,
		75,   19,   18,
		20,   75,   18,
		21,   75,   20,
		28,    4,   19,
		75,   28,   19,
		29,   28,   75,
		21,   29,   75,
		5,   29,   21,
		12,   20,    0,
		76,   21,   20,
		12,   76,   20,
		13,   76,   12,
		30,    5,   21,
		76,   30,   21,
		31,   30,   76,
		13,   31,   76,
		1,   31,   13,
		32,   42,    1,
		77,   43,   42,
		32,   77,   42,
		33,   77,   32,
		60,   10,   43,
		77,   60,   43,
		61,   60,   77,
		33,   61,   77,
		6,   61,   33,
		34,   44,    2,
		78,   45,   44,
		34,   78,   44,
		35,   78,   34,
		52,    6,   45,
		78,   52,   45,
		53,   52,   78,
		35,   53,   78,
		7,   53,   35,
		36,   46,    3,
		79,   47,   46,
		36,   79,   46,
		37,   79,   36,
		54,    7,   47,
		79,   54,   47,
		55,   54,   79,
		37,   55,   79,
		8,   55,   37,
		38,   48,    4,
		80,   49,   48,
		38,   80,   48,
		39,   80,   38,
		56,    8,   49,
		80,   56,   49,
		57,   56,   80,
		39,   57,   80,
		9,   57,   39,
		40,   50,    5,
		81,   51,   50,
		40,   81,   50,
		41,   81,   40,
		58,    9,   51,
		81,   58,   51,
		59,   58,   81,
		41,   59,   81,
		10,   59,   41,
		33,   45,    6,
		82,   44,   45,
		33,   82,   45,
		32,   82,   33,
		23,    2,   44,
		82,   23,   44,
		22,   23,   82,
		32,   22,   82,
		1,   22,   32,
		35,   47,    7,
		83,   46,   47,
		35,   83,   47,
		34,   83,   35,
		25,    3,   46,
		83,   25,   46,
		24,   25,   83,
		34,   24,   83,
		2,   24,   34,
		37,   49,    8,
		84,   48,   49,
		37,   84,   49,
		36,   84,   37,
		27,    4,   48,
		84,   27,   48,
		26,   27,   84,
		36,   26,   84,
		3,   26,   36,
		39,   51,    9,
		85,   50,   51,
		39,   85,   51,
		38,   85,   39,
		29,    5,   50,
		85,   29,   50,
		28,   29,   85,
		38,   28,   85,
		4,   28,   38,
		41,   43,   10,
		86,   42,   43,
		41,   86,   43,
		40,   86,   41,
		31,    1,   42,
		86,   31,   42,
		30,   31,   86,
		40,   30,   86,
		5,   30,   40,
		62,   64,   11,
		87,   65,   64,
		62,   87,   64,
		63,   87,   62,
		53,    7,   65,
		87,   53,   65,
		52,   53,   87,
		63,   52,   87,
		6,   52,   63,
		64,   66,   11,
		88,   67,   66,
		64,   88,   66,
		65,   88,   64,
		55,    8,   67,
		88,   55,   67,
		54,   55,   88,
		65,   54,   88,
		7,   54,   65,
		66,   68,   11,
		89,   69,   68,
		66,   89,   68,
		67,   89,   66,
		57,    9,   69,
		89,   57,   69,
		56,   57,   89,
		67,   56,   89,
		8,   56,   67,
		68,   70,   11,
		90,   71,   70,
		68,   90,   70,
		69,   90,   68,
		59,   10,   71,
		90,   59,   71,
		58,   59,   90,
		69,   58,   90,
		9,   58,   69,
		70,   62,   11,
		91,   63,   62,
		70,   91,   62,
		71,   91,   70,
		61,    6,   63,
		91,   61,   63,
		60,   61,   91,
		71,   60,   91,
		10,   60,   71
	};
} //namespace ellipsoid_solid 


inline  float3 	calculate_torus_vertex( float outer_radius, float inner_radius, float theta, float phi)
{
	float3 result;

	float cos_phi = math::cos( phi);

	int a = 0;
	float cos_theta = math::cos( theta); 

	result.x = (outer_radius + inner_radius*cos_phi)*cos_theta;

	if( !math::valid	( result.x ))
		a = a;

	result.y = inner_radius*math::table_sin((int)math::rad2deg(phi));

	if( !math::valid	( result.y ))
		a = a;

	result.z = (outer_radius + inner_radius*cos_phi)*math::sin( theta); 

	if( !math::valid	( result.z ))
		a = a;


	return result;	
}

bool generate_torus			( xray::vectora< float3 >& vertices, xray::vectora< u16 >& indices, float4x4 transform,
									 float outer_raduius,  float inner_raduius, u16 outer_segments, u16 inner_segments )
{
	XRAY_UNREFERENCED_PARAMETER	(transform);
	if( outer_segments <3 || inner_segments<3)
		return false;

	vertices.resize	( outer_segments*inner_segments);
	indices.resize	( 3*2*(outer_segments)*inner_segments);

	float delta_outer = math::pi_x2/outer_segments;
	float delta_inner = math::pi_x2/inner_segments;

	u16 vertex_index = 0;
	u16 index_index = 0;
	float3 temp_vertex;

	for ( int j = 0; j< inner_segments; ++vertex_index, ++j)
	{
		temp_vertex = calculate_torus_vertex( outer_raduius, inner_raduius, 0, delta_inner*j);
		vertices[vertex_index] = temp_vertex;
	}

	for (  int i = 1; i< outer_segments; ++i)
	{
		temp_vertex = calculate_torus_vertex( outer_raduius, inner_raduius, i*delta_outer, 0);

		vertices[vertex_index++] = temp_vertex;

		for ( int j = 1; j< inner_segments; ++vertex_index, ++j)
		{
			temp_vertex = calculate_torus_vertex( outer_raduius, inner_raduius, i*delta_outer, j*delta_inner);

			vertices[vertex_index] = temp_vertex;

			indices[index_index++] = vertex_index;
			indices[index_index++] = vertex_index-inner_segments-1;
			indices[index_index++] = vertex_index-inner_segments;

			indices[index_index++] = vertex_index-1;
			indices[index_index++] = vertex_index-inner_segments-1;
			indices[index_index++] = vertex_index;
		}

		indices[index_index++] = vertex_index-inner_segments;
		indices[index_index++] = vertex_index-inner_segments-1;
		indices[index_index++] = vertex_index-2*inner_segments;

		indices[index_index++] = vertex_index-1;
		indices[index_index++] = vertex_index-inner_segments-1;
		indices[index_index++] = vertex_index-inner_segments;
	}

	vertex_index = (u16)(vertex_index-inner_segments+1);

	u16 ind = 1;
	for ( int j = 1; j< inner_segments; ++vertex_index, ++j, ++ind)
	{
		indices[index_index++] = ind;
		indices[index_index++] = vertex_index-1;
		indices[index_index++] = vertex_index;

		indices[index_index++] = ind-1;
		indices[index_index++] = vertex_index-1;
		indices[index_index++] = ind;
	}

	indices[index_index++] = 0;
	indices[index_index++] = vertex_index-1;
	indices[index_index++] = vertex_index-inner_segments;

	indices[index_index++] = ind-1;
	indices[index_index++] = vertex_index-1;
	indices[index_index++] = 0;

	return true;
}

} // namespace geometry_utils
} // namespace xray
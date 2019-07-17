#pragma once
#include <cstdint>
#include <DirectXMath.h>
#include <vector>
#include "vertex.h"

class GeometryGenerator
{
public:

	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;

	class MeshData
	{
	public:
		std::vector<uint16> &GetIndices16()
		{
			if (mIndices16.empty())
			{
				mIndices16.resize(Indices32.size());
				for (size_t i = 0; i < Indices32.size(); ++i)
					mIndices16[i] = static_cast<uint16>(Indices32[i]);
			}
			return mIndices16;
		}

	public:
		std::vector<Vertex> Vertices;
		std::vector<uint32> Indices32;

	private:
		std::vector<uint16> mIndices16;
	};

	// Creates a box centered at the origin with the given dimensions.
	MeshData CreateBox(float width, float height, float depth, uint32 numSubdivisions);

	// Creates a sphere centered at the origin with the given radius.  The
	// slices and stacks parameters control the degree of tessellation.
	MeshData CreateSphere(float radius, uint32 sliceCount, uint32 stackCount);

	// Creates a geosphere centered at the origin with the given radius.
	MeshData CreateGeosphere(float radius, uint32 numSubdivisions);

	// Creates a cylinder parallel to the y-axis, and centered about the origin.  
	// The bottom and top radius can vary to form various cone shapes rather than true
	// cylinders.  The slices and stacks parameters control the degree of tessellation.
	MeshData CreateCylinder(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount);

	// Creates an mxn grid in the xz-plane with m rows and n columns, centered
	// at the origin with the specified width and depth.
	MeshData CreateGrid(float width, float depth, uint32 m, uint32 n);

	// Creates a quad aligned with the screen.  This is useful for postprocessing and screen effects.
	MeshData CreateQuad(float x, float y, float w, float h, float depth);

private:
	void Subdivide(MeshData& meshData);
	Vertex MidPoint(const Vertex& v0, const Vertex& v1);
	void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, MeshData& meshData);
	void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, MeshData& meshData);
};

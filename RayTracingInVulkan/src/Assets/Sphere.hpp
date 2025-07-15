#pragma once

#include "Procedural.hpp"
#include "Utilities/Glm.hpp"
#include <algorithm>

namespace Assets
{
	// WLZ
	struct gauss_param_t 
	{
		glm::vec3 Center;
		float Opacity;
		std::array<float, 6> Cov3D;
		std::array<float, 2> Padding;
		gauss_param_t() {}
		gauss_param_t(glm::vec3 center, float opacity, const std::array<float, 6>& cov3D)
			: Center(center), Opacity(opacity), Cov3D(cov3D) {}
	};
	
	struct splat_info_t
	{
		float depth;
		float alpha;
	};
	

	class Sphere final : public Procedural
	{
	public:

		Sphere(const glm::vec3& center, const float radius) :
			Center(center), Radius(radius)
		{
		}

		const glm::vec3 Center;
		const float Radius;

		std::pair<glm::vec3, glm::vec3> BoundingBox() const override
		{
			return std::make_pair(Center - Radius, Center + Radius);
		}

	};

	class Cube final : public Procedural
	{
	public:

		Cube(const glm::vec3& center, const float radius) :
			Center(center), Radius(radius)
		{
		}

		const glm::vec3 Center;
		const float Radius;

		std::pair<glm::vec3, glm::vec3> BoundingBox() const override
		{
			return std::make_pair(Center - Radius, Center + Radius);
		}

	};

	class Cylinder final : public Procedural
	{
	public:

		Cylinder(const glm::vec3& center, const float radius) :
			Center(center), Radius(radius)
		{
		}

		const glm::vec3 Center;
		const float Radius;

		std::pair<glm::vec3, glm::vec3> BoundingBox() const override
		{
			return std::make_pair(Center - Radius, Center + Radius);
		}

	};

	class Mandelbulb final : public Procedural
	{
	public:
		
		Mandelbulb(const glm::vec3 &center, const float radius) :
			Center(center), Radius(radius)
		{
		}

		const glm::vec3 Center;
		const float Radius;

		std::pair<glm::vec3, glm::vec3> BoundingBox() const override
		{
			return std::make_pair(Center - Radius, Center + Radius);
		}
	};

	// WLZ
	class Gauss final : public Procedural
	{
	public:

		Gauss(const glm::vec3 &center, const glm::vec4 &rot, const glm::vec3 &scale, const float opacity) : 
			Center(center), Rot(rot), Scale(scale), Opacity(opacity)
		{
			init_cov3d();
			init_radius();
		} 

		std::pair<glm::vec3, glm::vec3> BoundingBox() const override
		{
			return std::make_pair(Center - Radius, Center + Radius);
		}

		// Gauss Parameters 
		const glm::vec3 Center;
		const glm::vec4 Rot;
		const glm::vec3 Scale;
		const float Opacity;
		float Radius;
		std::array<float, 6> Cov3D;
	
	protected:
		void init_cov3d() 
		{
			// S: Create scaling matrix
			glm::mat3 S = glm::mat3(1.0f);
			S[0][0] = Scale.x;
			S[1][1] = Scale.y;
			S[2][2] = Scale.z;

			// R: Compute rotation matrix from quaternion
			float r = Rot.x;
			float x = Rot.y;
			float y = Rot.z;
			float z = Rot.w;

			glm::mat3 R = glm::mat3(
				1.f - 2.f * (y * y + z * z), 2.f * (x * y - r * z), 2.f * (x * z + r * y),
				2.f * (x * y + r * z), 1.f - 2.f * (x * x + z * z), 2.f * (y * z - r * x),
				2.f * (x * z - r * y), 2.f * (y * z + r * x), 1.f - 2.f * (x * x + y * y)
			);

			// Compute 3D world covariance matrix Sigma
			glm::mat3 M = S * R;
			glm::mat3 Sigma = glm::transpose(M) * M;

			// Covariance is symmetric, only store upper right
			Cov3D[0] = Sigma[0][0];
			Cov3D[1] = Sigma[0][1];
			Cov3D[2] = Sigma[0][2];
			Cov3D[3] = Sigma[1][1];
			Cov3D[4] = Sigma[1][2];
			Cov3D[5] = Sigma[2][2];
		}

		void init_radius() 
		{
			Radius = 3.0 * std::max({Scale.x, Scale.y, Scale.z});
		}
	};
}

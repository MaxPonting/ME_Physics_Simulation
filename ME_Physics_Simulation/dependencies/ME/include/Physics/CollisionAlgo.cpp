#include "CollisionAlgo.h"
#include "CollisionManifold.h"
#include "../ECS/CircleColliderComponent.h"
#include "../ECS/RectangleColliderComponent.h"
#include "../ECS/PolygonColliderComponent.h"
#include "../ECS/TransformComponent.h"
#include "../Helper/Vector2f.h"
#include "../Helper/Edge.h"


namespace ME
{
	CollisionManifold GetPolygonPolygonCollisionManifold(const TransformComponent& transformA, const PolygonColliderComponent* polyA, const TransformComponent& transformB, const PolygonColliderComponent* polyB)
	{
		// Check for collision

		CollisionManifold manifold = SAT(transformA, polyA->GetVertices(transformA), transformB, polyB->GetVertices(transformB));

		return manifold;
	}

	CollisionManifold GetPolygonRectangleCollisionManifold(const TransformComponent& transformA, const PolygonColliderComponent* polyA, const TransformComponent& transformB, const RectangleColliderComponent* rectB)
	{
		CollisionManifold manifold = SAT(transformA, polyA->GetVertices(transformA), transformB, rectB->GetVertices(transformB));

		return manifold;
	}

	CollisionManifold GetPolygonCircleCollisionManifold(const TransformComponent& transformA, const PolygonColliderComponent* polyA, const TransformComponent& transformB, const CircleColliderComponent* circleB)
	{
		// Check for collision
		CollisionManifold manifold = SATCircle(transformA, polyA->GetVertices(transformA), transformB, circleB);

		return manifold;
	}

	CollisionManifold GetRectangleRectangleCollisionManifold(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const RectangleColliderComponent* rectB)
	{
		// Check for collision
		CollisionManifold manifold;

		if (transformA.rotation.getDeg() == 0 && transformB.rotation.getDeg() == 0)
			manifold = AxisAlignedRectangleRectangleCollision(transformA, rectA, transformB, rectB);
		else
			manifold = SAT(transformA, rectA->GetVertices(transformA), transformB, rectB->GetVertices(transformB));

		return manifold;
	}

	CollisionManifold GetRectangleCircleCollisionManifold(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const CircleColliderComponent* circleB)
	{
		// Check for collision
		CollisionManifold manifold;

		if (transformA.rotation.getDeg() == 0)
			manifold = AxisAlignedCircleRectangleCollision(transformA, rectA, transformB, circleB);
		else
			manifold = SATCircle(transformA, rectA->GetVertices(transformA), transformB, circleB);
		
		return manifold;
	}

	CollisionManifold GetCircleCircleCollisionManifold(const TransformComponent& transformA, const CircleColliderComponent* circleA, const TransformComponent& transformB, const CircleColliderComponent* circleB)
	{
		// Check for collision
		Vector2f heading = transformB.position - transformA.position;
		float distance = pow(heading.X * heading.X + heading.Y * heading.Y, 0.5);
		bool collision = distance <= circleA->Radius + circleB->Radius;

		CollisionManifold manifold;
		manifold.HasCollision = collision;

		// Return if no collision
		if (!collision) return manifold;

		// Set Collision manifold
		manifold.Depth = (circleA->Radius + circleB->Radius - distance) / 2;
		manifold.Normal = heading.Normalize();

		return manifold;
	}

	
	CollisionManifold AxisAlignedRectangleRectangleCollision(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const RectangleColliderComponent* rectB)
	{
		if (abs(transformA.position.X - transformB.position.X) > (rectA->Width / 2 + rectB->Width / 2)) return CollisionManifold();
		if (abs(transformA.position.Y - transformB.position.Y) > (rectA->Height / 2 + rectB->Height / 2)) return CollisionManifold();

		CollisionManifold manifold;
		manifold.HasCollision = true;

		float depthX = rectA->Width / 2 + rectB->Width / 2 - abs(transformA.position.X - transformB.position.X);
		float depthY = rectA->Height / 2 + rectB->Height / 2 - abs(transformA.position.Y - transformB.position.Y);

		if (depthX < depthY)
		{
			manifold.Depth = depthX / 2 + 0.001f;
			if (transformA.position.X > transformB.position.X) manifold.Normal = { -1, 0 };
			else manifold.Normal = { 1, 0 };		
		}
		else
		{
			manifold.Depth = depthY / 2 + 0.001f;
			if (transformA.position.Y > transformB.position.Y) manifold.Normal = { 0, -1 };
			else manifold.Normal = { 0, 1 };			
		}

		return manifold;
	}

	CollisionManifold AxisAlignedCircleRectangleCollision(const TransformComponent& transformA, const RectangleColliderComponent* rectA, const TransformComponent& transformB, const CircleColliderComponent* circleB)
	{
		float px = transformB.position.X;
		float py = transformB.position.Y;
		px = fmaxf(px, transformA.position.X - rectA->Width / 2);
		px = fminf(px, transformA.position.X + rectA->Width / 2);
		py = fmaxf(py, transformA.position.Y - rectA->Height / 2);
		py = fminf(py, transformA.position.Y + rectA->Height / 2);

		Vector2f heading = { px - transformB.position.X, py - transformB.position.Y };
		float distanceSqr = heading.LengthSqr();

		CollisionManifold manifold;		

		if (distanceSqr < circleB->Radius * circleB->Radius) manifold.HasCollision = true;

		if (!manifold.HasCollision) return manifold;

		float distance = pow(distanceSqr, 0.5);
		manifold.Normal = -heading.Normalize(distance);
		manifold.Depth = (circleB->Radius - distance) / 2;

		return manifold;
	}

	CollisionManifold SAT(const TransformComponent& transformA, const std::vector<Vector2f>& verticesA, const TransformComponent& transformB, const std::vector<Vector2f>& verticesB)
	{
		//
		// Needs Fixed!!!
		// Can cause error on corners
		// Unknown reason		
		//
		
		Vector2f normal;
		float depth = 0;

		for (int i = 0; i < verticesA.size(); i++)
		{
			Vector2f edge = verticesA[(i + 1) % verticesA.size()] - verticesA[i];
			Vector2f axis = Vector2f(-edge.Y, edge.X).Normalize();

			float minA, maxA;
			float minB, maxB;

			ProjectVertices(verticesA, axis, minA, maxA);
			ProjectVertices(verticesB, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA) return CollisionManifold();

			float axisDepth = fminf(maxB - minA, maxA - minB);

			if (depth == 0)
			{
				depth = axisDepth;
				normal = axis;
			}
			else if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = axis;
			}
		}

		for (int i = 0; i < verticesB.size(); i++)
		{
			Vector2f edge = verticesB[(i + 1) % verticesB.size()] - verticesB[i];
			Vector2f axis = Vector2f(-edge.Y, edge.X).Normalize();

			float minA, maxA;
			float minB, maxB;

			ProjectVertices(verticesA, axis, minA, maxA);
			ProjectVertices(verticesB, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA) return CollisionManifold();

			float axisDepth = fminf(maxB - minA, maxA - minB);

			if (depth == 0)
			{
				depth = axisDepth;
				normal = axis;
			}
			else if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = axis;				
			}
		}

		CollisionManifold manifold;

		manifold.HasCollision = true;
		manifold.Depth = depth;
		manifold.Normal = normal;
		
		return manifold;
	}

	CollisionManifold SATCircle(const TransformComponent& transformA, const std::vector<Vector2f>& verticesA, const TransformComponent& transformB, const CircleColliderComponent* circleB)
	{
		//
		// Needs Fixed!!!
		// Can cause error on corners
		// Unknown reason		
		//

		Vector2f normal;
		float depth = 0;

		for (int i = 0; i < verticesA.size(); i++)
		{
			Vector2f edge = verticesA[(i + 1) % verticesA.size()] - verticesA[i];
			Vector2f axis = Vector2f(-edge.Y, edge.X).Normalize();

			float minA, maxA;
			float minB, maxB;

			ProjectVertices(verticesA, axis, minA, maxA);
			ProjectCircle(transformB.position, circleB->Radius, axis, minB, maxB);

			if (minA >= maxB || minB >= maxA) return CollisionManifold();

			float axisDepth = fminf(maxB - minA, maxA - minB);

			if (depth == 0)
			{
				depth = axisDepth;
				normal = axis;
			}
			else if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = axis;
			}
		}

		Vector2f closestPoint = verticesA[0];
		float minDistance = (verticesA[0] - transformB.position).Magnitude();

		for (int i = 1; i < verticesA.size(); i++)
		{
			float distance = (verticesA[i] - transformB.position).Magnitude();
			if (distance < minDistance)
			{
				minDistance = distance;
				closestPoint = verticesA[i];
			}
		}

		Vector2f axis = closestPoint - transformB.position;

		float minA, maxA;
		float minB, maxB;

		ProjectVertices(verticesA, axis, minA, maxA);
		ProjectCircle(transformB.position, circleB->Radius, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA) return CollisionManifold();

		float axisDepth = fminf(maxB - minA, maxA - minB);

		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}

		CollisionManifold manifold;
		manifold.HasCollision = true;
		manifold.Depth = depth;
		manifold.Normal = normal;

		return manifold;

	}

	void ProjectVertices(const std::vector<Vector2f>& vertices, const Vector2f& axis, float& min, float& max)
	{
		min = vertices[0] * axis;
		max = min;

		for (int i = 1; i < vertices.size(); i++)
		{
			float proj = vertices[i] * axis;

			if (proj < min) min = proj;
			if (proj > max) max = proj;
		}
	}

	void ProjectCircle(const Vector2f& center, const float& radius, const Vector2f& axis, float& min, float& max)
	{
		Vector2f heading = axis * radius;

		Vector2f A = center + heading;
		Vector2f B = center - heading;

		min = A * axis;
		max = B * axis;

		if (min > max)
		{
			float temp = min;
			min = max;
			max = temp;
		}

	}

	Vector2f FindArithmeticMean(const std::vector<Vector2f>& vertices)
	{
		float sumX = 0;
		float sumY = 0;

		for (int i = 0; i < vertices.size(); i++)
		{
			sumX += vertices[i].X;
			sumY += vertices[i].Y;
		}

		return { sumX / vertices.size(), sumY / vertices.size() };
	}

	void RotateVertices(const float rotation, std::vector<Vector2f>& vertices)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			Vector2f rotatedVector;
			rotatedVector.X = vertices[i].X * cosf(rotation) - sinf(rotation) * vertices[i].Y;
			rotatedVector.Y = vertices[i].X * sinf(rotation) + cosf(rotation) * vertices[i].Y;
			vertices[i] = rotatedVector;
		}
	}
	
	void SolveCollision(Collision collision)
	{

		// Seperate bodies
		// A

		Vector2f transformationA = collision.Manifold.Normal * collision.Manifold.Depth;
		collision.TransformA.position += transformationA;

		// B

		Vector2f transformationB = -collision.Manifold.Normal * collision.Manifold.Depth;
		collision.TransformB.position += transformationB;

		bool isImpulse = true;

		if (collision.RigidbodyA != nullptr)
		{
			if (collision.RigidbodyA->IsStatic == true)
			{
				collision.TransformA.position -= transformationA;
				collision.TransformB.position += transformationB;
			}
		}
		else isImpulse = false;

		if (collision.RigidbodyB != nullptr)
		{
			if (collision.RigidbodyB->IsStatic == true)
			{
				collision.TransformB.position -= transformationB;
				collision.TransformA.position += transformationA;
			}
		}
		else isImpulse = false;

		if (!isImpulse) return;

		// Apply Impulse

		Vector2f relativeVelocity = collision.RigidbodyA->Velocity - collision.RigidbodyB->Velocity;

		float e = fminf(collision.RigidbodyA->GetRestitution(), collision.RigidbodyB->GetRestitution());

		float impulseMagnitude = -(1 + e) * (relativeVelocity * collision.Manifold.Normal) / 
			(1 / collision.RigidbodyA->Mass + 1 / collision.RigidbodyB->Mass);

		Vector2f impulse = { collision.Manifold.Normal.X * impulseMagnitude, collision.Manifold.Normal.Y * impulseMagnitude };

		collision.RigidbodyA->Velocity += impulse;
		collision.RigidbodyB->Velocity -= impulse;

		if (collision.RigidbodyA->IsStatic)
		{
			collision.RigidbodyA->Velocity -= impulse;
			collision.RigidbodyB->Velocity -= impulse;
		}
		else if (collision.RigidbodyB->IsStatic)
		{
			collision.RigidbodyA->Velocity += impulse;
			collision.RigidbodyB->Velocity += impulse;
		}

	}
}
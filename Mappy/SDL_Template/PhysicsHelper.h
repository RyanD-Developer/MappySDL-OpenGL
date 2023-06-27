#ifndef __PHYSICSHELPER_H
#define __PHYSICSHELPER_H
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "MathHelper.h"

inline bool CircleVsCircleCollision(CircleCollider* c1, CircleCollider* c2) {
	return (c1->Position() - c2->Position()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool BoxVsCircleCollision(BoxCollider* box, CircleCollider* circle) {
	Vector2 circlePos = circle->Position();
	float radius = circle->GetRadius();

	Vector2 quad[4];
	quad[0] = box->GetVertexPos(0);
	quad[1] = box->GetVertexPos(1);
	quad[2] = box->GetVertexPos(2);
	quad[3] = box->GetVertexPos(3);

	for (int i = 0; i < 4; i++) {
		if ((quad[i] - circlePos).Magnitude() < radius) {
			return true;
		}
	}

	if (PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(1), circlePos) < radius ||
		PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(2), circlePos) < radius ||
		PointToLineDistance(box->GetVertexPos(2), box->GetVertexPos(3), circlePos) < radius ||
		PointToLineDistance(box->GetVertexPos(3), box->GetVertexPos(1), circlePos) < radius) {
		return true;
	}

	if (PointInPolygon(quad, 4, circlePos)) {
		return true;
	}

	return false;
}

inline bool BoxVsBoxCollision(BoxCollider* b1, BoxCollider* b2) {
	Vector2 projAxes[4];

	projAxes[0] = (b1->GetVertexPos(0) - b1->GetVertexPos(1)).Normalized();
	projAxes[1] = (b1->GetVertexPos(0) - b1->GetVertexPos(2)).Normalized();
	projAxes[2] = (b2->GetVertexPos(0) - b2->GetVertexPos(1)).Normalized();
	projAxes[3] = (b2->GetVertexPos(0) - b2->GetVertexPos(2)).Normalized();

	float b1Min = 0.0f, b1Max = 0.0f;
	float b2Min = 0.0f, b2Max = 0.0f;
	float proj1 = 0.0f, proj2 = 0.0f;

	for (int a = 0; a < 4; a++) {
		for (int v = 0; v < 4; v++) {
			proj1 = Dot(b1->GetVertexPos(v), projAxes[a]);
			proj2 = Dot(b2->GetVertexPos(v), projAxes[a]);

			if (v == 0) {
				b1Min = b1Max = proj1;
				b2Min = b2Max = proj2;
			}
			else {
				if (proj1 < b1Min)
					b1Min = proj1;
				if (proj1 > b1Max)
					b1Max = proj1;

				if (proj2 < b2Min)
					b2Min = proj2;
				if (proj2 > b2Max)
					b2Max = proj2;
			}
		}
		float halfDist1 = (b1Max - b1Min) * 0.5f;
		float midPoint1 = b1Min + halfDist1;

		float halfDist2 = (b2Max - b2Min) * 0.5f;
		float midPoint2 = b2Min + halfDist2;

		if (abs(midPoint1 - midPoint2) > (halfDist1 + halfDist2)) {
			return false;
		}
	}
	return true;
}

inline bool ColliderVsColliderCheck(Collider* c1, Collider* c2) {
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle)
		return CircleVsCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	else if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Circle)
		return BoxVsCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
	else if (c2->GetType() == Collider::ColliderType::Box && c1->GetType() == Collider::ColliderType::Circle)
		return BoxVsCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
	else if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Box)
		return BoxVsBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
	else
		return false;
}
#endif
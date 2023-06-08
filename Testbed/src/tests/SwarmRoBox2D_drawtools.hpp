/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 *
 * Tools for user dependent shapes.
 */

#ifndef TESTS_SWARMROBOX2D_DRAWTOOLS_HPP_
#define TESTS_SWARMROBOX2D_DRAWTOOLS_HPP_

#include "../test.h"

static void DrawTriangle(const b2Vec2 &center, float angle, float size,
		const b2Color &color)
{
	static const int32 vertexCount = 3;
	b2Vec2 vertices[vertexCount];
	float foward_angle = angle + b2_pi / 2.0f;
	float center_angle = 3.0 / 4.0 * b2_pi;

	vertices[0].x = center.x + size * cosf(foward_angle);
	vertices[0].y = center.y + size * sinf(foward_angle);
	vertices[1].x = (vertices[0].x - center.x) * cosf(center_angle)
			- (vertices[0].y - center.y) * sinf(center_angle) + center.x;
	vertices[1].y = (vertices[0].x - center.x) * sinf(center_angle)
			+ (vertices[0].y - center.y) * cosf(center_angle) + center.y;
	vertices[2].x = (vertices[0].x - center.x) * cosf(-center_angle)
			- (vertices[0].y - center.y) * sinf(-center_angle) + center.x;
	vertices[2].y = (vertices[0].x - center.x) * sinf(-center_angle)
			+ (vertices[0].y - center.y) * cosf(-center_angle) + center.y;

	g_debugDraw.DrawSolidPolygonAlpha(vertices, vertexCount, color);
}

static void DrawRectangle(const b2Vec2 &center, float angle, float width,
		float height, const b2Color &color)
{
	static const int32 vertexCount = 4;
	b2Vec2 vertices[vertexCount];

	vertices[0].x = (center.x + width / 2.0f) * cosf(angle)
			- (center.y + height / 2.0f) * sinf(angle);
	vertices[0].y = (center.y + height / 2.0f) * cosf(angle)
			+ (center.x + width / 2.0f) * sinf(angle);
	vertices[1].x = (center.x - width / 2.0f) * cosf(angle)
			- (center.y + height / 2.0f) * sinf(angle);
	vertices[1].y = (center.y + height / 2.0f) * cosf(angle)
			+ (center.x - width / 2.0f) * sinf(angle);
	vertices[2].x = (center.x - width / 2.0f) * cosf(angle)
			- (center.y - height / 2.0f) * sinf(angle);
	vertices[2].y = (center.y - height / 2.0f) * cosf(angle)
			+ (center.x - width / 2.0f) * sinf(angle);
	vertices[3].x = (center.x + width / 2.0f) * cosf(angle)
			- (center.y - height / 2.0f) * sinf(angle);
	vertices[3].y = (center.y - height / 2.0f) * cosf(angle)
			+ (center.x + width / 2.0f) * sinf(angle);

	g_debugDraw.DrawSolidPolygonAlpha(vertices, vertexCount, color);
}

////
//void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
//{
//    b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
//
//    for (int32 i = 1; i < vertexCount - 1; ++i)
//    {
//        m_triangles->Vertex(vertices[0], fillColor);
//        m_triangles->Vertex(vertices[i], fillColor);
//        m_triangles->Vertex(vertices[i + 1], fillColor);
//    }
//
//    b2Vec2 p1 = vertices[vertexCount - 1];
//    for (int32 i = 0; i < vertexCount; ++i)
//    {
//        b2Vec2 p2 = vertices[i];
//        m_lines->Vertex(p1, color);
//        m_lines->Vertex(p2, color);
//        p1 = p2;
//    }
//}

////
//void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
//{
//    const float k_segments = 16.0f;
//    const float k_increment = 2.0f * b2_pi / k_segments;
//    float sinInc = sinf(k_increment);
//    float cosInc = cosf(k_increment);
//    b2Vec2 v0 = center;
//    b2Vec2 r1(cosInc, sinInc);
//    b2Vec2 v1 = center + radius * r1;
//    b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
//    for (int32 i = 0; i < k_segments; ++i)
//    {
//        // Perform rotation to avoid additional trigonometry.
//        b2Vec2 r2;
//        r2.x = cosInc * r1.x - sinInc * r1.y;
//        r2.y = sinInc * r1.x + cosInc * r1.y;
//        b2Vec2 v2 = center + radius * r2;
//        m_triangles->Vertex(v0, fillColor);
//        m_triangles->Vertex(v1, fillColor);
//        m_triangles->Vertex(v2, fillColor);
//        r1 = r2;
//        v1 = v2;
//    }
//
//    r1.Set(1.0f, 0.0f);
//    v1 = center + radius * r1;
//    for (int32 i = 0; i < k_segments; ++i)
//    {
//        b2Vec2 r2;
//        r2.x = cosInc * r1.x - sinInc * r1.y;
//        r2.y = sinInc * r1.x + cosInc * r1.y;
//        b2Vec2 v2 = center + radius * r2;
//        m_lines->Vertex(v1, color);
//        m_lines->Vertex(v2, color);
//        r1 = r2;
//        v1 = v2;
//    }
//
//    // Draw a line fixed in the circle to animate rotation.
//    b2Vec2 p = center + radius * axis;
//    m_lines->Vertex(center, color);
//    m_lines->Vertex(p, color);
//}

#endif /* TESTS_SWARMROBOX2D_DRAWTOOLS_HPP_ */

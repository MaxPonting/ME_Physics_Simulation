#include "Scanline.h"

#include <algorithm>

namespace ME
{
	std::vector<Vector2f> Scanline (std::vector<Vector2f> verts, unsigned int w, unsigned int h)
	{
		std::vector<Vector2f> points;
		points.reserve(w * h);

		float minX, maxX, minY, maxY;
		AssignMinMaxXY(verts, minX, maxX, minY, maxY);

		std::vector<float> inter;
		inter.reserve(verts.size());
		int i, j;
		float x;

		//loop each scan line
		for (float currentY = minY; currentY < maxY; currentY++)
		{
			j = verts.size() - 1;
			for (i = 0; i < verts.size(); i++)
			{
				if ((verts[i].Y <= currentY && verts[j].Y >= currentY
					|| verts[j].Y <= currentY && verts[i].Y >= currentY)
					&& (verts[i].Y != verts[j].Y))
				{
					x = (verts[i].X + (currentY - verts[i].Y) / (verts[j].Y - verts[i].Y) * (verts[j].X - verts[i].X));
					//Check intersection is not on an inward edge
					bool inwardEdge = false;
					if (verts[i].Y == currentY)
					{
						if (i == verts.size() - 1)
						{
							if ((verts[0].Y >= currentY && verts[j].Y >= currentY) || (verts[0].Y <= currentY && verts[j].Y <= currentY))
							{
								inwardEdge = true;
							}
						}
						else
						{
							if ((verts[i + 1].Y >= currentY && verts[j].Y >= currentY) || (verts[i + 1].Y <= currentY && verts[j].Y <= currentY))
							{
								inwardEdge = true;
							}
						}
					}
					else if (verts[j].Y == currentY)
					{
						if (j == 0)
						{
							if ((verts[i].Y >= currentY && verts[verts.size() - 1].Y >= currentY) || (verts[i].Y <= currentY && verts[verts.size() - 1].Y <= currentY))
							{
								inwardEdge = true;
							}
						}
						else
						{
							if ((verts[i].Y >= currentY && verts[j - 1].Y >= currentY) || (verts[i].Y <= currentY && verts[j - 1].Y <= currentY))
							{
								inwardEdge = true;
							}
						}
					}
					if (!inwardEdge)
					{
						bool inside = false;
						for (std::vector<float>::iterator it = inter.begin(); it != inter.end(); it++)
						{
							if (*it == x) { inside = true; break; }
						}
						if (!inside) { inter.push_back(x); }
					}
					//Add outline points				
					points.push_back(Vector2f(x, currentY));
				}
				j = i;
			}
			//Sort intersections		
			sort(inter.begin(), inter.end());
			//Add points
			for (i = 0; i < inter.size(); i += 2)
			{
				if (i == inter.size() - 1) { break; }
				if (inter[i] >= maxX) { break; }
				if (inter[i + 1] > minX)
				{
					if (inter[i] < minX) { inter[i] = minX; }
					if (inter[i + 1] < minX) { inter[i + 1] = maxX; }
					for (x = inter[i] + 1; x < inter[i + 1]; x++)
					{
						//Add fill points
						points.push_back(Vector2f(x, currentY));
					}
				}
			}
			//Clear intersections;
			inter.clear();
		}

		//Add horizontal outlines
		i = 0;
		j = verts.size() - 1;
		float x1, x2, min, max;
		for (i = 0; i < verts.size(); i++)
		{
			if ((verts[i].Y == verts[j].Y))
			{
				x1 = verts[i].X; x2 = verts[j].X;
				min = std::min(x1, x2); max = std::max(x1, x2);
				for (int x = min; x <= max; x++)
				{
					points.push_back(Vector2f(x, verts[i].Y));
				}
			}
			j = i;
		}
		
		return points;
	}

	void AssignMinMaxXY(std::vector<Vector2f> verts, float& minX, float& maxX, float& minY, float& maxY)
	{
		maxY = verts[0].Y;
		minY = verts[0].Y;
		maxX = verts[0].X;
		minX = verts[0].X;
		for (int i = 0; i < verts.size(); i++)
		{
			if (verts[i].Y > maxY) maxY = verts[i].Y;
			if (verts[i].Y < minY) minY = verts[i].Y;
			if (verts[i].X > maxX) maxX = verts[i].X;
			if (verts[i].X < minX) minX = verts[i].X;
		}
	}

	
}
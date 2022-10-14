#pragma once

#include <array>

class AABB
{
public:
	AABB();

	bool collides(const AABB& other) const;

	const std::array<int, 2>& getCenter() const { return mCenter; }
	const std::array<int, 2>& getExtent() const { return mExtent; }

    void setCenter(const std::array<int, 2>& center) { mCenter = center; }
    void setExtent(const std::array<int, 2>& extent) { mExtent = extent; }

    int getCenterX() const { return mCenter[0]; }
    int getCenterY() const { return mCenter[1]; }
    int getExtentX() const { return mExtent[0]; }
    int getExtentY() const { return mExtent[1]; }

    void setCenterX(int x) { mCenter[0] = x; }
    void setCenterY(int y) { mCenter[1] = y; }
    void setExtentX(int x) { mExtent[0] = x; }
    void setExtentY(int y) { mExtent[1] = y; }

private:
	std::array<int, 2> mCenter;
	std::array<int, 2> mExtent;
};


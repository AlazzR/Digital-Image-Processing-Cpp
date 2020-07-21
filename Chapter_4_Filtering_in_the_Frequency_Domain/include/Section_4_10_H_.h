#ifndef _SECTION_4_10_H_
#define _SECTION_4_10_H_
#include "main_header.h"
#include <unordered_set>
class coordinate
{
private:
	int x;
	int y;
public:
	coordinate(int x, int y);

	int getX() const;
	int getY() const;
};
struct customCompare
{
public:
	bool operator()(const coordinate& lhs, const coordinate& rhs) const;
};
struct customHashing
{
	size_t operator()(const coordinate& obj)const;
};
std::unordered_set<coordinate, customHashing, customCompare> find_loc_to_suppress(cv::Mat&, int width=40);
cv::Mat creating_notch(int P, int N, float D0, int uk, int vk, int n);
void filtering_by_notch(const cv::Mat& img, float D0, int n);

#endif _SECTION_4_10_H_
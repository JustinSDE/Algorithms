#pragma once
#define NOTCONNECTED 100
class PtInfo
{
public:
	PtInfo();
	~PtInfo();
	int PointID;
	int PrevPointID;
	int TotalDistanceToSource;
};


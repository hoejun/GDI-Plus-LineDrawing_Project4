#pragma once

class CShape
{
public:
	CShape();
	CShape(CPoint startPos);

	~CShape();

public:
	CPoint Start;//½ÃÀÛ ÁÂÇ¥
	CPoint End;//³¡ ÁÂÇ¥
};
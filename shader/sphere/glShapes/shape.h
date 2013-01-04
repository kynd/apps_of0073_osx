#ifndef __SHAPE__
#define __SHAPE__

class Shape
{
public:
    Shape();
    virtual ~Shape();

    virtual void draw() = 0;
	virtual void update();
};
#endif

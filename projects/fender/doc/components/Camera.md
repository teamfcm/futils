# Components::Camera

> A Camera is an object used to know what to display.

```c++
class Camera : GameObject
{
	// A Camera can target either an Object, or a point in space.
	union Target
	{
		GameObject *,
		futils::Point
	};
	
	enum FollowMode
    {
    	Slow,
    	Instant,
    	DistanceFirst
    };
 
 	std::string name;
	Camera::Target target;
};
```


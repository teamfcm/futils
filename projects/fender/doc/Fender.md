# Fender

Well, Fender is a huge project. It will take some time before its complete. Let's break it down into steps.

## Window

Because fender is a game engine, its going to render to the screen. It matters little what's under the hood, at some point a window is required.

So the first system we'll implement is [Window]. What components does it handle ? 

(Meta) ! Yeah...

> Insert screenshot of simple window (800x600)

A (Meta) is the data describing a basic Window. 

```c++
class fender::Meta : futils::IComponent
{
  std::string title;
  futils::Asset icon;
  futils::WStyle style;
};
```

## Camera

Having a window is good. But what is it going to display ? In order to display anything, a camera is required.

You could potentially have several cameras, switch between them whenever you want or need to. You cannot however have several cameras rendering at the same time (for now ?).

> Insert screenshot of camera focus point (crosshair)

The [Camera] handles, yet again unsurprisingly (Camera) components. 

```c++
class fender::Camera : futils::IEntity
{
	(Camera)
	(Children)
};

class fender::Camera : futils::IComponent
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

As you can see, a camera is a simple thing. You give it a name and you specify what you want to follow.

## GameObject

So now we have a camera but nothing to film. Let's create a GameObject ! Its an entity, but what is it made of ?

```c++
class GameObject : futils::IEntity
{
	(Transform) // Any object in the game needs to have a Position, rotation and scale.
	(Children) // Any GameObject can have children.
};

class Sprite : GameObject
{
	(Image) // The Image component will contain image-size and image-path
};

class WhiteSquare : Sprite
{
	(Color) // We'll just add a filter to modify the pixels
};
```

(Transform) indicates where the object is in the world. If you want to fix the object in the view (to make a gui object for example) you can use the (Children) of Camera. Therefore, whenever the Camera moves, all its Children move with it and stay in view. 

(Transform) contains a position that will be used to know where to display content. Here's a simple image explaining how this works.

> Insert screenshot of grid with basic sprite 

Notes :

​	{Trinité}

​	{Children} -> GameObject, 

​	{ListView} -> GameObject, 

​	(Transform), 

​	(RelPos)
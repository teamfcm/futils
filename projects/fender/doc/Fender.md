# Fender

Well, Fender is a huge project. It will take some time before its complete. Let's break it down into steps.

## Window

Because fender is a game engine, its going to render to the screen. It matters little what's under the hood, at some point a window is required.

So the first system we'll implement is [Window]. What components does it handle ? 

Yes. Unsurprisingly it handles (Window).

> Insert screenshot of simple window (800x600)

A (Window) is the data describing a basic Window. 

```c++
class fender::Window : futils::IComponent
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
class fender::Camera : futils::IComponent
{
	// A Camera can target either an Object, or a point in space.
	union Target
	{
		GameObject *,
		futils::Point
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




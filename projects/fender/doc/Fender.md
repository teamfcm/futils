# Fender

Well, Fender is a huge project. It will take some time before its complete. Let's break it down into steps.

## Window

Because fender is a game engine, its going to render to the screen. It matters little what's under the hood, at some point a window is required.

So the first system we'll implement is [Window]. What components does it handle ? 

(Meta) ! Yeah...

> Insert screenshot of simple window (800x600)

A (Meta) is the data describing a basic Window. 

### Component

```c++
class fender::Meta : futils::IComponent
{
	std::string title; // Displayed title
	futils::Asset icon; // Displayed Icon
	futils::WStyle style; // Nobar, titlebar, etc...
	vec2f position; // Where should the window open ?
	vec2f size; // How big should the window be ?
	bool visible{false}; // Should the system display this window ?
    
    // Updated by [Window] :
	vec2f actualPosition;
	vec2f actualSize;
	vec2f screenSize;
	bool isOpen{false};
	bool isClosed{false};
};
```

### Entity

```c++
class fender::Window : futils::IEntity
{
	(Window)
	// Different constructors, does not really matter.
	void open(); // Emits OpenWindow request unless already open
	void close(); // Emits CloseWindow request unless already closed
	void resize(vec2f updatedSize); // close() and open() window with updated size
	void move(vec2f updatedPos); // close() and open() window with updated pos
	void rename(std::string title); // Really ? You don't know ?
};
```

### System

#### Required Events

```c++
struct ComponentAttached<Window>
{
	Window &window;
};

struct ComponentDeleted<Window>
{
	Window &window;
};
```

#### Events Emitted

```c++
struct WindowOpened
{
	Window &window;
};

struct WindowClosed
{
	Window &window;
};
```

#### Run Pseudocode

```c++
void Window::run(float)
{
	// Events make it easy to track new and deprecated windows.
  	if (window) was visible and is now hidden
      	closeWindow and send WindowClosed
    if (window) was hidden and is now visible
      	openWindow and send WindowOpened
};
```

## World

Cool, we have Window, now let's build a {World} inside that Window !

```c++
class World : futils::IEntity
{
	(World)
};

class World : futils::IComponent
{
	using GridUnit = float;
	
	std::string name;
	float unit; // Describes grid unit (one square for unit pixels)
	Vec2<GridUnit> size;
	GameTime time; // InGame time
	... // Basically, env variables.
};
```

## Camera

Having a window is good. But what is it going to display ? In order to display anything, a camera is required.

You could potentially have several cameras, switch between them whenever you want or need to. You cannot however have several cameras rendering at the same time (for now ?).

> Insert screenshot of camera focus point (crosshair)

The [Camera] handles, unsurprisingly (Camera) components. 

```c++
class fender::Camera : GameObject
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

Its main purpose is to determine which entities are visible (and should therefore be rendered) and which are not. Then, dedicated systems will simply access "visible" entities through the (Visible) and render them as they like.

> Insert screenshot of grid

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

## GUI

But before you can have a game, it would be nice to have a Menu ! But a Menu is an object that is glued to the camera view, not "in" the world. So how are going to place that object, since **everything** is in GridUnit position ?

Well, here comes the Children mechanic.

### Children

```c++
class Children : futils::IComponent
{
	using Container = std::vector<GameObject>;
	
	Container children;
};
```

This component indicates that the entity transfers its transformations (movement, rotation, scale) to all its children. This can be used to create a **logic** bound between entities. 

> Insert screenshot of ship and drone rotation around it.

You need to indicate where the child is relatively to its parent.

```c++
class ChildInfo : futils::IComponent
{
	bool gridUnit{false}; // By default, position is in pourcentage
	Vec2<float> relPos;
};
```

For example, you could say an object is 10% (relative to the parent height) above another one, or that it's one GridUnit above. 

**Why are we talking about children ? I thought we were talking about GUI ?**

Well exactly, GUI are GameObjects, they exist in the world, but they follow the Camera to be "always" visible.

So we simply make our GUI objects children of the Camera.

```c++
class SomeSystem : futils::ISystem
{
  	World world;
	Camera cam;
	Button exit;
}

void SomeSystem::init() {
  	auto &gui = cam.get<Children>();
	gui.add(exit);
	auto &exitPos = exit.get<ChildInfo>();
	exitPos.relPos.x = 10;
	exitPos.relPos.y = 10;
	exit.onClick = [this](){
		this->shouldStop = true;
	};
}

void SomeSystem::run() {
	if (shouldStop)
    	this->stop();
}

```

When you make ```exit``` a child of ```cam```, a new component is added ```ChildInfo```, which describes how the child is positioned relativ to its parent. But it can be a bit tiresome to write positions all the time relative to the camera. What if you had 2, 3 or more buttons ? So here comes... **ListView** !

### ListView

```c++
class SomeSystem : futils::ISystem
{
  	World world;
	Camera cam;
	ListView mainMenu;
};

void SomeSystem::init() {
	mainMenu.direction = Directions::TopDown;
  	auto &gui = cam.get<Children>();
	gui.add(mainMenu);
	
	auto &menuPos = mainMenu.get<ChildInfo>();
	menuPos.relPos.x = 10;
	menuPos.relPos.y = 10;
	
	auto &size = mainMenu.get<Transform>();
	size.x = 50;
	size.y = 80;
	
    auto exit = Button("Quit", [this](){
    	this->shouldStop = true;
    });
    
    mainMenu.push_back(exit);
    mainMenu.emplace_front<Button>("Play", [this](){
    	this->entityManager->addSystem<MyGame>();
    	this->shouldStop = true;
    });
}

void SomeSystem::run() {
	if (shouldStop)
    	this->stop();
}
```

Pretty neat right ? As you can see you can push already existing elements, or build them in place.

```c++
class ListView : GameObject
{
	(ListView)
	void push_back(GameObject &);
	void push_front(GameObject &);
	void insert(GameObject &, int index);
	template <typename T, typename ...Args>
	T &emplace_back(Args ...args);
	template <typename T, typename ...Args>
	T &emplace_front(Args ...args);
};

class ListView : futils::IComponent
{
	using Container = std::vector<GameObject>;
	
	Container elements;
};
```

Quite like the Children mechanics, elements added to a ListView are attached (ViewInfo).

```c++
class ViewInfo : futils::IComponent
{
  	futils::Pct margin;
};
```

## Text

// Ok c'est cool mais comment j'affiche un texte pour l'utilisateur ? 

// Exemples : label de barre de chargement, version du moteur, titre du jeu...

{Text}

```c++
class Text : futils::IEntity
{
	(Text)
	(Color)
	(Progressiv)?
	(Center)?
	...
};

class Text : futils::IComponent
{
	using Lang = int;
	
	std::unordered_map<Lang, std::string> content;
	futils::FontInfo font;
};
```

## InputEvents



## Config


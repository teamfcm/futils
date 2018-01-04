# Fender

Well, Fender is a huge project. It will take some time before its complete. Let's break it down into steps.

## Window

Because fender is a game engine, its going to render to the screen. It matters little what's under the hood, at some point a window is required.

So the first system we'll implement is [Window]. What components does it handle ? 

(Window) ! Yeah...

> Insert screenshot of simple window (800x600)

A (Window) is the data describing a basic Window. 

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

### Component

```c++
class World : futils::IComponent
{
	using GridUnit = float;
	
	std::string name; // ProximaCentauri B
	GridUnit unit; // How many pixels does a square represent ?
	Vec3<GridUnit> size; // So how big is it ? Where does the cam stop ? (x, y, z)
};
```

### Entity

```c++
class World : futils::IEntity
{
	(World)
};
```

### System

#### Required Events

```c++
struct ComponentAttached<World>
{
	World &world;
};

struct ComponentDeleted<World>
{
	World &world;
};
```

#### Events Emitted

```c++
struct WorldResized
{
  	World &world;
  	vec2<GridUnit> oldSize;
};

struct WorldRenamed
{
  	World &world;
  	std::string oldName;
};

struct GridUnitUpdated
{
  	World &world;
  	GridUnit old;
}
```

#### Run pseudocode

```c++
void World::run(float)
{
	// Events make it easy to track new and deprecated worlds.
	if (world).size has changed // Resize the world when loading another chunk or level ?
		resizeWorld and send WorldResized
	if (world).name has changed // Rename the world... yeah... ?
		send WorldRenamed
	if (world).unit has changed // TimeSpace continuum breach ?
      	send GridUnitUpdated
}
```

## GameObject

Yay, we have given birth to a World. Let's create a GameObject ! Its an entity, but what is it made of ?

### Component 

```c++
class GameObject : futils::IComponent
{
	bool visible;
};
```

### Entity

```c++
class GameObject : futils::IEntity
{
	(GameObject)
	(Transform)
	(Border) // This component is useful for debugging (so its.. optional)
};
```

## Camera

> Used to know what to display, and some world related information. Does not display GameObjects.

Having a window is good. Setting the basic world variables is better. Having GameObjects is GREAT. Actually **SEING ANYTHING WOULD BE NICE**. Enter : the Camera.

The goal of the Camera is to determine which entities are in view. This is a crucial system in the engine. Note that you could potentially have several cameras, switch between them whenever you want or need to. 

**So, even [Camera] doesn't display anything ? wtf ?**

Yeah.. but soon you'll understand why !

### Component

```c++
class fender::Camera : futils::IComponent
{
	enum FollowMode
    {
    	Slow,
    	Instant,
    	DistanceFirst
    };
    
 	std::string name;
	GameObject *target{nullptr};
	FollowMode followMode;
};
```

### Entity

```c++
class Camera : GameObject
{
	(Camera) // Obviously.
	(Children) // Used for the GUI, you'll soon understand why.
};
```

**Note: The size of the camera will be updated by [Camera], you should not touch it.**

### System

```c++
class Camera : futils::ISystem
{
	struct Layer
    {
    	int index;
    	std::vector<entities::GameObjects *> objects;
    }
	std::vector<entities::GameObjects *> gameObjects;
	std::unordered_map<int, Layer> layers;
public:
	void run(float) override;
};
```

#### Required Events

```c++
struct ComponentAttached<GameObject>
{
	GameObject &go;
};

struct ComponentDeleted<GameObject>
{
	GameObject &go;
};
```

#### Events emitted

```c++
struct GameObjectEnteredView
{
	GameObject &go;
	Camera &cam;
};

struct GameObjectLeftView
{
	GameObject &go;
  	Camera &cam;
};

struct RenderingLayer // This event is crucial ! All rendering systems should care.
{
  	int z-index; // Which layer is to be rendered
	const Container &objects; // And which objects are on that layer
 	componentWindow win;
};

struct RenderingDone // When all visible layers are rendered.
{
	
};
```

#### Run pseudocode

```c++
void Camera::run(float f)
{
  if its time to refresh the screen (60 fps cap) run
    otherwise return
    
	auto &activeCam = getActiveCam();
	Sort gameObjects by z-index (anything "behind" is not visible and anything "too far")
    Foreach gameObject (go) :
    {
      	bool visible = go.visible;
      	updateView(go); // Checks z-index first, then distance to cam.
		if (go) was visible but is not anymore
          markOutOfView(go) and send GameObjectLeftView
		if (go) enters view
          markInView(go) and send GameObjectEnteredView
    }
  For each valid z-index (from further to closer)
    send RenderingLayer event with index and map
};
```

## GridRenderer

> This system displays the grid over everything else.

### System

#### Required events

```c++
struct RenderingDone
{
  
};
// -> Reaction is to display the grid over everything else
```

#### Events emitted

```c++
struct GridRendered
{
	
};
```

#### Run pseudocode

> Insert screenshot of grid

## ImageRenderer

// Now that we have a framework for modular rendering, we can code an independant system that displays images. It will wait for the RenderingLayer event, and for each entity, take (Image) and render it to the screen.

It does not need to check the position, the camera has done that for him before.

________

But before you can have a game, it would be nice to have a Menu ! But a Menu is an object that is glued to the camera view, not "in" the world. So how are going to place that object, since **everything** is in GridUnit position ?

Well, here comes the Children feature.

## Children

```c++
class Children : futils::IComponent
{
	Container children;
};
```

This component indicates that the entity transfers its transformations (movement, rotation, scale) to all its children. This can be used to create a **logic** bound between entities. 

> Insert screenshot of ship and drone rotation around it.

You need to indicate where the child is relatively to its parent.

```c++
class ChildInfo : futils::IComponent
{
	bool gridUnit{false}; // By default, position is in percentage of parent size
	Vec3<float> relPos; // 3d position, because why not? fender is 2.5d!
};
```

For example, you could say an object is 10% (relative to the parent height) above another one, or that it's one GridUnit above. 

**Why are we talking about children ? I thought we were talking about GUI ?**

Well exactly, GUI are GameObjects, they exist in the world, but they follow the Camera, therefore they are "always" visible.

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

When you make ```exit``` a child of ```cam```, a new component is added ```ChildInfo```, which describes how the child is positioned relativ to its parent. But it can be a bit tiresome to write positions all the time relative to the camera. What if you had 2, 3 or more buttons ? So here comes... **View** !

## View

### Component

```c++
class View : futils::IComponent
{
	enum Direction
    {
		Vertical,
		Horizontal
    };
    
    enum HorizontalAlignment
    {
		Left = 0,
		Center,
		Right
    };
    
    enum VerticalAlignment
    {
		Top,
		Middle,
		Bottom
    };
    
	Container<GameObjects> content;
	Direction direction;
	HorizontalAlignment h-align;
	VerticalAlignment v-align;
	bool reverse{false};
}
```

### Entity

```c++
class View : GameObject
{
	(View)
};
```

### System

Quite like the Children mechanics, elements added to a View are attached (ViewInfo) to specify how to be handled in the View.

```c++
class ViewInfo : futils::IComponent
{
	Vec4<futils::Pct> padding;
  	Vec4<futils::Pct> margins;
  	VerticalAlignment v-align;
  	HorizontalAlignment h-align;
};
```

#### Required Events

#### Events Emitted

#### Run pseudocode

```c++
void systems::View::run(float)
{
	foreach view in views:
		if view has no content continue
		else foreach elem in view.content:
			recursively update from parent to child base on elem.(ViewInfo)
}
```

**Note: This is a good example of systems optimization. First, we'll iterate over every (View), sometimes updating the same (View) several times per run. Then, with a better implementation, we could keep a tree of view and update recursively from top to bottom with only one update per view per run.**

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


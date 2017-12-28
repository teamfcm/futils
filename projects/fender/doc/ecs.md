# ECS

> Disclaimer : This is not actual working code, this is only for helping you understand the Engine.

The ECS is a design pattern used to favor **composition** over inheritance. You create entities, that are composed of components and meaningful output is done through the systems in a regular (systemic) way.

For example, here is a Window :

```c++
class Window : public Entity
{
  	Window(string name, string icon = "defaultIcon.ico") {
      attach<Meta>(name, icon);
  	}
};
```

As you can see it is an entity (```public Entity```) composed of a Meta component (```attach<Meta>```) that holds the name of our Window, and a path to an icon.

Using the Entity Manager (the glue that makes everything work in a magical way) we create a window:

```c++
entityManager->create<Window>("Demo")
```

And thus a Window is born with the name ```Demo```. 

But wait... what happened ?

Well, Fender actually already loaded a system to handle ```Meta Components``` named... ```Meta```.

When the EntityManager creates a ```Window```, it knows its going to be composed of a ```Meta```. It will emit an event ```ComponentAttached<Meta>``` and the ```Meta System``` will catch that event and create an actual Window. (An SFML Window for example).

Now you should keep the return value of the ```create<T>``` function. Say we want to change the name of our window.

```c++
auto &win = entityManager->create<Window>("Demo")
auto &meta = win.get<Meta>();
meta.name = "Awesome";
```

Since ```meta``` 's name is now "Awesome", the ```Meta System``` will now display "Awesome".

What if you want to add a background color to your Window ?

```c++
auto &bg = win.attach<Color>();
bg = Granite;
```

or

```c++
auto &bg = win.attach<Color>(Granite);
```

Now the ```Meta System``` will know the window has a ```Color Component``` and will update the window with a Granite like background.

You want to remove the background ?

```c++
win.detach<Color>();
```

And we're back to a normal window with a black background color;

For now, there is no error checking. By error, I mean what if you attached a component to an entity but it made no sense ? 

```c++
win.attach<onFire>();
```

Well, it will work. But it won't have any impact. If you want to know more about how components affect your program, you can read either the documentation or the source code of the systems. Beware what components you put together though, some combinations might not work as you'd expect, or work at all.

If you want to know more about systems, [follow this link](systems.md)

**Also its recommended you [read this](./fender.md) before going further into details**



## [Entities](./entities.md)

+ [GameObject](./entities/GameObject.md)
  + Transform
  + Outline


+ [Window](./entities/Window.md)
  + Meta
  + Transform
  + Color
+ Camera
  + Transform
  + Camera
+ Grid : GameObject
  + Grid
+ Text : GameObject
  + Text
  + Color
+ Sprite : GameObject
  + Image
  + Color
  + Texture
+ Bar : GameObject
  + Color
  + Text
  + Progressive
  + Texture
+ Button : GameObject
  + Color
  + Image
  + Text
  + Clickable
  + Hoverable
+ TextBox
  + Transform
  + Text
  + Color
  + Scrollable
+ Sound
  + Audio
+ Music
  + Audio
+ Cursor
  + Transform
  + Color
  + Image
  + Effect
+ Popup (with multiple choices)
  + Transform
  + Color
  + Text
+ Container
  + Transform
  + Image
  + Color
  + Content
+ InputField
  + Transform
  + Image
  + Color
  + Text
+ Slider
  + Transform
  + Image
  + Color
  + Clickable

## [Components](./components.md)

+ [Meta](./components/Meta.md)
  + name
  + style
+ Transform
  + position
  + scale
  + rotation
  + isRelative
+ Color
  + color


+ Text
  + content (string)
  + font
  + font-size
  + modifiers (bold, underlined, italic...)
+ Image
  + filepath (string)
  + layer, z-index
+ Progressive
  + min
  + max
  + current
  + callback ?
+ Texture
  + filepath (string)
+ Clickable
  + function
+ Hoverable
  + function
+ Scrollable
  + min
  + max
  + currentScroll
  + autoScroll (bool)
+ Effect
  + ​
+ Audio
  + filepath (string)
  + loop (bool)
  + volume 
+ Content
  + text (string)
  + max
  + possible values (only numbers ? )
  + masked (for passwords)
+ Camera
  + Background (color)
  + Field of view (float)
  + PostProcessing effects (antialiasing, etc...)

## [Systems](./systems.md)

### 
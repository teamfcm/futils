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

Well, it will work. But it won't have any impact. If you want to know more about how components affect your program, you can read either the documentation or the source code of the systems.

If you want to know more about systems, [follow this link](systems.md)



## [Entities](./entities.md)

+ Window
+ Text
+ Sprite
+ Bar
+ Button
+ Stream
+ Sound
+ Music
+ Cursor
+ Popup (and its derived classes)
+ TextBox
+ Container

## [Components](./components.md)

### 

## [Systems](./systems.md)

### 
# ECS

> Disclaimer : This is not actual working code, this is only for helping you understand the ECS.

The ECS is a design pattern used to favor **composition** over inheritance. You create entities, that are composed of components and meaningful output is done through the systems in a regular (systemic) way.

For example, here is a Window :

```
class Window : public Entity
{
  	Window(string name) {
      attach<Meta>(name);
  	}
};
```

As you can see it used an entity (```public Entity```) composed of a Meta component (```attach<Meta>```) that holds the name of our Window. 

Using the Entity Manager (the glue that makes everything work in a magical way) we create a window:

```
entityManager->create<Window>("Demo")
```

And thus a Window is born with the name ```Demo```. 

But wait... what happened ?

Well, Fender actually already loaded a system to handle ```Meta Components``` named... ```Meta```.

When the EntityManager creates a ```Window```, it knows its going to be composed of a ```Meta```. It will emit an event ```ComponentAttached<Meta>``` and the ```Meta System``` will catch that event and create an actual Window. (An SFML Window for example).

## Entities

### List

## Components

### List

## Systems

### List
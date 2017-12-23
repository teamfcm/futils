# Components::Meta 

## Description

A meta component characterizes an entity that is out-of-context, not rendered but rather required for the rendering process. It typically describes Windows. 

If you want to open a window using this component, don't forget to attach a Components::Transform or inherit from [Entities::GameObject](../Entities/GameObject.md)

## Associated systems

fender::systems::Meta

## Attributes

```c++
std::string name;
futils::WStyle style;
futils::Color bgColor;
```
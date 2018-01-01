# Components

Using Fender means understanding Component Based programming.
Basically, if you want to output something you have 3 options:
1. Use an Entity from the fender::entities namespace
2. Assemble your own Entity with fender::components
3. Create your own components and systems (why would you?)

Here you will find the list of built-in components with a short description and their corresponding systems (the list may not include all systems manipulating the component)

## Window (WindowSystem)
> Window indicates the entity is "above" current context.
### Fields
```c++
std::string name;
futils::WStyle style;
futils::Color bgColor;
```
### Methods
**Entities** : Window, ...

## Box (Transform)
> Box indicates the entity is shaped like a box
### Fields
```c++
futils::Vec2<float> pos;
futils::Vec2<float> siz;
```
### Methods
**Entities** : Window, ...
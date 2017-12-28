# Components::Transform

> The Transform component holds the data required move in all directions an object.

```c++
class Transform : public futils::IComponent
{
  	futils::Vec3f position;
  	futils::Vec3f rotation;
  	futils::Vec3f scale;
};
```

The Transform component holds position information. But what does it mean to be in (0, 0) or (1, 0) etc.. ? 

> Insert screenshot of grid

Well, this is explained in the [[Camera]](../systems/Camera.md)


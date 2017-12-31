# Systems::SplashScreen

You want to display the Fender Splashscreen before launching your game ? Thank you !

Here's what it looks like.

```c++
class SplashScreen : futils::ISystem
{
	ISystem &_userSystem;
	Window _win;
	World _world;
	Camera _cam;
	View _view;
	
	enum States
    {
    	Init,
    	Run
    };
    States state{Init};
public:
	SplashScreen(ISystem &userSystem):
		_userSystem(userSystem)
    {

    }
};

void SplashScreen::init()
{
	auto &win = _win.get<components::Window>();
	win.title = "Fender";
	win.style = futils::None;
	win.position.x = 0.33;
	win.position.y = 0.33;
	win.size.x = 0.33;
	win.size.y = 0.33;
	win.visible = true;
  
	auto &world = _world.get<components::World>();
	world.name = "SplashScreen";
	world.unit = 10;
	world.size = Vec3(25, 25, 1);
  
  	auto &cam = _cam.get<components::Camera>();
	cam.followMode = Instant;
	cam.name = "MainCamera";
	cam.target = nullptr;
	auto &camPos = _cam.get<components::Transform>();
	camPos.x = 0;
	camPos.y = 0;
	camPos.z = 1;
  
  	auto &view = _view.get<components::View>();
	view.direction = Directions::TopDown;
  	auto &gui = cam.get<Children>();
	gui.add(_view);
	
	auto &viewPos = _view.get<ChildInfo>();
	viewPos.relPos.x = 10;
	viewPos.relPos.y = 10;
	
	auto &viewSize = _view.get<Transform>();
	viewSize.x = 50;
	viewSize.y = 80;
	
    auto exit = Button("Quit", [this](){
    	this->shouldStop = true;
    });
    
    view.content.emplace_back<Button>("Play", [this](){
    	this->entityManager->addSystem<MyGame>();
    	this->shouldStop = true;
    });
	view.content.push_back(exit);
	state = Run;
}

void SplashScreen::run(float)
{
  switch (state) {
    case Init : return init();
    case Run :
      return ;
  }
}
```


# SFMLRenderer

> The SFMLRenderer is the system you require if you want any graphical output.

# Description

Because Fender favors composition over inheritance, there is no abstraction of rendering. However, you can simply load a different system (yours or any from the fender github) to change the output.
If you do your own system, pay attention to requests and events, as they are the only way systems communicate.
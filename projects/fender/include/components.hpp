//
// Created by arroganz on 11/29/17.
//

#ifndef FENDER_COMPONENTS_HPP
#define FENDER_COMPONENTS_HPP

# include "fender.hpp"

namespace fender::components {
    struct Transform : public futils::IComponent
    {
        int x;
        int y;
        int w;
        int h;
    };
    struct Image : public futils::IComponent
    {
        Image(std::string const &image): asset(image) {}
        std::string asset;
        fender::Color color;
    };
    class Runnable : public futils::IComponent {
        futils::Action _action;
    public:
        Runnable(futils::Action action) : _action(action) {

        }

        void run() {
            _action();
        }
    };
    class Sequenced : public futils::IComponent {
    public:
        Sequenced() = default;
    };
    class Named : public futils::IComponent {
        std::string _name{"UndefinedName"};
    public:
        Named(std::string const &name) : _name(name) {

        }

        std::string const &get() const {
            return _name;
        }

        void rename(std::string const &name) {
            _name = name;
        }
    };
    class Object2d : public futils::IComponent {
    protected:
        futils::Vec2d<float> position;
        futils::Vec2d<float> size;
        Object2d *parent{nullptr};
    public:
        Object2d(futils::Vec2d<float> const &position = {},
                 futils::Vec2d<float> const &size = {}) :
                position(position), size(size) {
            this->__name = "Object2d";
        }

        void setPosition(futils::Vec2d<float> const &pos);

        void setSize(futils::Vec2d<float> const &size);

        void setRPosition(futils::Vec2d<float> const &pos);

        void setRSize(futils::Vec2d<float> const &size);

        futils::Vec2d<float> getPosition() const { return position; }

        futils::Vec2d<float> getSize() const { return size; }

        void move(float x, float y) {
            this->position.X += x;
            this->position.Y += y;
        }
    };
    class Object3d : public futils::IComponent {
    protected:
        futils::Vec3d<float> position;
        futils::Vec3d<float> size;
        Object3d *parent{nullptr};
    public:
        Object3d(futils::Vec3d<float> const &position = {},
                 futils::Vec3d<float> const &size = {}) :
                position(position), size(size) {
            this->__name = "Object3d";
        }

        void setPosition(futils::Vec3d<float> const &pos) { this->position = pos; }

        void setSize(futils::Vec3d<float> const &size) { this->size = size; }

        futils::Vec3d<float> getPosition() const { return position; }

        futils::Vec3d<float> getSize() const { return size; }
    };
    class Drawable : public futils::IComponent {
        fender::Color color{fender::Color::WHITE};
    public:
        Drawable() {
            this->__name = "Drawable";
        }

        void setColor(fender::Color c) { this->color = c; }

        fender::Color getColor() const { return this->color; }
    };
    class Clickable : public futils::IComponent {
        futils::Rect<float> area;
        std::function<void(void)> function;
    public:
        Clickable() {
            this->__name = "Clickable";
        }

        void setArea(float x, float y, float w, float h) {
            this->area.X = x;
            this->area.Y = y;
            this->area.EndX = x + w;
            this->area.EndY = y + h;
        }

        void setArea(futils::Vec2d<float> const &pos,
                     futils::Vec2d<float> const &size) {
            this->area = futils::Rect<float>(pos, size);
        }

        void setArea(futils::Rect<float> const &ref) { this->area = ref; }

        void setAction(std::function<void(void)> func) {
            this->function = func;
        }

        futils::Rect<float> const &getRect() const { return this->area; }

        void operator()() {
            return this->function();
        }
    };
    class Hoverable : public futils::IComponent {
        futils::Rect<float> area;
    public:
        std::function<void(void)> onHover{[]() {}};
        std::function<void(void)> onLeave{[]() {}};

        Hoverable() {
            this->__name = "Hoverable";
        }

        void setArea(float x, float y, float w, float h) {
            this->area.X = x;
            this->area.Y = y;
            this->area.EndX = x + w;
            this->area.EndY = y + h;
        }

        void setArea(futils::Vec2d<float> const &pos,
                     futils::Vec2d<float> const &size) {
            this->area = futils::Rect<float>(pos, size);
        }

        void setArea(futils::Rect<float> const &ref) { this->area = ref; }

        futils::Rect<float> const &getRect() const { return this->area; }
    };
	/*
    class Ini : public futils::IComponent {
        std::string file{""};
        std::string scope{""};
        std::string identifier{"id:_" + file + "-" + scope};
        bool isNew{true};
        bool hasChanged{false};
        futils::Ini source{file};
    public:
        Ini(std::string const &file, std::string const &scope) : file(file), scope(scope) {
            this->__name = "Ini";
        }

        std::string const &getIdentifier() const {
            return this->identifier;
        }

        bool shouldSave() {
            return this->source.hasChanged();
        }

        bool isLoaded() {
            return !this->isNew;
        }

        futils::INI::Token &operator[](std::string const &name) {
            this->hasChanged = true;
            return source[this->scope][name];
        }

        void save() {
            source.save();
            this->hasChanged = false;
        }
    };
	*/
    //class draggable : public futils::icomponent {
    //    bool followingmouse{false};
    //public:
    //    draggable() { this->__name = "draggable"; }

    //    bool isdragged() const { return this->followingmouse; }
    //};
    //class animated : public futils::icomponent {
    //public:
    //    animated() { this->__name = "animated"; }

    //    std::function<void(float)> callback{[](float) {}};
    //    std::function<bool(void)> isdone{[]() { return true; }};
    //};
}

#endif //FENDER_COMPONENTS_HPP

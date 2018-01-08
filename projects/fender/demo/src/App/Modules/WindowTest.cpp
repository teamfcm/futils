//
// Created by arroganz on 1/1/18.
//

#include "WindowTest.hpp"
#include "Components/Color.hpp"
#include "Components/World.hpp"
#include "inputKeys.hpp"

void WindowTest::initWindow()
{
    addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
        auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
        if (key == futils::Keys::F)
        {
            auto worlds = entityManager->get<fender::components::World>();
            if (worlds.empty())
                return ;
            auto &world = worlds.front();
            world->unit *= 2;
        }
        else if (key == futils::Keys::G)
        {
            auto worlds = entityManager->get<fender::components::World>();
            if (worlds.empty())
                return ;
            auto &world = worlds.front();
            world->unit /= 2;
        }
        else if (key == futils::Keys::D)
        {
            auto cameras = entityManager->get<fender::components::Camera>();
            for (auto &cam: cameras)
            {
                cam->debugMode = !cam->debugMode;
            }
        }
    });
    window = &entityManager->create<fender::entities::Window>();
    auto &win = window->get<fender::components::Window>();
    if (win.isOpen)
    {

    } else {
        win.size.w = 1024;
        win.size.h = 780;
        win.position.x = 0;
        win.position.y = 0;
        win.visible = true;
        win.style = futils::WStyle::None;
        auto &world = window->attach<fender::components::World>();
        world.unit = 64;
        world.name = "Project Elixia";
        win.title = world.name;
        world.size = fender::vec3f(100, 100, 100);
        auto &color = window->attach<fender::components::Color>();

        color.color = futils::Granite;
//        addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
//           auto &key =  futils::Mediator::rebuild<futils::Keys>(pkg);
//            if (key == futils::Keys::Escape || key == futils::Keys::K)
//                events->send<fender::events::Shutdown>();
//        });
        addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
            entityManager->removeSystem(name);
        });

        camera = &entityManager->create<fender::entities::Camera>();
        auto &cam = camera->get<fender::components::Camera>();
        cam.window = window;
        cam.activated = true;
        cam.debugMode = true;
    }
}


void testGO(futils::EntityManager &em, int x, int y, int w, int h, int z)
{
    auto &go = em.create<fender::entities::GameObject>();
    auto &border = go.get<fender::components::Border>();
    border.color = futils::Violetred;
    auto &pos = go.get<fender::components::Transform>();
    pos.position.x = x;
    pos.position.y = y;
    pos.position.z = z;
    pos.size.w = w;
    pos.size.h = h;
}

void createGo(futils::EntityManager &em)
{
    futils::IntegralRange<int> rng(-50, 50);
    futils::IntegralRange<int> zrng(0, 10);
    testGO(em, rng.getRandom(), rng.getRandom(), 2 + zrng.getRandom() % 3, 1 + zrng.getRandom() % 3, zrng.getRandom());
}


void WindowTest::initInputs()
{
    input = &entityManager->create<fender::entities::Input>();
    auto &component = input->get<fender::components::Input>();
    component.name = "WindowTest";
    component.activated = true;
    futils::InputSequence escape;
    futils::InputAction action(futils::Keys::Escape, futils::InputState::Down);
    escape.actions.push_back(action);

    futils::InputSequence generate;
    futils::InputAction gen_action(futils::Keys::Space, futils::InputState::Down);
    generate.actions.push_back(gen_action);
    component.map[escape] = [this](){
        events->send<fender::events::Shutdown>();
    };
    component.map[generate] = [this](){
        createGo(*entityManager);
    };
}
void WindowTest::run(float) {
    if (window == nullptr) {
        initWindow();
        initInputs();
    } else
    {
        static int i = 0;
        if (i == 0)
        {
            while (i < 10) {
                i++;
                createGo(*entityManager);
            }
        }
    }
}
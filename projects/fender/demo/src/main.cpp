#include "App.hpp"

int main(int argc, char *argv[])
{
	try {
		demo::App app(argc, argv);

		if (app.start() != 0)
			return -1;
		return app.run();
	} catch (std::exception const &e) {
		LOUT(e.what());
	}
}

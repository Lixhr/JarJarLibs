#include "jjl.hpp"
#include "JarJarLibs.hpp"


int	main(int argc, char **argv) {
	try {
		string file = get_args(argc, argv);
		std::cout << "TODO PARSING ARGS\n";
		JarJarLibs jjl(file);
	}
	catch (const exception &e) {
		cerr << "Error: " << e.what() << endl;
	}
}
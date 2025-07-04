#include "jjl.hpp"
#include "JarJarLibs.hpp"
#include "ArgsParser.hpp"



int	main(int argc, char **argv) {
	try {
		ArgsParser args(argc, argv);
		JarJarLibs jjl(args);
	}
	catch (const exception &e) {
		cerr << "Error: " << e.what() << endl;
	}
}
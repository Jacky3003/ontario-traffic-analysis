#include "cliargs.h"

CliArgs::CliArgs(int argcnt, char **argval){
    for(int i = 1; i < argcnt; i++){
        std::string arg = argval[i];
        if (arg == "-h") {
            help_msg(argval[0]);
            exit(0);
        }
        else if (arg == "-f") {
            i++;
            filepath = argval[i];
        }
        else if (arg == "-io"){
            enable_write = true;
        }
        else{
            std::cerr << "Invalid command line argument" << std::endl;
            help_msg(argval[0]);
            exit(-1);
        }

    }
}

void help_msg(char *progname){
    std::cerr << "Usage: " << progname << " -f data/<path-to-file>.data -t <num-threads>"
              << "Options:\n"
              << "\t-h\t\tShow this help message\n"
              << "\t-f <path-to-file> \tSpecify the .data file path\n"
              << "\t-io <num-threads> \tEnable writing to I/O, disabled by default"
              << std::endl;
}
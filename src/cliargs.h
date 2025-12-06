/**
 * Module for setting command line arguments for the project.
 */

#include <string>
#include <iostream>


 class CliArgs {
    public:
        int argcount;
        int road_len = 100000;
        std::string filepath = "";
        bool enable_write = false;

        /// @brief argument parser for command line arguments
        /// @param argcnt   amount of arguments to parse
        /// @param argval   values given in parameters
        CliArgs(int argcnt, char **argval);
};

/// @brief prints help message for the user
/// @param progname     name of the program used
void help_msg(char *progname);
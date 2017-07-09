
//#include "streaker.hh"

#include <cstdio>
#include <string>
#include <iostream>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main( int argc, const char* argv[] ) {

//
//    std::string directory( fs::current_path().string() );
//
//    std::string sequenceName;
//
//    po::options_description description("Streaker usage");
//
//    description.add_options()
//            ("help,h", "Display this help message")
//            ("sequence", po::value< std::string >( &sequenceName )->required(), "Sequence file name(s)" );
//
//    po::positional_options_description positionalOptions;
//    positionalOptions.add("sequence", -1);
//
//    po::variables_map vm;
//    try {
//        po::store( po::command_line_parser( argc, argv )
//                           .options( description )
//                           .positional( positionalOptions )
//                           .run(), vm );
//        po::notify(vm);
//    } catch(boost::program_options::required_option& e) {
//        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
//        return 1;
//    } catch(boost::program_options::error& e) {
//        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
//        return 1;
//    }
//
//    fs::path fullpath( sequenceName );
//
//    try {
//        if ( !fullpath.is_absolute() ) {
//            fullpath = ( fs::current_path() / fullpath );
//        }
//    } catch ( ... ) {
//        std::cerr << "Bad file." << std::endl;
//        return 1;
//    }
//
//    // Check directory exists
//    if ( !fs::exists( fullpath.parent_path() ) ) {
//        std::cerr << "Directory does not exist: " << fullpath.parent_path() << std::endl;
//        return 1;
//    }
//
//    // Update file
//    fullpath = fs::canonical( fullpath.parent_path() ) / fullpath.filename();
//
//    const SequenceFile sequence( fullpath.filename().string() );
//    Streaker streaker( fullpath.parent_path().string() );
//    Streak streak = streaker.find( sequence );
//    if ( streak ) {
//        print( streak );
//    } else {
//        std::cerr << "No streaks found: " << fullpath.string() << std::endl;
//    }

    return 0;
}
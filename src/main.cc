#include <cstdio>
#include <iostream>
#include "streaker.hh"

#include <boost/program_options.hpp>
#include <string>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main( int argc, const char* argv[] ) {

    std::string directory( fs::current_path().string() );

    Streaks streaks = findStreaks( directory );
    for ( const Streak& streak : streaks ) {
        print( streak );
    }

//    std::vector< std::string > sequenceNames;
//
//    po::options_description description("Streaker usage");
//
//    description.add_options()
//            ("help,h", "Display this help message")
//            ("sequence", po::value< std::vector< std::string > >( &sequenceNames )->required(), "Sequence file name(s)" );
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
//    std::map< std::string, std::vector< std::string > > SequenceNameMap;
//    const std::vector< std::string > sequenceFilenames = vm[ "sequence" ].as< std::vector< std::string > >();
//    for ( const std::string& sequenceFilename : sequenceFilenames ) {
//
//        fs::path fullpath( sequenceFilename );
//        try {
//            if ( !fullpath.is_absolute() ) {
//                fullpath = ( fs::current_path() / fullpath );
//            }
//        } catch ( ... ) {
//            std::cerr << "Bad path." << std::endl;
//            continue;
//        }
//
//        // Check directory exists
//        if ( !fs::exists( fullpath.parent_path() ) ) {
//            std::cerr << "Directory does not exist: " << fullpath.parent_path() << std::endl;
//            continue;
//        }
//
//        // Update path
//        fullpath = fs::canonical( fullpath.parent_path() ) / fullpath.filename();
//
//        const SequenceFile sequence( fullpath.filename().string() );
//        Streak streak = findStreak( fullpath.parent_path().string(), sequence );
//        if ( streak ) {
//            print( streak );
//        } else {
//            std::cerr << "No streaks found: " << fullpath.string() << std::endl;
//        }
//    }

    return 0;


//    const std::string test = "/Users/eddiehoyle/Code/cpp/streaker/resources/test.@@@.txt";
//    const SequenceFile sequence( test );
//    Streak streak = findStreak( sequence );
//    print( streak );

}
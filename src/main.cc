#include <cstdio>
#include <iostream>
#include "streaker.hh"

#include <boost/program_options.hpp>
#include <string>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main( int argc, const char* argv[] ) {

    std::string sequenceName;

    po::options_description description("Streaker usage");

    description.add_options()
            ("help,h", "Display this help message")
            ("sequence", po::value< std::string >( &sequenceName )->required(), "Sequence file name" );

    po::positional_options_description positionalOptions;
    positionalOptions.add("sequence", 1);

    po::variables_map vm;


    try {

        po::store( po::command_line_parser( argc, argv )
                           .options( description )
                           .positional( positionalOptions )
                           .run(), vm );
        po::notify(vm);


    } catch(boost::program_options::required_option& e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        return 1;
    } catch(boost::program_options::error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        return 1;
    }

//    std::cerr << "sequence: " << vm[ "sequence" ].as<std::string>() << std::endl;
    fs::path sequenceDirectory( fs::current_path() );
    fs::path sequenceFilename( vm[ "sequence"].as<std::string>() );
    fs::path canonicalDirectory = fs::canonical( ( sequenceDirectory / sequenceFilename ).parent_path() );
    fs::path canonicalFilename = sequenceFilename.filename();
    fs::path scan = canonicalDirectory / canonicalFilename;
    std::cerr << scan.string() << std::endl;

//    const SequencePath sequence( scan.string() );
//    Streak streak = findStreak( sequence );
//    if ( streak ) {
//        print( streak );
//    } else {
//        std::cerr << "No streaks found: " << sequenceFilename.string() << std::endl;
//    }






//    const std::string test = "/Users/eddiehoyle/Code/cpp/streaker/resources/test.@@@.txt";
//    const SequencePath sequence( test );
//    Streak streak = findStreak( sequence );
//    print( streak );


    return 0;
}
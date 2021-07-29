#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/section/33.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using RectangularMatrix = section::Type< 33 >::RectangularMatrix;

std::string chunk();
std::string invalidLB();
std::string inconsistentEnergies();
void verifyChunk( const RectangularMatrix& );


SCENARIO( "RectangularMatrix" ) {

  GIVEN( "valid data for a RectangularMatrix" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > rowEnergies = { 1.1, 1.2, 1.3 };
      std::vector< double > columnEnergies = { 2.1, 2.2, 2.3, 2.4 };
      std::vector< double > values = { 1, 2, 3, 4, 5, 6 };

      RectangularMatrix chunk( std::move(rowEnergies),
                               std::move(columnEnergies),
                               std::move(values) );

      THEN( "a RectangularMatrix can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 33, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      RectangularMatrix chunk( begin, end, lineNumber, 9228, 33, 5 );

      THEN( "a RectangularMatrix object can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 33, 5 );
        CHECK( buffer == string );
      } // THEN
    } // WHEN

  } // GIVEN

  GIVEN( "invalid data for a RectangularMatrix" ) {

    WHEN( "a string representation is used with an invalid LB" ) {

      std::string string = invalidLB();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          RectangularMatrix( begin, end, lineNumber, 9228, 33, 5 ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation is used with inconsistent NER and NT" ) {

      std::string string = inconsistentEnergies();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS(
          RectangularMatrix( begin, end, lineNumber, 9228, 33, 5 ) );
      } // THEN
    } // WHEN
  } // GIVEN

} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 0.000000+0          0          6         13          3922833  5     \n"
    " 1.100000+0 1.200000+0 1.300000+0 2.100000+0 2.200000+0 2.300000+0922833  5     \n"
    " 2.400000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0922833  5     \n"
    " 6.000000+0                                                       922833  5     \n";
}

void verifyChunk( const RectangularMatrix& chunk ) {

  // metadata
  CHECK( 6 == chunk.LB() );
  CHECK( 6 == chunk.procedure() );
  CHECK( 3 == chunk.NER() );
  CHECK( 3 == chunk.numberRowEnergies() );
  CHECK( 4 == chunk.NEC() );
  CHECK( 4 == chunk.numberColumnEnergies() );
  CHECK( 13 == chunk.NT() );
  CHECK( 13 == chunk.numberValues() );

  // values
  CHECK( 1.1 == Approx( chunk.rowEnergies()[0] ) );
  CHECK( 1.2 == Approx( chunk.rowEnergies()[1] ) );
  CHECK( 1.3 == Approx( chunk.rowEnergies()[2] ) );
  CHECK( 2.1 == Approx( chunk.columnEnergies()[0] ) );
  CHECK( 2.2 == Approx( chunk.columnEnergies()[1] ) );
  CHECK( 2.3 == Approx( chunk.columnEnergies()[2] ) );
  CHECK( 2.4 == Approx( chunk.columnEnergies()[3] ) );
  CHECK( 1.0 == Approx( chunk.values()[0] ) );
  CHECK( 2.0 == Approx( chunk.values()[1] ) );
  CHECK( 3.0 == Approx( chunk.values()[2] ) );
  CHECK( 4.0 == Approx( chunk.values()[3] ) );
  CHECK( 5.0 == Approx( chunk.values()[4] ) );
  CHECK( 6.0 == Approx( chunk.values()[5] ) );

  CHECK( 4 == chunk.NC() );

}


std::string invalidLB() {
  return
    " 0.000000+0 0.000000+0          0          5         13          3922833  5     \n"
    " 1.100000+0 1.200000+0 1.300000+0 2.100000+0 2.200000+0 2.300000+0922833  5     \n"
    " 2.400000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0922833  5     \n"
    " 6.000000+0                                                       922833  5     \n";
}

std::string inconsistentEnergies() {
  return
    " 0.000000+0 0.000000+0          0          6         14          3922833  5     \n"
    " 1.100000+0 1.200000+0 1.300000+0 2.100000+0 2.200000+0 2.300000+0922833  5     \n"
    " 2.400000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0922833  5     \n"
    " 6.000000+0 7.000000+0                                            922833  5     \n";
}

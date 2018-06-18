#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

std::string chunk();
std::string invalidLANG();

SCENARIO( "section::Type< 6 >::ReactionProduct" ) {

  GIVEN( "valid data for a "
         "section::Type< 6 >::ReactionProduct" ) {

    int zaid = 92235;
    double awr = 2.330248e+2;
    int jp = 0;
    int lct = 2;
    int mt = 5;
    std::vector< section::Type< 6 >::ReactionProduct > products = {
      section::Type< 6 >::ReactionProduct(
        // multiplicity
        { 1001., 0.9986234, 0, 1, { 4 }, { 2 },
          { 1e-5, 1.1e+7, 1.147e+7, 2e+7 },
          { 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 } },
        // distribution
        { section::Type< 6 >::ContinuumEnergyAngle(
            1, 2, { 2 }, { 1 },
            { section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
                section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
                  1e-5, 0, 1, 4,
                  { 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12. } ) ),
              section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
                section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
                  2e+7, 0, 1, 2, {1., 2., 3., 4., 5., 6.} ) ) } ) } ),
      section::Type< 6 >::ReactionProduct( 
        // multiplicity
        { 1., 1., 0, 1, { 2 }, { 2 },
          { 1.858639e+7, 2.e+7 },
          { 4., 4. } },
        // distribution
        { section::Type< 6 >::ContinuumEnergyAngle(
          1, 2, { 2 }, { 22 },
        { section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              1.858639e+7, 0, 1, 2, { 0., 0., .5, 2., 1., 0. } ) ),
          section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              2e+7, 0, 1, 2, { 0., 0., .5, 2., 1., 0. } ) ) } ) } ),
      section::Type< 6 >::ReactionProduct( 
        // multiplicity
        { 0., 0., 0, 1, { 3 }, { 2 },
          { 1.858639e+7, 1.9e+7, 2.e+7 },
          { 1., 2., 3. } },
        // distribution
        { section::Type< 6 >::ContinuumEnergyAngle(
          1, 2, { 2 }, { 5 },
        { section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              1.858639e+7, 0, 1, 2, { 0., 1., 0., 2., 0., .5 } ) ),
          section::Type< 6 >::ContinuumEnergyAngle::SubSectionVariant(
            section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients(
              2e+7, 0, 1, 2, { 0., 1., 0., 2., 0., .5 } ) ) } ) } ) };

    THEN( "a section::Type< 6 >::ReactionProduct can "
          "be constructed and members can be tested" ) {
      section::Type< 6 > chunk( mt, zaid, awr, jp, lct, std::move( products ) );

      REQUIRE( 92235. == Approx( chunk.ZA() ) );
      REQUIRE( 2.330248e+2 == Approx( chunk.AWR() ) );
      REQUIRE( 0 == chunk.JP() );
      REQUIRE( 2 == chunk.LCT() );
      REQUIRE( 3 == chunk.NK() );
      REQUIRE( 5 == chunk.MT() );

      auto products = chunk.products();
      REQUIRE( 3 == products.size() );

      // product 1
      REQUIRE( 1001. == Approx( products[0].ZAP() ) );
      REQUIRE( 0.9986234 == Approx( products[0].AWP() ) );
      REQUIRE( 0 == products[0].LIP() );
      REQUIRE( 1 == products[0].LAW() );

      REQUIRE( 1001. == Approx( products[0].multiplicity().ZAP() ) );
      REQUIRE( 0.9986234 == Approx( products[0].multiplicity().AWP() ) );
      REQUIRE( 0 == products[0].multiplicity().LIP() );
      REQUIRE( 1 == products[0].multiplicity().LAW() );

      REQUIRE( 4 == products[0].multiplicity().NP() );
      REQUIRE( 1 == products[0].multiplicity().NR() );
      REQUIRE( 1 == products[0].multiplicity().interpolants().size() );
      REQUIRE( 1 == products[0].multiplicity().boundaries().size() );
      REQUIRE( 2 == products[0].multiplicity().interpolants()[0] );
      REQUIRE( 4 == products[0].multiplicity().boundaries()[0] );
      REQUIRE( 4 == products[0].multiplicity().energies().size() );
      REQUIRE( 4 == products[0].multiplicity().multiplicities().size() );
      REQUIRE( 1e-5 == Approx( products[0].multiplicity().energies()[0] ) );
      REQUIRE( 1.1e+7 == Approx( products[0].multiplicity().energies()[1] ) );
      REQUIRE( 1.147e+7 == Approx( products[0].multiplicity().energies()[2] ) );
      REQUIRE( 2e+7 == Approx( products[0].multiplicity().energies()[3] ) );
      REQUIRE( 0. == Approx( products[0].multiplicity().multiplicities()[0] ) );
      REQUIRE( 8.45368e-11 == Approx( products[0].multiplicity().multiplicities()[1] ) );
      REQUIRE( 6.622950e-8 == Approx( products[0].multiplicity().multiplicities()[2] ) );
      REQUIRE( 2.149790e-1 == Approx( products[0].multiplicity().multiplicities()[3] ) );

      auto law = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle >( products[0].distribution() );

      REQUIRE( 1 == law.LAW() );
      REQUIRE( 2 == law.LEP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 1 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      auto energies = law.energies();

      REQUIRE( 1e-5 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 1 == energies[0].NA() );
      REQUIRE( 12 == energies[0].NW() );
      REQUIRE( 4 == energies[0].NEP() );

      auto subsection1 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[0] );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 1 == subsection1.NA() );
      REQUIRE( 12 == subsection1.NW() );
      REQUIRE( 4 == subsection1.NEP() );
      REQUIRE( 4 == subsection1.energies().size() );
      REQUIRE( 1. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 7. == Approx( subsection1.energies()[2] ) );
      REQUIRE( 10. == Approx( subsection1.energies()[3] ) );
      REQUIRE( 4 == subsection1.coefficients().size() );
      REQUIRE( 2. == Approx( subsection1.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection1.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection1.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection1.coefficients()[1][1] ) );
      REQUIRE( 8. == Approx( subsection1.coefficients()[2][0] ) );
      REQUIRE( 9. == Approx( subsection1.coefficients()[2][1] ) );
      REQUIRE( 11. == Approx( subsection1.coefficients()[3][0] ) );
      REQUIRE( 12. == Approx( subsection1.coefficients()[3][1] ) );
      REQUIRE( 4 == Approx( subsection1.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection1.totalEmissionProbabilities()[1] ) );
      REQUIRE( 8. == Approx( subsection1.totalEmissionProbabilities()[2] ) );
      REQUIRE( 11. == Approx( subsection1.totalEmissionProbabilities()[3] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 1 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 1 == energies[1].NA() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );

      auto subsection2 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[1] );
      REQUIRE( 1 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 1 == subsection2.NA() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 1. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 4. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.coefficients().size() );
      REQUIRE( 2. == Approx( subsection2.coefficients()[0][0] ) );
      REQUIRE( 3. == Approx( subsection2.coefficients()[0][1] ) );
      REQUIRE( 5. == Approx( subsection2.coefficients()[1][0] ) );
      REQUIRE( 6. == Approx( subsection2.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
      REQUIRE( 2. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 5. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

      // product 2
      REQUIRE( 1. == Approx( products[1].ZAP() ) );
      REQUIRE( 1. == Approx( products[1].AWP() ) );
      REQUIRE( 0 == products[1].LIP() );
      REQUIRE( 1 == products[1].LAW() );

      REQUIRE( 1. == Approx( products[1].multiplicity().ZAP() ) );
      REQUIRE( 1. == Approx( products[1].multiplicity().AWP() ) );
      REQUIRE( 0 == products[1].multiplicity().LIP() );
      REQUIRE( 1 == products[1].multiplicity().LAW() );

      REQUIRE( 2 == products[1].multiplicity().NP() );
      REQUIRE( 1 == products[1].multiplicity().NR() );
      REQUIRE( 1 == products[1].multiplicity().interpolants().size() );
      REQUIRE( 1 == products[1].multiplicity().boundaries().size() );
      REQUIRE( 2 == products[1].multiplicity().interpolants()[0] );
      REQUIRE( 2 == products[1].multiplicity().boundaries()[0] );
      REQUIRE( 2 == products[1].multiplicity().energies().size() );
      REQUIRE( 2 == products[1].multiplicity().multiplicities().size() );
      REQUIRE( 1.858639e+7 == Approx( products[1].multiplicity().energies()[0] ) );
      REQUIRE( 2e+7 == Approx( products[1].multiplicity().energies()[1] ) );
      REQUIRE( 4. == Approx( products[1].multiplicity().multiplicities()[0] ) );
      REQUIRE( 4. == Approx( products[1].multiplicity().multiplicities()[1] ) );

      law = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle >( products[1].distribution() );

      REQUIRE( 1 == law.LAW() );
      REQUIRE( 2 == law.LEP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 22 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      energies = law.energies();

      REQUIRE( 1.858639e+7 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 1 == energies[0].NA() );
      REQUIRE( 6 == energies[0].NW() );
      REQUIRE( 2 == energies[0].NEP() );

      subsection1 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[0] );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 1 == subsection1.NA() );
      REQUIRE( 6 == subsection1.NW() );
      REQUIRE( 2 == subsection1.NEP() );
      REQUIRE( 2 == subsection1.energies().size() );
      REQUIRE( 0. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 2. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 2 == subsection1.coefficients().size() );
      REQUIRE( 0. == Approx( subsection1.coefficients()[0][0] ) );
      REQUIRE( .5 == Approx( subsection1.coefficients()[0][1] ) );
      REQUIRE( 1. == Approx( subsection1.coefficients()[1][0] ) );
      REQUIRE( 0. == Approx( subsection1.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection1.totalEmissionProbabilities().size() ) );
      REQUIRE( 0. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 1. == Approx( subsection1.totalEmissionProbabilities()[1] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 1 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 1 == energies[1].NA() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );

      subsection2 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[1] );
      REQUIRE( 1 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 1 == subsection2.NA() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 0. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 2. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.coefficients().size() );
      REQUIRE( 0. == Approx( subsection2.coefficients()[0][0] ) );
      REQUIRE( .5 == Approx( subsection2.coefficients()[0][1] ) );
      REQUIRE( 1. == Approx( subsection2.coefficients()[1][0] ) );
      REQUIRE( 0. == Approx( subsection2.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
      REQUIRE( 0. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 1. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

      // product 3
      REQUIRE( 0. == Approx( products[2].ZAP() ) );
      REQUIRE( 0. == Approx( products[2].AWP() ) );
      REQUIRE( 0 == products[2].LIP() );
      REQUIRE( 1 == products[2].LAW() );

      REQUIRE( 0. == Approx( products[2].multiplicity().ZAP() ) );
      REQUIRE( 0. == Approx( products[2].multiplicity().AWP() ) );
      REQUIRE( 0 == products[2].multiplicity().LIP() );
      REQUIRE( 1 == products[2].multiplicity().LAW() );

      REQUIRE( 3 == products[2].multiplicity().NP() );
      REQUIRE( 1 == products[2].multiplicity().NR() );
      REQUIRE( 1 == products[2].multiplicity().interpolants().size() );
      REQUIRE( 1 == products[2].multiplicity().boundaries().size() );
      REQUIRE( 2 == products[2].multiplicity().interpolants()[0] );
      REQUIRE( 3 == products[2].multiplicity().boundaries()[0] );
      REQUIRE( 3 == products[2].multiplicity().energies().size() );
      REQUIRE( 3 == products[2].multiplicity().multiplicities().size() );
      REQUIRE( 1.858639e+7 == Approx( products[2].multiplicity().energies()[0] ) );
      REQUIRE( 1.9e+7 == Approx( products[2].multiplicity().energies()[1] ) );
      REQUIRE( 2e+7 == Approx( products[2].multiplicity().energies()[2] ) );
      REQUIRE( 1. == Approx( products[2].multiplicity().multiplicities()[0] ) );
      REQUIRE( 2. == Approx( products[2].multiplicity().multiplicities()[1] ) );
      REQUIRE( 3. == Approx( products[2].multiplicity().multiplicities()[2] ) );

      law = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle >( products[2].distribution() );

      REQUIRE( 1 == law.LAW() );
      REQUIRE( 2 == law.LEP() );
      REQUIRE( 2 == law.NE() );
      REQUIRE( 1 == law.NR() );
      REQUIRE( 1 == law.interpolants().size() );
      REQUIRE( 1 == law.boundaries().size() );
      REQUIRE( 5 == law.interpolants()[0] );
      REQUIRE( 2 == law.boundaries()[0] );

      energies = law.energies();

      REQUIRE( 1.858639e+7 == Approx( energies[0].energy() ) );
      REQUIRE( 1 == energies[0].LANG() );
      REQUIRE( 0 == energies[0].ND() );
      REQUIRE( 1 == energies[0].NA() );
      REQUIRE( 6 == energies[0].NW() );
      REQUIRE( 2 == energies[0].NEP() );

      subsection1 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[0] );
      REQUIRE( 0 == subsection1.ND() );
      REQUIRE( 1 == subsection1.NA() );
      REQUIRE( 6 == subsection1.NW() );
      REQUIRE( 2 == subsection1.NEP() );
      REQUIRE( 2 == subsection1.energies().size() );
      REQUIRE( 0. == Approx( subsection1.energies()[0] ) );
      REQUIRE( 2. == Approx( subsection1.energies()[1] ) );
      REQUIRE( 2 == subsection1.coefficients().size() );
      REQUIRE( 1. == Approx( subsection1.coefficients()[0][0] ) );
      REQUIRE( 0. == Approx( subsection1.coefficients()[0][1] ) );
      REQUIRE( 0. == Approx( subsection1.coefficients()[1][0] ) );
      REQUIRE( .5 == Approx( subsection1.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection1.totalEmissionProbabilities().size() ) );
      REQUIRE( 1. == Approx( subsection1.totalEmissionProbabilities()[0] ) );
      REQUIRE( 0. == Approx( subsection1.totalEmissionProbabilities()[1] ) );

      REQUIRE( 2e+7 == Approx( energies[1].energy() ) );
      REQUIRE( 1 == energies[1].LANG() );
      REQUIRE( 0 == energies[1].ND() );
      REQUIRE( 1 == energies[1].NA() );
      REQUIRE( 6 == energies[1].NW() );
      REQUIRE( 2 == energies[1].NEP() );

      subsection2 = std::experimental::get< section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients >( energies[1] );
      REQUIRE( 1 == subsection2.LANG() );
      REQUIRE( 0 == subsection2.ND() );
      REQUIRE( 1 == subsection2.NA() );
      REQUIRE( 6 == subsection2.NW() );
      REQUIRE( 2 == subsection2.NEP() );
      REQUIRE( 2 == subsection2.energies().size() );
      REQUIRE( 0. == Approx( subsection2.energies()[0] ) );
      REQUIRE( 2. == Approx( subsection2.energies()[1] ) );
      REQUIRE( 2 == subsection2.coefficients().size() );
      REQUIRE( 1. == Approx( subsection2.coefficients()[0][0] ) );
      REQUIRE( 0. == Approx( subsection2.coefficients()[0][1] ) );
      REQUIRE( 0. == Approx( subsection2.coefficients()[1][0] ) );
      REQUIRE( .5 == Approx( subsection2.coefficients()[1][1] ) );
      REQUIRE( 2 == Approx( subsection2.totalEmissionProbabilities().size() ) );
      REQUIRE( 1. == Approx( subsection2.totalEmissionProbabilities()[0] ) );
      REQUIRE( 0. == Approx( subsection2.totalEmissionProbabilities()[1] ) );

      REQUIRE( 30 == chunk.NC() );
    }
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 9.223500+4 2.330248+2         11          1         61          09228 6  5     \n"
    " 1.001000+3 9.986234-1          0          1          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 1.000000+0 1.000000+0          0          1          1          29437 6  5     \n"
    "          2          2                                            9437 6  5     \n"
    " 1.858639+7 4.000000+0 2.000000+7 4.000000+0                      9437 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29437 6  5     \n"
    "          2         22                                            9437 6  5     \n"
    " 0.000000+0 1.858639+7          0          0          6          39437 6  5     \n"
    " 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09437 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          6          39437 6  5     \n"
    " 0.000000+0 0.000000+0 5.000000-1 2.000000+0 1.000000+0 0.000000+09437 6  5     \n"
    " 0.000000+0 0.000000+0          0          1          1          39437 6  5     \n"
    "          3          2                                            9437 6  5     \n"
    " 1.858639+7 1.000000+0 1.900000+7 2.000000+0 2.000000+7 3.000000+09437 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29437 6  5     \n"
    "          2          5                                            9437 6  5     \n"
    " 0.000000+0 1.858639+7          0          0          6          39437 6  5     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 5.000000-19437 6  5     \n"
    " 0.000000+0 2.000000+7          0          0          6          39437 6  5     \n"
    " 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0 5.000000-19437 6  5     \n"
    "                                                                  9437 6  0     \n";
}

std::string invalidLANG() {
  return
    " 1.001000+3 9.986234-1          0          8          1          49228 6  5     \n"
    "          4          2                                            9228 6  5     \n"
    " 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n"
    " 2.000000+7 2.149790-1                                            9228 6  5     \n"
    " 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n"
    "          2          1                                            9228 6  5     \n"
    " 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n"
    " 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n"
    " 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n"
    " 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n";
}

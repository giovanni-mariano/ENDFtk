// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section/1/452.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSection_1_452( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 1, 452 >;
  using Multiplicity = njoy::ENDFtk::section::Type< 1, 452 >::Multiplicity;

  // wrap views created by this section

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT452",
    "MF452 - the total number of fission neutrons"
  );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF1 MT452 section - the total number of fission neutrons"
  );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr, Multiplicity multiplicity )
                     { return Section( zaid, awr,
                                       std::move( multiplicity ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "multiplicity" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self            the section\n"
    "    zaid            the ZA value of the material\n"
    "    multiplicity    the multiplicity data"
  )
  .def_property_readonly(

    "LNU",
    &Section::LNU,
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "representation",
    &Section::representation,
    "The fission multiplicity representation type"
  )
  .def_property_readonly(

    "nubar",
    &Section::nubar,
    "The fission multiplicity data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}

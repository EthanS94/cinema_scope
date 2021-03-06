## Documentation for CinemaScope 

CinemaScope is a cross-platform application for viewing Cinema databases. It is currently built and tested for Linux, OSX and Windows.

<img src="img/cinema_scope.png" width="800" border="1">

### Overall Class Structure

- CinCore, core definitions for Cinema code
- CinArtifactSet, a set of artifacts
- CinCore, Core code for all classes
- CinDatabase, an in-memory database instance
- CinDBReader, an object that reads a Cinema database from disk and builds a CinDatabase instance
- CinDBView, A view of a CinDatabase.
    - Contains CinParamSet and CinArtifactSet objects
- CinParameter, a single parameter
- CinParamSet, a set of CinParameter objects

### UI Class Structure

- CinCompoundSlider, a multi-widget slider
- CinImageView, a Cinema image-based view
- CinParamSliders, a set of sliders for a CinParamSet
- CinParameterMapDialog
- CinScopeWindow

### Other Classes

- CinScopeTest, a unit test class, utilizing Qt's testing framework


trzerba ustawic rozdzilczos emulatoru terminalu na
WIDTH = 168;
HEIGHT = 38;

pewne "fonts" moga dzialac niepoprawnie, w tym: zepsute proporcje, pomylona jaskrawosc i td.

uruchomic przez

./a.out

w razie potrzeba mozna skompilowac main.cpp, w takim przypadku render.cpp musi byc w tym samym pliku
np.

clang++ main.cpp

uwaga:
czasami wystepuja bledy graficzne(zwiazane z ograniczeniami liczb zmiennoprzecinkowych), ktore dobrze widac dzieki malej rozdielczosci i malym zasiegu kolorow
czasami terminal nie podaza wypisywac(wydarza sie to najczesciej w czasie automatycznego wyczyscenia terminalu)

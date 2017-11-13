#include <QApplication>

#include <LineupOptimizerFrontEnd.h>


int main( int argc, char* argv[] )
{
    // Create the application
    QApplication app( argc, argv );

    // Instantiate main GUI and show
    LineupOptimizerFrontEnd lofe;
    lofe.show();

    // Execute the app
    return app.exec();
}

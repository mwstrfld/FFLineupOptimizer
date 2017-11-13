#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>

#include <CsvParser.h>
#include <LineupOptimizerFrontEnd.h>
#include <ui_LineupOptimizerFrontEnd.h>


LineupOptimizerFrontEnd::LineupOptimizerFrontEnd( QWidget* parent )
    : QMainWindow( parent ),
      m_ui( new Ui::FFLineupOptimizerFrontEnd )
{
    // Parent the actual UI
    m_ui->setupUi( this );

    // Create a new CSV Parser
    m_parser = new CsvParser();

    // Create a new model for rankings display
    m_rankingsModel = dynamic_cast< QStandardItemModel* >( m_ui->rankingsTableWidget->model() );

    // Signal/slot connections
    connect( m_ui->optimizeButton, SIGNAL( pressed() ), SLOT( handleOptimizeButtonPressed() ) );
}


LineupOptimizerFrontEnd::~LineupOptimizerFrontEnd()
{
    delete m_ui;
}


void LineupOptimizerFrontEnd::handleOptimizeButtonPressed()
{
    QString qbFileName = QFileDialog::getOpenFileName( this,
                                                       "Open QB Rankings CSV File",
                                                       QDir::currentPath(),
                                                       "CSV (*.csv)" );

    m_parser->parseRankings( Player::Position::QB, qbFileName, m_rankingsModel );
}

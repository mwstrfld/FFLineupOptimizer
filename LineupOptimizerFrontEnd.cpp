#include <QCompleter>
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
    m_qbRankingsModel = new QStandardItemModel( this );
    m_ui->rankingsTableView->setModel( m_qbRankingsModel );

    // Signal/slot connections
    connect( m_ui->selectRankingsButton, SIGNAL( pressed() ), SLOT( handleSelectRankingsButtonPressed() ) );

    // Initialize My Team
    initializeMyTeamModel();
}


LineupOptimizerFrontEnd::~LineupOptimizerFrontEnd()
{
    delete m_ui;
}


void LineupOptimizerFrontEnd::handleSelectRankingsButtonPressed()
{
    QString qbFileName = QFileDialog::getOpenFileName( this,
                                                       "Open QB Rankings CSV File",
                                                       QDir::currentPath(),
                                                       "CSV (*.csv)" );

    m_parser->parseRankings( Player::Position::QB, qbFileName, m_qbRankingsModel );
}


void LineupOptimizerFrontEnd::initializeMyTeamModel()
{
    // Create the model for the team display
    m_myTeamModel = new QStandardItemModel( this );
    m_ui->myTeamTableView->setModel( m_myTeamModel );

    // Set the horizontal header labels
    QStringList hHeaders = { "Player", "Overall Ranking", "Position Ranking" };
    m_myTeamModel->setHorizontalHeaderLabels( hHeaders );

    // Set the vertical header labels
    QStringList vHeaders = { "QB", "WR1", "WR2", "WR3", "RB1", "RB2", "TE", "K", "DEF",
                             "BEN1", "BEN2", "BEN3", "BEN4", "BEN5", "BEN6" };
    m_myTeamModel->setVerticalHeaderLabels( vHeaders );
}

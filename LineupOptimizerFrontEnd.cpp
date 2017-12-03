#include <QCompleter>
#include <QDebug>
#include <QString>
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

    // Create new models for rankings displays
    // Overall
    m_overallRankingsModel = new QStandardItemModel( this );
    m_ui->overallRankingsTableView->setModel( m_overallRankingsModel );
    // QB
    m_qbRankingsModel = new QStandardItemModel( this );
    m_ui->qbRankingsTableView->setModel( m_qbRankingsModel );
    // WR
    m_wrRankingsModel = new QStandardItemModel( this );
    m_ui->wrRankingsTableView->setModel( m_wrRankingsModel );
    // RB
    m_rbRankingsModel = new QStandardItemModel( this );
    m_ui->rbRankingsTableView->setModel( m_rbRankingsModel );
    // TE
    m_teRankingsModel = new QStandardItemModel( this );
    m_ui->teRankingsTableView->setModel( m_teRankingsModel );
    // K
    m_kRankingsModel = new QStandardItemModel( this );
    m_ui->kRankingsTableView->setModel( m_kRankingsModel );
    // DST
    m_dstRankingsModel = new QStandardItemModel( this );
    m_ui->dstRankingsTableView->setModel( m_dstRankingsModel );

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
    Player::Position pos = Player::Position::NONE;
    QStandardItemModel* model = 0;

    QString windowTitle = "Open ";

    auto ind = m_ui->rankingsTabWidget->currentIndex();
    switch( ind )
    {
    case 0: // Overall
        windowTitle.append( "Overall" );
        pos = Player::Position::NONE;
        model = m_overallRankingsModel;
        break;
    case 1: // QB
        windowTitle.append( "Quarterback" );
        pos = Player::Position::QB;
        model = m_qbRankingsModel;
        break;
    case 2: // WR
        windowTitle.append( "Wide Receiver" );
        pos = Player::Position::WR;
        model = m_wrRankingsModel;
        break;
    case 3: // RB
        windowTitle.append( "Running Back" );
        pos = Player::Position::RB;
        model = m_rbRankingsModel;
        break;
    case 4: // TE
        windowTitle.append( "Tight End" );
        pos = Player::Position::TE;
        model = m_teRankingsModel;
        break;
    case 5: // K
        windowTitle.append( "Kicker" );
        pos = Player::Position::K;
        model = m_kRankingsModel;
        break;
    case 6: // DEF
        windowTitle.append( "Defense/Special Teams" );
        pos = Player::Position::DST;
        model = m_dstRankingsModel;
        break;
    default:
        break;
    }

    windowTitle.append( " Rankings CSV File" );
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     windowTitle,
                                                     QDir::currentPath(),
                                                     "CSV (*.csv)" );

    m_parser->parseRankings( pos, fileName, model );

    /*QString debugStr = "Index: ";
    debugStr.append( QString.arg( ind ) );
    debugStr.append( ", File name: " );
    debugStr.append( fileName );
    qDebug << debugStr;*/
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
